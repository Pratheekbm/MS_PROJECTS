/*
 * sim_cache.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: pratheek
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include "castTypes.h"
#include "cache.h"
using namespace std;

void getParameters(int i, int figure, int &blocksize, int &L1Size, int &L1Asso, int &L2Size, int &L2Asso,
        LRUPOLICY &lruP, IP &incP, string &traceFile) {

    if (1 == figure) {
        if (0 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (1 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (2 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (3 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (4 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (5 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (6 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (7 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (8 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (9 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (10 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (11 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        }
    }

    if (2 == figure) {
        if (0 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 1;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (1 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 2;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (2 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (3 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 8;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (4 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 1;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (5 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 2;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (6 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (7 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 8;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (8 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 1;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (9 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 2;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (10 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (11 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 8;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        }
    }
    if (3 == figure) {
        if (0 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (1 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (2 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (3 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (4 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (5 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (6 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (7 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (8 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (9 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (10 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (11 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (12 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (13 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (14 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (15 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (16 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (17 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (18 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (19 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (20 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (21 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (22 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (23 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (24 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (25 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (26 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (27 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (28 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (29 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (30 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (31 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = FIFO;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (32 == i) {
            blocksize = 64;
            L1Size = 8192;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (33 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (34 == i) {
            blocksize = 64;
            L1Size = 32768;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (36 == i) {
            blocksize = 64;
            L1Size = 65536;
            L1Asso = 4;
            L2Size = 0;
            L2Asso = 0;
            lruP = PLRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        }
    }
    if (4 == figure) {
        if (0 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (1 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 262144;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (2 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 524288;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (3 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 1048576;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (4 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (5 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 262144;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (6 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 524288;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (7 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 1048576;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (8 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (9 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 262144;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (10 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 524288;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (11 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 1048576;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        }
    }

    if (5 == figure) {
        if (0 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 1;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (1 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 2;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (2 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 4;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (3 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (4 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 1;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (5 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 2;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (6 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 4;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (7 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (8 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 1;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (9 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 2;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (10 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 4;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (11 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        }
    }
    if (6 == figure) {
        if (0 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (1 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 262144;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (2 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 524288;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (3 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 1048576;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "MCF.t";
        } else if (4 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (5 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 262144;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (6 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 524288;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (7 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 1048576;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "GCC.t";
        } else if (8 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 131072;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (9 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 262144;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (10 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 524288;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        } else if (11 == i) {
            blocksize = 64;
            L1Size = 16384;
            L1Asso = 4;
            L2Size = 1048576;
            L2Asso = 8;
            lruP = LRU;
            incP = NONINCLUSION;
            traceFile = "LBM.t";
        }
        L1Size = 8192 * 2 * 2 * 2;
        incP = EXCLUSION;
    }
}
int main(int argc, char *argv[]) {

    int blocksize = 0;
    int L1Size = 0;
    int L1Asso = 0;
    int L2Size = 0;
    int L2Asso = 0;
    LRUPOLICY lru = INV;
    IP ip = NONE;
    string traceFile;
    string incP, lruP;

    if (9 != argc) {
        ERROR_LOG;
        cout << "ER : Insufficient arguments";
        return 0;
    } else {
        blocksize = stoi(argv[1], nullptr, 10);
        L1Size = stoi(argv[2], nullptr, 10);
        L1Asso = stoi(argv[3], nullptr, 10);
        L2Size = stoi(argv[4], nullptr, 10);
        L2Asso = stoi(argv[5], nullptr, 10);
        traceFile = argv[8];

        switch (stoi(argv[6], nullptr, 10)) {
        case 0: {
            lru = LRU;
            lruP = "LRU";
            break;
        }
        case 1: {
            lru = FIFO;
            lruP = "FIFO";
            break;
        }
        case 2: {
            lru = PLRU;
            lruP = "Psedo LRU";
            break;
        }
        default: {
            ERROR_LOG;
            lru = INV;
            break;
        }
        }

        switch (stoi(argv[7], nullptr, 10)) {
        case 0: {
            ip = NONINCLUSION;
            incP = "non-inclusive";
            break;
        }
        case 1: {
            ip = INCLUSION;
            incP = "inclusive";
            break;
        }
        case 2: {
            ip = EXCLUSION;
            incP = "exclusive";
            break;
        }
        default: {
            ERROR_LOG;
            cout << "ER : Invalid ip";
            break;
        }

        }

    }

    int start = 0;
    int iteration = 36;
    float results[iteration][13];
    int figure = 3;
    for (int i = start; i < iteration; i++) {

        getParameters(i, figure, blocksize, L1Size, L1Asso, L2Size, L2Asso, lru, ip, traceFile);
        cout << "===== Simulator configuration =====" << endl;
        cout << "BLOCKSIZE:             " << blocksize << endl;
        cout << "L1_SIZE:               " << L1Size << endl;
        cout << "L1_ASSOC:              " << L1Asso << endl;
        cout << "L2_SIZE:               " << L2Size << endl;
        cout << "L2_ASSOC:              " << L2Asso << endl;
        cout << "REPLACEMENT POLICY:    " << lruP << endl;
        cout << "INCLUSION PROPERTY:    " << incP << endl;
        cout << "trace_file:            " << traceFile << endl;
        if (0 != L1Asso && 0 != L1Size && 0 != L2Asso && 0 != L2Size) {
            Cache L1(CACHE_L1, L1Asso, L1Size, blocksize, lru, ip);
            Cache L2(CACHE_L2, L2Asso, L2Size, blocksize, lru, ip);
            L1.next = &(L2);
            L2.previous = &(L1);

            string line;
            ifstream myFile;
            myFile.open(traceFile);
            long int add = 0;
            while (std::getline(myFile, line)) {
                string address = (string) &line[2];

                add = stol(address, nullptr, 16);

                if ('r' == line[0]) {
                    L1.read(add);
                } else if ('w' == line[0]) {
                    L1.write(add);
                }
            }

            cout << "===== Simulation results (raw) =====" << endl;
            cout << "a. number of L1 reads:        " << L1.totalRead << endl;
            cout << "b. number of L1 read misses:  " << L1.readMiss << endl;
            cout << "c. number of L1 writes:       " << L1.totalWrite << endl;
            cout << "d. number of L1 write misses: " << L1.writeMiss << endl;
            cout << "e. L1 miss rate:              " << std::setprecision(6)
                    << (float) (L1.readMiss + L1.writeMiss) / (float) (L1.totalRead + L1.totalWrite) << endl;
            cout << "f. number of L1 writebacks:   " << L1.writeBack << endl;
            cout << "g. number of L2 reads:        " << L2.totalRead << endl;
            cout << "h. number of L2 read misse:   " << L2.readMiss << endl;
            cout << "i. number of L2 writes:       " << L2.totalWrite << endl;
            cout << "j. number of L2 write misses: " << L2.writeMiss << endl;
            cout << "k. L2 miss rate:              " << std::setprecision(6)
                    << (float) (L2.readMiss) / (float) (L2.totalRead) << endl;
            cout << "l. number of L2 writebacks:   " << L2.writeBack << endl;
            cout << "m. total memory traffic:      " << L1.memTraffic + L2.memTraffic << endl;
            results[i][0] = (float) L1.totalRead;
            results[i][1] = L1.readMiss;
            results[i][2] = L1.totalWrite;
            results[i][3] = L1.writeMiss;
            results[i][4] = (float) (L1.readMiss + L1.writeMiss) / (float) (L1.totalRead + L1.totalWrite);
            results[i][5] = L1.writeBack;
            results[i][6] = L2.totalRead;
            results[i][7] = L2.readMiss;
            results[i][8] = L2.totalWrite;
            results[i][9] = L2.writeMiss;
            results[i][10] = (float) (L2.readMiss) / (float) (L2.totalRead);
            results[i][11] = L2.writeBack;
            results[i][12] = L1.memTraffic + L2.memTraffic;

        } else if (0 != L1Asso && 0 != L1Size) {
            Cache L1(CACHE_L1, L1Asso, L1Size, blocksize, lru, ip);
            string line;
            ifstream myFile;
            myFile.open(traceFile);
            long int add = 0;
            while (std::getline(myFile, line)) {
                string address = (string) &line[2];

                add = stol(address, nullptr, 16);
                if ('r' == line[0]) {
                    L1.read(add);
                } else if ('w' == line[0]) {
                    L1.write(add);
                }
            }
            cout << "===== Simulation results (raw) =====" << endl;
            cout << "a. number of L1 reads:        " << L1.totalRead << endl;
            cout << "b. number of L1 read misses:  " << L1.readMiss << endl;
            cout << "c. number of L1 writes:       " << L1.totalWrite << endl;
            cout << "d. number of L1 write misses: " << L1.writeMiss << endl;
            cout << "e. L1 miss rate:              " << std::setprecision(6)
                    << (float) (L1.readMiss + L1.writeMiss) / (float) (L1.totalRead + L1.totalWrite) << endl;
            cout << "f. number of L1 writebacks:   " << L1.writeBack << endl;
            cout << "g. number of L2 reads:        0" << endl;
            cout << "h. number of L2 read misses:  0" << endl;
            cout << "i. number of L2 writes:       0" << endl;
            cout << "j. number of L2 write misses: 0" << endl;
            cout << "k. L2 miss rate:              0" << endl;
            cout << "l. number of L2 writebacks:   0" << endl;
            cout << "m. total memory traffic:      0" << endl;
            results[i][0] = (float) L1.totalRead;
            results[i][1] = L1.readMiss;
            results[i][2] = L1.totalWrite;
            results[i][3] = L1.writeMiss;
            results[i][4] = (float) (L1.readMiss + L1.writeMiss) / (float) (L1.totalRead + L1.totalWrite);
            results[i][5] = L1.writeBack;
            results[i][6] = 0;
            results[i][7] = 0;
            results[i][8] = 0;
            results[i][9] = 0;
            results[i][10] = 0;
            results[i][11] = 0;
            results[i][12] = 0;
        }
    }

    for (int j = 0; j < iteration; j++) {
        if (j % 4 == 0) {
            cout << "Next Trial" << endl;
        }
        for (int k = 0; k < 13; k++) {
            cout << std::setprecision(10) << results[j][k] << "\t";
        }
        cout << endl;

    }
}

