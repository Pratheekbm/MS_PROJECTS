/*
 * superScalar.h
 *
 *  Created on: Apr 24, 2015
 *      Author: Pratheek
 */

#ifndef SUPERSCALAR_H_
#define SUPERSCALAR_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <queue>
using namespace std;

typedef enum _STAGE {
    INV = -1,
    IF = 0,
    ID,
    IS,
    EX,
    WB
} STAGE;

typedef enum _READINESS {
    NOT_READY = 0,
    READY
} READINESS;

typedef enum _VALIDITY {
    INVALID = 0,
    VALID
} VALIDITY;

typedef struct _ROB {
    STAGE stage;
    int tag;
    int src1;
    int src2;
    int dest;
    int src1Tag;
    int src2Tag;
    int destTag;
    int type;
    int cyclesForcompletion;
    READINESS src1Ready;
    READINESS src2Ready;
    int IFEntry;
    int IDEntry;
    int ISEntry;
    int EXEntry;
    int WBEntry;
} ROB;

typedef struct _dispatchList {
    STAGE stage;
    int tag;
} dispatchList;

typedef struct _issueList {
    int tag;
    int src1Tag;
    int src2Tag;
    READINESS src1Ready;
    READINESS src2Ready;
} issueList;

typedef struct _executeList {
    int tag;
    int cyclesForCompletion;
} executeList;

typedef struct _register {
    int tag;
    VALIDITY validity;
} regist;
/* main class definition here */

struct compareIssueList: public std::binary_function<ROB*, ROB*, bool> {
    bool operator()(const ROB* lhs, const ROB* rhs) const {
        return lhs->tag > rhs->tag;
    }
};

class SuperScalar {
public:
    int N;
    int S;
    int cycle;
    int insCount;
    int fetchCount;
    int dispatchCount;
    int issueCount;
    int executeCount;
    int wbCount;
    int finished;
    regist *reg;
    executeList *exQ;
    queue<ROB*> FQ;
    queue<ROB*> DQ;
    priority_queue<ROB*, vector<ROB*>, compareIssueList> SQ;
    priority_queue<ROB*, vector<ROB*>, compareIssueList> EQ;
    queue<ROB*> FROB;

    SuperScalar(int, int);
    ~SuperScalar();
    void start(char*);
    void fetch(FILE*);
    void dispatch();
    void issue();
    void execute();
};

#endif /* SUPERSCALAR_H_ */
