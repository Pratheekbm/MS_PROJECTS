/*
 * main.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: pratheek
 */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include "ifs.h"
#include "flip.h"
#include "castTypes.h"
#include "image.h"
using namespace std;

#define PI 3.14159265

int main() {

    Image img((char *) "site4.c.ifs");
    float **kernel;
    float kernel1[3][3] = { { 1, 1, 1 }, { 1, 2, 1 }, { 1, 1, 1 } };
    kernel = new float*[3];
    for (int i = 0; i < 3; i++)
        kernel[i] = new float[3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = kernel1[i][j];
        }
    }
//    int row = img.row;
//    int col = img.col;
//    int midRow = row / 2;
//    int midCol = col / 2;
//    float disFromMid = 0;
//
//    img.reset(0);
//    for (int _row = 0; _row < row; _row++) {
//        for (int _col = 0; _col < col; _col++) {
//            disFromMid = sqrt((_row - midRow) * (_row - midRow) + (_col - midCol) * (_col - midCol));
//            if (100 > disFromMid) {
//                img.img[_row][_col] = 256;
//            }
//        }
//    }
//    img.write((char*)"synth.ifs");
    //img.convl((float **) kernel, 3, 3);
    //img.convl((float **) kernel, 3, 3);
    img.write((char *) "blur.ifs");

    Image imgDx(img), imgDy(img), imgGrad(img), temp(img);
    Image accumulator(img);

    accumulator.reset(0);

//    Image cur(img), curx(img), cury(img), curxx(img), curyy(img), curxy(img), curx2(img), cury2(img), num(img), den(
//            img);
//    Image num1(img), num2(img), num3(img);
//    Image radius(img);
//
//    radius.reset(1);
//    num.reset(0);
//    den.reset(0);
//
//    curx.diffx();
//    cury.diffy();
//    curx2 = curx;
//    cury2 = cury;
//    curxy = curx;
//    curxy.diffy();
//
//    curx2.mul(curx2);
//    cury2.mul(cury2);
//
//    curxx = curx;
//    curyy = cury;
//
//    curxx.diffx();
//    curyy.diffy();
//
//    num1 = curxx;
//    num1.mul(curx2);
//    num2 = curx;
//    num2.mul(cury);
//    num2.mul(curxy);
//    num2.div(0.5);
//    num3 = curyy;
//    num3.mul(cury2);
//
//    num = num1;
//    num.add(num2);
//    num.add(num3);
//
//    den = curx2;
//    den.add(cury2);
//    den.power(1.5);
//
//    cur = num;
//    cur.div(den);
//    cur.write((char *) "cur.ifs");
//    radius.div(cur);
//    radius.write((char *) "radius.ifs");

    imgDx.diffx();
    imgDy.diffy();

    imgDx.convl((float **) kernel, 3, 3);
    imgDy.convl((float **) kernel, 3, 3);
    temp = imgDx;
    temp.mul(temp);
    imgGrad.add(temp);
    temp = imgDy;
    temp.mul(temp);
    imgGrad.add(temp);
    imgGrad.power(0.5);
    imgGrad.write((char *) "imgGrad.ifs");

    //imgGrad.convl((float **) kernel, 3, 3);

