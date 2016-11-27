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
#include <stdio.h>
#include <stdlib.h>
#include "castTypes.h"
#include "cache.h"
using namespace std;

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
        blocksize = atoi(argv[1]);
        L1Size = atoi(argv[2]);
        L1Asso = atoi(argv[3]);
        L2Size = atoi(argv[4]);
        L2Asso = atoi(argv[5]);
        traceFile = argv[8];

        switch (atoi(argv[6])) {
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

        switch (atoi(argv[7])) {
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

        FILE *myFile;
        char read_write;
        myFile = fopen((char *) argv[8], "r");
        long int address;
        if (!myFile)
            cout << "\n Error in file";
        else {
            while (fscanf(myFile, "%c%lx", &read_write, &address) != EOF) {
                if ('r' == read_write) {
                    L1.read(address);
                } else if ('w' == read_write) {
                    L1.write(address);
                }
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
        cout << "h. number of L2 read misses:  " << L2.readMiss << endl;
        cout << "i. number of L2 writes:       " << L2.totalWrite << endl;
        cout << "j. number of L2 write misses: " << L2.writeMiss << endl;
        cout << "k. L2 miss rate:              " << std::setprecision(6)
                << (float) (L2.readMiss) / (float) (L2.totalRead) << endl;
        cout << "l. number of L2 writebacks:   " << L2.writeBack << endl;
        cout << "m. total memory traffic:      " << L1.memTraffic + L2.memTraffic << endl;
    } else if (0 != L1Asso && 0 != L1Size) {

        Cache L1(CACHE_L1, L1Asso, L1Size, blocksize, lru, ip);
        FILE *myFile;
        char read_write;
        myFile = fopen((char *) argv[8], "r");
        long int address;
        if (!myFile)
            cout << "\n Error in file";
        else {
            while (fscanf(myFile, "%c%lx", &read_write, &address) != EOF) {
                if ('r' == read_write) {
                    L1.read(address);
                } else if ('w' == read_write) {
                    L1.write(address);
                }
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
        cout << "m. total memory traffic:      " << L1.memTraffic << endl;
    }
}

