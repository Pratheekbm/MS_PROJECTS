/*
 * cache.cpp

 *
 *  Created on: Feb 27, 2015
 *      Author: pratheek
 */
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include  <math.h>
#include"cache.h"
#include "castTypes.h"

Cache::Cache(CACHEID id, int assosivity, int size, int blockSize, LRUPOLICY lru, IP incPolicy) {

    this->id = id;
    this->assosivity = assosivity;
    this->size = size;
    this->blockSize = blockSize;
    this->lruPolicy = lru;
    this->incPolicy = incPolicy;
    if ((0 == this->blockSize) || (0 == this->assosivity)) {
        return;
    }
    bitsForBlockOffset = log_2(blockSize);
    if (0 != blockSize) {
        noOfSets = (size / blockSize) / assosivity;
        bitsForIndex = log_2(noOfSets);
    } else {
        ERROR_LOG;
        cout << "ER << Divide by zero" << endl;
    }

    indexMask = (1 << bitsForIndex) - 1; //pow(2, bitsForIndex) - 1;

    tag = new long int*[noOfSets];

    for (int i = 0; i < noOfSets; i++) {
        tag[i] = new long int[assosivity];
    }

    validity = new VALIDITY*[noOfSets];

    for (int i = 0; i < noOfSets; i++) {
        validity[i] = new VALIDITY[assosivity];
    }

    for (int i = 0; i < noOfSets; i++) {
        for (int j = 0; j < assosivity; j++) {
            tag[i][j] = 0x7FFFFFFFFFFFFFFF;
            validity[i][j] = INVALID;
        }
    }

    if (LRU == lruPolicy) {
        lruMatrix = new int**[noOfSets];
        for (int i = 0; i < noOfSets; i++) {
            lruMatrix[i] = new int*[assosivity];
            for (int j = 0; j < assosivity; j++) {
                lruMatrix[i][j] = new int[assosivity];
            }
        }

        for (int i = 0; i < noOfSets; i++) {
            for (int j = 0; j < assosivity; j++) {
                for (int k = 0; k < assosivity; k++) {
                    lruMatrix[i][j][k] = 0;
                }
            }
        }
    } else if (FIFO == lruPolicy) {
        fifoLruTs = new long int*[noOfSets];
        for (int i = 0; i < noOfSets; i++) {
            fifoLruTs[i] = new long int[assosivity];
        }
        for (int i = 0; i < noOfSets; i++) {
            for (int j = 0; j < assosivity; j++) {
                fifoLruTs[i][j] = 0;
            }
        }

    } else if (PLRU == lruPolicy) {
        pLruMatrix = new int*[noOfSets];
        for (int i = 0; i < noOfSets; i++) {
            pLruMatrix[i] = new int[assosivity - 1];
        }
        for (int i = 0; i < noOfSets; i++) {
            for (int j = 0; j < assosivity - 1; j++) {
                pLruMatrix[i][j] = 1;
            }
        }
    }

    next = NULL;
    previous = NULL;
    totalRead = 0;
    totalWrite = 0;
    readMiss = 0;
    writeMiss = 0;
    readHit = 0;
    writeHit = 0;
    writeBack = 0;
    memTraffic = 0;
}

Cache::~Cache() {

    if ((0 == this->blockSize) || (0 == this->assosivity)) {
        return;
    }

    if (LRU == lruPolicy) {
        for (int i = 0; i < noOfSets; i++) {
            for (int j = 0; j < assosivity; j++) {
                delete[] lruMatrix[i][j];
            }
            delete[] lruMatrix[i];
        }
        delete[] lruMatrix;
    } else if (FIFO == lruPolicy) {
        for (int i = 0; i < noOfSets; i++) {
            delete[] fifoLruTs[i];
        }
        delete[] fifoLruTs;
    } else if (PLRU == lruPolicy) {
        for (int i = 0; i < noOfSets; i++) {
            delete[] pLruMatrix[i];
        }
        delete[] pLruMatrix;
    }

    for (int i = 0; i < noOfSets; i++) {
        delete[] tag[i];
        delete[] validity[i];
    }
    delete[] validity;
    delete[] tag;

    id = BAD;
    assosivity = 0;
    size = 0;
    blockSize = 0;
    lruPolicy = INV;
    incPolicy = NONE;
    next = NULL;
    previous = NULL;
    readMiss = 0;
    writeMiss = 0;
    readHit = 0;
    writeHit = 0;
    writeBack = 0;
}

int Cache::log_2(long int var) {
    int ans = 0;
    do {
        var = var / 2;
        ans++;
    } while (var != 1);
    return ans;
}

void Cache::calculateTagFromAddress(long int address, long int &tag, long int &index) {
    long int tempAdd = address;
    tempAdd = tempAdd >> bitsForBlockOffset;
    index = tempAdd & indexMask;
    tag = tempAdd >> bitsForIndex;
}

STATUS Cache::searchForTagInASet(long int localTag, long int index, int &slot) {

    for (int i = 0; i < assosivity; i++) {
        if ((localTag == tag[index][i]) && (INVALID != validity[index][i])) {
            slot = i;
            return SUCCESS;
        }
    }
    return FAIL;
}

