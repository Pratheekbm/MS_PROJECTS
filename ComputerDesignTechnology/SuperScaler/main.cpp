//
//  main.cpp
//  mp3
//
//  Created by Pratheek Mallikarjuna on 4/26/15.
//  Copyright (c) 2015 Pratheek Mallikarjuna. All rights reserved.
//

/*
 * main.cpp
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
#include "superScalar.h"
#include "castTypes.h"
using namespace std;

int main(int argc, char *argv[]) {

    if (4 != argc) {
        ERROR_LOG;
        cout << "Input format" << endl;
        cout << "sim <S> <N> <tracefile>" << endl;
        return 0;
    } else {
        int S = atoi(argv[1]);
        int N = atoi(argv[2]);
        FILE *fp = fopen((char *) argv[3], "r");
        if (NULL == fp) {
            ERROR_LOG;
            cout << "File name not proper " << argv[3] << endl;
            return 0;
        }

        SuperScalar tomosulo(S, N);
        tomosulo.start((char *) argv[3]);
    }
}