#if 0
    for (int i = 0; i < img.row; i++) {
        for (int j = 0; j < img.col; j++) {
            if (20 < imgGrad.img[i][j]) {
                double slope = 0;

                if (0 != imgDx.img[i][j]) {
                    slope = imgDy.img[i][j] / imgDx.img[i][j];
                } else {
                    slope = imgDy.img[i][j] / 0.1;
                }

//                for (int iLine = 0; iLine < img.row; iLine++) {
//                    for (int jLine = 0; jLine < img.col; jLine++) {
//                        double dx = 0, dy = 0, curSlope = 0, curDiff;
//                        dy = jLine - j;
//                        dx = iLine - i;
//
//                        if (0 != dx) {
//                            curSlope = dy / dx;
//                        } else {
//                            curSlope = dy / 0.0001;
//                        }
//
//                        if (0 >= curSlope) {
//                            curSlope = curSlope * -1;
//                        }
//
//                        if (0 >= slope) {
//                            slope = slope * -1;
//                        }
//                        curDiff = (curSlope - slope);
//
//
//                        if (0 >= curDiff) {
//                            curDiff = curDiff * -1;
//                        }
//
//                        double radi = 0;
//                        radi = sqrt(pow((iLine - i), 2) + pow((jLine - j), 2));
//                        if (0.4 >= curDiff /*&& 0.3 >= (radi - radius.img[i][j])*/) {
//                            accumulator.img[iLine][jLine] += 1;
//                            if ((1 < iLine) && (img.row - 1 > iLine) && (1 < jLine) && (img.col - 1 > jLine)) {
//                                accumulator.img[iLine + 1][img.col - jLine]++;
//                                accumulator.img[iLine + 1][img.col - jLine + 1]++;
//                                accumulator.img[iLine + 1][img.col - jLine - 1]++;
//                                accumulator.img[iLine - 1][img.col - jLine]++;
//                                accumulator.img[iLine - 1][img.col - jLine + 1]++;
//                                accumulator.img[iLine - 1][img.col - jLine - 1]++;
//                                accumulator.img[iLine][img.col - jLine]++;
//                                accumulator.img[iLine][img.col - jLine + 1]++;
//                                accumulator.img[iLine][img.col - jLine - 1]++;
//                            }
//                        }
//                    }
//                }

                if (-1.3 <= slope && 1.3 >= slope)
                {
                    for (int iLine = 0; iLine < img.row; iLine++) {

                        int jLine = 0;
                        jLine = -slope * (iLine - i) - j;
                        //cout << jLine <<endl;
                        jLine = jLine * -1;
                        if ((1 <= jLine) && (img.col - 1 > jLine)) {
                            accumulator.img[iLine][jLine] += 1;
                            if (1 < iLine && img.row - 1 > iLine) {
                                accumulator.img[iLine + 1][jLine]++;
                                accumulator.img[iLine + 1][jLine + 1]++;
                                accumulator.img[iLine + 1][jLine - 1]++;
                                accumulator.img[iLine - 1][jLine]++;
                                accumulator.img[iLine - 1][jLine + 1]++;
                                accumulator.img[iLine - 1][jLine - 1]++;
                                accumulator.img[iLine][jLine]++;
                                accumulator.img[iLine][jLine + 1]++;
                                accumulator.img[iLine][jLine - 1]++;
                            }

                        }
                    }
                }

                if (-0.7 >= slope || 0.7 <= slope)
                {
                    for (int jLine = 0; jLine < img.col; jLine++) {
                        int iLine = 0;
                        if (0 != slope) {
                            iLine = ((jLine - j) / slope) + i;
                        } else {
                            iLine = ((jLine - j) / 0.001) + i;
                        }
                        if (1 <= iLine && img.row - 2 > iLine) {
                            accumulator.img[iLine][jLine] += 1;
                            if ((1 <= jLine) && (img.col - 1 > jLine)) {
                                accumulator.img[iLine + 1][jLine]++;
                                accumulator.img[iLine + 1][jLine + 1]++;
                                accumulator.img[iLine + 1][jLine - 1]++;
                                accumulator.img[iLine - 1][jLine]++;
                                accumulator.img[iLine - 1][jLine + 1]++;
                                accumulator.img[iLine - 1][jLine - 1]++;
                                accumulator.img[iLine][jLine]++;
                                accumulator.img[iLine][jLine + 1]++;
                                accumulator.img[iLine][jLine - 1]++;
                            }
                        }
                    }
                }
            }
        }
    }
#else

    ERROR_LOG;
    cout << img.row << " " << img.col << " " << (int) ((img.row + img.col) / 2) << endl;
    int *maxR = new int[(int) ((img.row + img.col) / 2)];
    for (int r = 0; r < (int) ((img.row + img.col) / 2); r++) {
        maxR[r] = 0;
    }

    Image accum(img);
    accum.reset(0);
    ERROR_LOG;
    for (int i = 0; i < img.row; i++) {
        for (int j = 0; j < img.col; j++) {

            for (int iLine = 0; iLine < img.row; iLine++) {
                for (int jLine = 0; jLine < img.col; jLine++) {
                    if (10 < imgGrad.img[iLine][jLine]) {
                        int r = 0;
                        r = (int) sqrt(pow((i - iLine), 2) + pow((j - jLine), 2));
                        if (r < img.row / 2) {
                            maxR[r]++;
                        }

                        //cout << i << " " << j << " " << iLine << " " << jLine << " " << endl;
                    }
                }
            }
            double mean = 0, var = 0;
            for (int r = 0; r < (int) ((img.row + img.col) / 2); r++) {
                mean += maxR[r];
            }
            mean = mean / ((img.row) / 2);
            for (int r = 0; r < (int) ((img.row) / 2); r++) {
                var += pow((maxR[r] - mean), 2);
            }
            accum.img[i][j] = var;
            //cout << i << " " << j << " " << var << " "<<mean <<endl;
            for (int r = 0; r < (int) ((img.row + img.col) / 2); r++) {
                maxR[r] = 0;
            }
        }
    }

    accumulator = accum;
    ERROR_LOG;
    int maxRadius = 0;
    int maxRadiusLocation = 0;
