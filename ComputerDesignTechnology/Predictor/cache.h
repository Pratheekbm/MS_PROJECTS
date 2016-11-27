/*
 * cache.h
 *
 *  Created on: Feb 27, 2015
 *      Author: pratheek
 */

#ifndef INC_CACHE_H_
#define INC_CACHE_H_

typedef enum _STATUS {
    FAIL = -1,
    SUCCESS = 0
} STATUS;

typedef enum _TYPE {
    RESET = 0,
    SET = 1
} TYPE;

typedef enum _swing {
    MISS = 0,
    HIT = 1
}SWING;
typedef enum _CACHEID {
    CACHE_L1 = 1,
    CACHE_L2 = 2,
    CACHE_L3 = 3,
    MEM = 100,
    BAD = 101
} CACHEID;

typedef enum _replacementPolicy {
    LRU = 0,
    FIFO = 1,
    PLRU = 2,
    INV = 3
} LRUPOLICY;

typedef enum _INC {
    NONINCLUSION = 0,
    INCLUSION = 1,
    EXCLUSION = 2,
    NONE = 3
} IP;

typedef enum _VALIDITY {
    INVALID = -1,
    VALID = 0,
    DIRTY = 1
} VALIDITY;

class Cache {
public:
    CACHEID id;
    int assosivity;
    int size;
    int blockSize;
    LRUPOLICY lruPolicy;
    IP incPolicy;
    int noOfSets;
    int bitsForBlockOffset;
    int bitsForIndex;
    int bitsForTag;
    long int indexMask;
    long int **fifoLruTs;
    int ***lruMatrix;
    int **pLruMatrix;

    long int **tag;
    VALIDITY **validity;
    Cache *next;
    Cache *previous;
    int totalRead;
    int totalWrite;
    int readMiss;
    int writeMiss;
    int readHit;
    int writeHit;
    int writeBack;
    int memTraffic;

    Cache(CACHEID id, int associvity, int size, int blockSize, LRUPOLICY lru, IP incPolicy);
    ~Cache();
    void calculateTagFromAddress(long int address, long int &tag, long int &index);
    int log_2(long int var);
    STATUS searchForTagInASet(long int localtag, long int index, int &slot);
    STATUS checkSpaceInASet(long int index, int &slot);
    void updateLru(long int index, int slot);
    void getLru(long int index, long int &tag, int &slot);
    void updateValidity(long int address, VALIDITY val);
    void updateValidity(long int index, int slot, VALIDITY val);
    STATUS evictBlockWithAddress(long int address);
    void evictBlockFromASet(long int index);
    void checkValidity(long int address, VALIDITY &validity);
    SWING read(long int address);
    void write(long int write);
    void print();
};

#endif /* INC_CACHE_H_ */
