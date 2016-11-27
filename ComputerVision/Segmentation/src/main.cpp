/*
 * main.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: pratheek
 */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ifs.h"
#include "castTypes.h"
#include "image.h"
using namespace std;

int main() {

    Image img1(3, 256,256);
    img1.read((char *)"asterix256.ifs");
    int hist[256];

    for(int i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    for (int i = 0 ; i < 256; i ++) {
        for( int j = 0; j< 256; j++) {
            hist[(int)img1.getValue(i, j)]++;
        }
    }

    for(int i = 0; i < 256; i++) {
        cout << i<< "," << hist[i] << endl;
    }
    cout << endl;

    Image img2(3, 256,256);
    img1.read((char *)"asterix256histeq.ifs");

    for(int i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    for (int i = 0 ; i < 256; i ++) {
        for( int j = 0; j< 256; j++) {
            hist[(int)img1.getValue(i, j)]++;
        }
    }

    for(int i = 0; i < 256; i++) {
        cout << i<< "," << hist[i] << endl;
    }
    cout << endl;

    return 0;
}