//    for (int r = 0; r < (int) ((img.row + img.col) / 4); r++) {
//        cout << "max ra" << maxR[r] << " " << r << endl;
//        ;
//        if (maxRadius < maxR[r]) {
//            maxRadius = maxR[r];
//            maxRadiusLocation = r;
//            //cout << "max ra" << maxR[r] << " " << maxRadiusLocation;
//        }
//    }

//maxRadiusLocation = 100;
//    for (int i = 0; i < img.row; i++) {
//        for (int j = 0; j < img.col; j++) {
//            if (20 < imgGrad.img[i][j]) {
//                for (int iLine = 0; iLine < img.row; iLine++) {
//                    for (int jLine = 0; jLine < img.col; jLine++) {
//                        double r = (int) sqrt(pow((i - iLine), 2) + pow((j - jLine), 2));
//                        if ((maxRadiusLocation > (r - 2)) && (maxRadiusLocation < (r + 2))) {
//                            if (1 <= iLine && img.row - 2 > iLine) {
//                                accumulator.img[iLine][jLine] += 1;
//                                if ((1 <= jLine) && (img.col - 1 > jLine)) {
//                                    accumulator.img[iLine + 1][jLine]++;
//                                    accumulator.img[iLine + 1][jLine + 1]++;
//                                    accumulator.img[iLine + 1][jLine - 1]++;
//                                    accumulator.img[iLine - 1][jLine]++;
//                                    accumulator.img[iLine - 1][jLine + 1]++;
//                                    accumulator.img[iLine - 1][jLine - 1]++;
//                                    accumulator.img[iLine][jLine]++;
//                                    accumulator.img[iLine][jLine + 1]++;
//                                    accumulator.img[iLine][jLine - 1]++;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }

//    for (int i = 0; i < img.row; i++) {
//        for (int j = 0; j < img.col; j++) {
//            if (20 < imgGrad.img[i][j]) {
//                for (int iLine = 0; iLine < img.row; iLine++) {
//                    for (int jLine = 0; jLine < img.col; jLine++) {
//                        if (20 < imgGrad.img[i][j]) {
//                            for (int iLi = 0; iLi < img.row; iLi++) {
//                                for (int jLi = 0; jLi < img.col; jLi++) {
//                                    double d1 = sqrt(pow((iLi - i), 2) + pow((jLi - j), 2));
//                                    double d2 = sqrt(pow((iLi - iLine), 2) + pow((jLi - jLine), 2));
//                                    if ((-1) < (llabs(d1 - d2)) && (1) > (llabs(d2 - d1))) {
//                                        if ((1 <= iLi) && (img.row - 2 > iLi) && (1 <= jLi) && (img.col - 2 > jLi)) {
//                                            accumulator.img[iLi + 1][jLi]++;
//                                            accumulator.img[iLi + 1][jLi + 1]++;
//                                            accumulator.img[iLi + 1][jLi - 1]++;
//                                            accumulator.img[iLi - 1][jLi]++;
//                                            accumulator.img[iLi - 1][jLi + 1]++;
//                                            accumulator.img[iLi - 1][jLi - 1]++;
//                                            accumulator.img[iLi][jLi] += 2;
//                                            accumulator.img[iLi][jLi + 1]++;
//                                            accumulator.img[iLi][jLi - 1]++;
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }

#endif
    //accumulator.convl((float **) kernel, 3, 3);
    //accumulator.convl((float **) kernel, 3, 3);
    //accumulator.convl((float **) kernel, 3, 3);
    accumulator.write((char*) "accumulator.ifs");
    cout << endl;
    for (int i = 0; i < img.row; i++) {
        for (int j = 0; j < img.col; j++) {
             cout << (int)accumulator.img[i][j] << " ";
        }
        cout << endl;
    }

    double max = 0;
    int maxX = 0, maxY = 0;
    for (int i = 0; i < img.row; i++) {
        for (int j = 0; j < img.col; j++) {
            if (max < accumulator.img[i][j]) {
                maxX = i;
                maxY = j;
                max = accumulator.img[i][j];
            }
        }
    }
    cout << endl << maxX << " " << maxY << endl;
    return 0;

}

