/*
 * superScalar.cpp
 
 *
 *  Created on: Apr 24, 2015
 *      Author: Pratheek
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <queue>
#include "superScalar.h"
#include "castTypes.h"
using namespace std;

SuperScalar::SuperScalar(int S, int N) {
    cycle = 0;

    this->N = N;
    this->S = S;
    reg = new regist[128];
    for (int i = 0; i < 128; i++) {
        reg[i].tag = -1;
        reg[i].validity = VALID;
    }

    exQ = new executeList[N * 7];
    for (int i = 0; i < N; i++) {
        exQ[i].cyclesForCompletion = 0;
        exQ[i].tag = -1;
    }

    cycle = 0;
    insCount = 0;
    fetchCount = 0;
    dispatchCount = 0;
    issueCount = 0;
    executeCount = 0;
    wbCount = 0;
    finished = 0;
}

SuperScalar::~SuperScalar() {
    delete exQ;
    delete reg;
}

void SuperScalar::start(char* name) {
    FILE *fp = fopen((char *) name, "r");
    if (NULL == fp) {
        ERROR_LOG;
        cout << "File name not proper " << name << endl;
        return;
    }
    while (((fetchCount + dispatchCount + issueCount + executeCount) != 0) || (finished == 0)) {
        execute();
        issue();
        dispatch();
        fetch(fp);
        cycle++;
    }
    while (0 < FROB.size()) {
        ROB* item = FROB.front();
        int fetchTime = item->IDEntry - item->IFEntry;
        int dispatchTime = item->ISEntry - item->IDEntry;
        int issueTime = item->EXEntry - item->ISEntry;
        int exTime = item->WBEntry - item->EXEntry;

        printf("%d fu{%d} src{%d,%d} dst{%d} IF{%d,%d} ID{%d,%d} IS{%d,%d} EX{%d,%d} WB{%d,%d}\n", item->tag,
                item->type, item->src1, item->src2, item->dest, item->IFEntry, fetchTime, item->IDEntry, dispatchTime,
                item->ISEntry, issueTime, item->EXEntry, exTime, item->WBEntry, 1);
        FROB.pop();
    }

    printf("CONFIGURATION\n");
    printf(" superscalar bandwidth (N) = %d\n", N);
    printf(" dispatch queue size (2*N) = %d\n", 2 * N);
    printf(" schedule queue size (S)   = %d\n", S);
    printf("RESULTS\n");
    printf(" number of instructions = %d\n", insCount);
    printf(" number of cycles       = %d\n", cycle);
    float ipc = (float) (insCount) / (float) (cycle);
    printf(" IPC                    = %0.2f\n", ipc);

}

void SuperScalar::fetch(FILE* fp) {

    long PC = 0;

    while ((dispatchCount < 2 * N) && (0 != FQ.size())) {
        ROB *item;
        item = FQ.front();
        item->stage = ID;
        item->IDEntry = cycle;
        DQ.push(item);
        FQ.pop();
        fetchCount--;
        dispatchCount++;
    }

    while ((dispatchCount + fetchCount < 2 * N) && (fetchCount < N)) {
        if (!feof(fp)) {
            ROB *item = new ROB;
            fscanf(fp, "%lx %d %d %d %d\n", &PC, &(item->cyclesForcompletion), &(item->dest), &(item->src1),
                    &(item->src2));
            item->stage = IF;
            item->tag = insCount;
            item->src1Tag = -1;
            item->src2Tag = -1;
            item->destTag = -1;
            item->type = item->cyclesForcompletion;
            item->src1Ready = NOT_READY;
            item->src2Ready = NOT_READY;
            item->IFEntry = cycle;
            item->IDEntry = -1;
            item->ISEntry = -1;
            item->EXEntry = -1;
            item->WBEntry = -1;
            FQ.push(item);
            FROB.push(item);
            insCount++;
            fetchCount++;
            //cout << insCount << endl;
        } else {
            finished = 1;
            break;
        }
    }
}

void SuperScalar::dispatch() {
    int count = 0;
    while (S > SQ.size() && (0 != DQ.size()) && (N > count)) {
        ROB *item;
        item = DQ.front();
        item->stage = IS;
        item->ISEntry = cycle;

        if ((-1 == item->src1) || (VALID == reg[item->src1].validity)) {
            item->src1Ready = READY;
        } else {
            item->src1Ready = NOT_READY;
            item->src1Tag = reg[item->src1].tag;
        }

        if ((-1 == item->src2) || (VALID == reg[item->src2].validity)) {
            item->src2Ready = READY;
        } else {
            item->src2Ready = NOT_READY;
            item->src2Tag = reg[item->src2].tag;
        }

        if (-1 != item->dest) {
            reg[item->dest].tag = item->tag;
            reg[item->dest].validity = INVALID;
        }

        SQ.push(item);
        DQ.pop();
        dispatchCount--;
        issueCount++;
        count++;
    }
}

void SuperScalar::issue() {
    int count = 0;
    queue<ROB*> temp;
    ROB *item = NULL;
    while ((0 < SQ.size()) && (N > count) && (7 * N > EQ.size())) {
        item = SQ.top();
        if ((READY == item->src1Ready) && (READY == item->src2Ready)) {
            item->stage = EX;
            item->EXEntry = cycle;
            if (0 == item->cyclesForcompletion) {
                item->cyclesForcompletion = 1;
            } else if (1 == item->cyclesForcompletion) {
                item->cyclesForcompletion = 3;
            } else if (2 == item->cyclesForcompletion) {
                item->cyclesForcompletion = 7;
            } else {
                ERROR_LOG;
            }
            EQ.push(item);
            SQ.pop();
            issueCount--;
            executeCount++;
            count++;
        } else {
            SQ.pop();
            temp.push(item);
        }
    }

    while (0 < temp.size()) {
        ROB *item = temp.front();
        SQ.push(item);
        temp.pop();
    }
}

void SuperScalar::execute() {
    queue<ROB*> temp;
    while ((0 < EQ.size())) {
        ROB *item = EQ.top();
        item->cyclesForcompletion--;

        if (0 == item->cyclesForcompletion) {
            item->WBEntry = cycle;
            item->stage = WB;
            queue<ROB*> SQTemp;
            while (0 < SQ.size()) {
                ROB *SQItem = SQ.top();
                if ((SQItem->src1Tag == item->tag) && (NOT_READY == SQItem->src1Ready)) {
                    SQItem->src1Ready = READY;
                }
                if ((SQItem->src2Tag == item->tag) && (NOT_READY == SQItem->src2Ready)) {
                    SQItem->src2Ready = READY;
                }
                SQTemp.push(SQItem);
                SQ.pop();
            }

            while (0 < SQTemp.size()) {
                ROB* SQItem = SQTemp.front();
                SQ.push(SQItem);
                SQTemp.pop();
            }

            if (-1 != item->dest) {
                if (item->tag == reg[item->dest].tag) {
                    reg[item->dest].validity = VALID;
                }
            }
            EQ.pop();
            executeCount--;
            wbCount++;
        } else {
            EQ.pop();
            temp.push(item);
        }
    }

    while (0 < temp.size()) {
        ROB *item = temp.front();
        EQ.push(item);
        temp.pop();
    }
}