STATUS Cache::checkSpaceInASet(long int index, int &slot) {

    for (int i = 0; i < assosivity; i++) {
        if (INVALID == validity[index][i]) {
            slot = i;
            return SUCCESS;
        }
    }
    return FAIL;
}

void Cache::updateLru(long int index, int slot) {
    if (LRU == lruPolicy) {
        int **localLru = lruMatrix[index];
        for (int i = 0; i < assosivity; i++) {
            localLru[slot][i] = 1;
        }
        for (int i = 0; i < assosivity; i++) {
            localLru[i][slot] = 0;
        }

    } else if (FIFO == lruPolicy) {
        timeval tv;
        gettimeofday(&tv, NULL);
        fifoLruTs[index][slot] = tv.tv_sec * 1000000 + tv.tv_usec;
        usleep(1);
    } else if (PLRU == lruPolicy) {
        int *pLruArray = pLruMatrix[index];
        int child = slot + assosivity - 1;
        int parent = floor((float) (child - 1) / 2.0);
        do {
            if (child == ((2 * parent) + 1)) {
                pLruArray[parent] = 0;
            } else if (child == ((2 * parent) + 2)) {
                pLruArray[parent] = 1;
            } else {
                ERROR_LOG;
            }
            child = parent;
            parent = floor((float) (child - 1) / 2.0);
        } while (parent >= 0);
    }
}
void Cache::getLru(long int index, long int &localTag, int &slot) {
    if (LRU == lruPolicy) {
        int **localLru = lruMatrix[index];
        int sortArray[assosivity];
        int min = assosivity;
        for (int i = 0; i < assosivity; i++) {
            sortArray[i] = 0;
            for (int j = 0; j < assosivity; j++) {
                sortArray[i] += localLru[i][j];
            }
        }

        for (int i = 0; i < assosivity; i++) {
            if (sortArray[i] < min && INVALID != validity[index][i]) {
                min = sortArray[i];
                localTag = tag[index][i];
                slot = i;
            }
        }
    } else if (FIFO == lruPolicy) {
        long int min = 0x7FFFFFFFFFFFFFFF;
        for (int i = 0; i < assosivity; i++) {
            if (fifoLruTs[index][i] < min && INVALID != validity[index][i]) {
                min = fifoLruTs[index][i];
                localTag = tag[index][i];
                slot = i;
            }
        }
    } else if (PLRU == lruPolicy) {
        int *pLruArray = pLruMatrix[index];
        int parent = 0;
        do {
            if (0 == pLruArray[parent]) {
                parent = 2 * parent + 2;
            } else if (1 == pLruArray[parent]) {
                parent = 2 * parent + 1;
            }
        } while ((assosivity - 1) > parent);
        slot = parent - assosivity + 1;
        localTag = tag[index][slot];
    }
}

void Cache::updateValidity(long int address, VALIDITY val) {
    long int index = 0, localTag = 0;
    int slot = 0;
    STATUS status = FAIL;
    calculateTagFromAddress(address, localTag, index);
    status = searchForTagInASet(localTag, index, slot);
    if (SUCCESS == status) {
        validity[index][slot] = val;
    }
}

void Cache::updateValidity(long int index, int slot, VALIDITY val) {

    validity[index][slot] = val;
}

STATUS Cache::evictBlockWithAddress(long int address) {
    long int index = 0, localTag = 0;
    int slot = 0;
    STATUS status = FAIL;
    STATUS writeToMemDuringBackInvalidation = FAIL;

    calculateTagFromAddress(address, localTag, index);
    status = searchForTagInASet(localTag, index, slot);
    if (SUCCESS == status) {
        if (INCLUSION == incPolicy) {
            if (NULL != previous) {
                writeToMemDuringBackInvalidation = previous->evictBlockWithAddress(address);
            }
        }
        if (FAIL == writeToMemDuringBackInvalidation) {
            if ((DIRTY == validity[index][slot]) && (INCLUSION == incPolicy)) {
                writeToMemDuringBackInvalidation = SUCCESS;
                memTraffic++;
            } else {
                writeToMemDuringBackInvalidation = FAIL;
            }
        }

        tag[index][slot] = 0x7FFFFFFFFFFFFFFF;
        updateValidity(index, slot, INVALID);
//updateLru(index, slot);
        return writeToMemDuringBackInvalidation;

    } else {
        writeToMemDuringBackInvalidation = FAIL;
    }
    return writeToMemDuringBackInvalidation;
}

void Cache::evictBlockFromASet(long int index) {
    long int localTag = 0;
    long int tempAdd = 0;
    int slot;
    STATUS status = FAIL;
    getLru(index, localTag, slot);
    tempAdd = tag[index][slot];
    tempAdd = tempAdd << bitsForIndex;
    tempAdd = tempAdd | index;
    tempAdd = tempAdd << bitsForBlockOffset;

    if (INCLUSION == incPolicy) {
        if (NULL != previous) {
            status = previous->evictBlockWithAddress(tempAdd);
            if (SUCCESS == status) {
                validity[index][slot] = VALID;
            }
        }
    }

    if (DIRTY == validity[index][slot]) {
        writeBack++;
        if (NULL == next) {
            memTraffic++;
        }
        if (NULL != next) {
            next->write(tempAdd);
        }
    } else {
        if ((EXCLUSION == incPolicy) && (NULL != next)) {
            next->write(tempAdd);
            next->updateValidity(tempAdd, VALID);
        }
    }

    tag[index][slot] = 0x7FFFFFFFFFFFFFFF;
    updateValidity(index, slot, INVALID);
    //updateLru(index, slot);
}

