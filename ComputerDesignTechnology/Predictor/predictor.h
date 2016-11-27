/*
 * gshareBp.h
 *
 *  Created on: Mar 23, 2015
 *      Author: Pratheek
 */

#ifndef PREDICTOR_H_
#define PREDICTOR_H_

typedef enum _decision {
    NOTTAKEN = 0,
    TAKEN = 1
} DECISION;

typedef enum _predictor {
    BIMODAL = 0,
    GSHARE = 1
} PREDICTOR;

class Predictor {
private:
protected:
public:

    int indexBits;
    int gbhbSize;
    int *pTable;
    int gbhb;
    int gbhbAdd;
    int gbhbMask;
    long int addressMask;
    Predictor(int mIndex, int nGbhbSize);
    ~Predictor();
    int log_2(long int var);
    void resetPtable(int resetTo);
    void getIndex(long int address, long int &index);
    DECISION predict(long int address);
    void updatePTable(long int address, DECISION actual);
    void updateHistory(long int address, DECISION actual);
    void print();
};

#endif /* PREDICTOR_H_ */
