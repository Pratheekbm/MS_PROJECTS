/*
 * gshareBp.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: Pratheek
 */
#include "predictor.h"

#include <sys/time.h>
#include <unistd.h>
#include "castTypes.h"

Predictor::Predictor(int mIndex, int nGbhbSize) {

    int pTableSize = 0;

    indexBits = mIndex;
    gbhbSize = nGbhbSize;

    pTableSize = 1 << indexBits;
    if (0 < indexBits) {
        pTable = new int[pTableSize];
    } else {
        pTable = NULL;
    }

    for (int i = 0; i < pTableSize; i++) {
        pTable[i] = 2;
    }
    gbhb = 0;
    if (0 != nGbhbSize) {
        gbhbAdd = 1 << (nGbhbSize - 1);
    }
    gbhbMask = (1 << gbhbSize) - 1;
    addressMask = (1 << indexBits) - 1;
}

Predictor::~Predictor() {
    delete pTable;
    pTable = NULL;
    indexBits = 0;
    gbhbSize = 0;
    gbhb = 0;
    gbhbMask = 0;
}

int Predictor::log_2(long int var) {
    int ans = 0;
    do {
        var = var / 2;
        ans++;
    } while (var != 1);
    return ans;
}

void Predictor::resetPtable(int resetTo) {
    long int pTableSize = 1 << indexBits;
    for (int i = 0; i < pTableSize; i++) {
        pTable[i] = resetTo;
    }
}

void Predictor::getIndex(long int address, long int &index) {
    index = (address >> 2);
    index = (index) & (addressMask);

    if (0 != gbhbSize) {
        index = (index) ^ (gbhb << (indexBits - gbhbSize));
    }
}

DECISION Predictor::predict(long int address) {
    DECISION prediction = NOTTAKEN;
    long int index = 0;
    index = (address >> 2);

    index = (index) & (addressMask);

    if (0 != gbhbSize) {
        index = (index) ^ (gbhb << (indexBits - gbhbSize));
    }

    if (2 <= pTable[index]) {
        prediction = TAKEN;
    } else {
        prediction = NOTTAKEN;
    }

    return prediction;
}

void Predictor::updatePTable(long int address, DECISION actual) {
    long int index = 0;
    index = (address >> 2);

    index = (index) & (addressMask);

    if (0 != gbhbSize) {
        index = (index) ^ (gbhb << (indexBits - gbhbSize));
    }

    if (TAKEN == actual) {
        if (3 != pTable[index]) {
            pTable[index]++;
        }
    } else if (NOTTAKEN == actual) {
        if (0 != pTable[index]) {
            pTable[index]--;
        }
    } else {
        ERROR_LOG;
    }
}

void Predictor::updateHistory(long int address, DECISION actual) {
    long int index = 0;
    index = (address >> 2);

    index = (index) & (addressMask);

    if (0 != gbhbSize) {
        index = (index) ^ (gbhb << (indexBits - gbhbSize));
    }

    if (TAKEN == actual) {
        if (0 != gbhbSize) {
            gbhb = gbhb >> 1;
            gbhb += gbhbAdd;
            gbhb = gbhb & gbhbMask;
        }
    } else if (NOTTAKEN == actual) {
        if (0 != gbhbSize) {
            gbhb = gbhb >> 1;
            gbhb = gbhb & gbhbMask;
        }
    } else {
        ERROR_LOG;
    }
}

void Predictor::print() {
    long int pTableSize = 1 << indexBits;
    for (int i = 0; i < pTableSize; i++) {
        cout << i << "\t" << pTable[i] << endl;
    }
}