void Cache::checkValidity(long int address, VALIDITY &valid) {
    long int index = 0, localTag = 0;
    int slot = 0;
    STATUS status = FAIL;
    calculateTagFromAddress(address, localTag, index);
    status = searchForTagInASet(localTag, index, slot);
    if (SUCCESS == status) {
        valid = validity[index][slot];
    } else {
        if (NULL != next) {
            next->checkValidity(address, valid);
        } else {
            valid = INVALID;
        }
    }
}

SWING Cache::read(long int address) {
    SWING swing = MISS;
    long int index = 0, localTag = 0;
    int slot = 0;
    STATUS status = FAIL;
    VALIDITY validi = VALID;

    totalRead++;
    calculateTagFromAddress(address, localTag, index);
    status = searchForTagInASet(localTag, index, slot);
    if (SUCCESS == status) {
//read hit
        swing = HIT;
        readHit++;
        if (FIFO != lruPolicy) {
            updateLru(index, slot);
        }
        if (EXCLUSION == incPolicy) {
            if (NULL != previous) {
                evictBlockWithAddress(address);
            }
        }
    } else {
//read miss
        swing = MISS;
        readMiss++;
        if (NULL == next) {
            memTraffic++;
        }
        status = checkSpaceInASet(index, slot);
        if (SUCCESS == status) {
            // there is space in cache, no need to evict
            if (NULL != next) {
                checkValidity(address, validi);
                if (DIRTY != validi) {
                    validi = VALID;
                }
                next->read(address);
            }
            if (EXCLUSION != incPolicy) {
                tag[index][slot] = localTag;
                updateLru(index, slot);
                updateValidity(index, slot, VALID);
            } else {
                if (NULL == previous) {
                    tag[index][slot] = localTag;
                    updateLru(index, slot);
                    updateValidity(index, slot, validi);
                }
            }
        } else {
            //no space in cache, need to evict LRU
            if (EXCLUSION != incPolicy) {
                evictBlockFromASet(index);
                if (NULL != next) {
                    next->read(address);
                }
                status = checkSpaceInASet(index, slot);
                if (SUCCESS == status) {
                    tag[index][slot] = localTag;
                    updateLru(index, slot);
                    updateValidity(index, slot, VALID);
                } else {
                    ERROR_LOG;
                    cout << "ER : This can't be happening" << endl;
                }
            } else {
                if (NULL == previous) {
                    evictBlockFromASet(index);
                    if (NULL != next) {
                        checkValidity(address, validi);
                        if (DIRTY != validi) {
                            validi = VALID;
                        }
                        next->read(address);
                    }
                    status = checkSpaceInASet(index, slot);
                    if (SUCCESS == status) {
                        tag[index][slot] = localTag;
                        updateLru(index, slot);
                        updateValidity(index, slot, validi);
                    } else {
                        ERROR_LOG;
                        cout << "ER : This can't be happening" << endl;
                    }
                }
            }
        }
    }
    return swing;
}

void Cache::write(long int address) {

    long int index = 0, localTag = 0;
    int slot = 0;
    STATUS status = FAIL;
    totalWrite++;

    calculateTagFromAddress(address, localTag, index);
    status = searchForTagInASet(localTag, index, slot);
    if (SUCCESS == status) {
//write hit
        writeHit++;
        if (FIFO != lruPolicy) {
            updateLru(index, slot);
        }
        updateValidity(index, slot, DIRTY);
    } else {
//write miss
        writeMiss++;
        if ((NULL == next) && (EXCLUSION != incPolicy)) {
            memTraffic++;
        }
        status = checkSpaceInASet(index, slot);
        if (SUCCESS == status) {
            //there is space in cache, no need to evict
            if (NULL != next) {
                next->read(address);
            }

            tag[index][slot] = localTag;
            updateLru(index, slot);
            updateValidity(index, slot, DIRTY);
        } else {
            //no space in cache, need to evict LRU
            evictBlockFromASet(index);
            status = checkSpaceInASet(index, slot);
            if (NULL != next) {
                next->read(address);
            }
            if (SUCCESS == status) {
                tag[index][slot] = localTag;
                updateLru(index, slot);
                updateValidity(index, slot, DIRTY);
            } else {
                ERROR_LOG;
                cout << "ER : This can't be happening" << endl;
            }
        }
    }
}

void Cache::print() {
    for (int i = 0; i < noOfSets; i++) {
        cout << "set " << i << "\t:";
        for (int j = 0; j < assosivity; j++) {
            cout << hex << "\t" << tag[i][j];
        }
        cout << dec << endl;
    }
}
