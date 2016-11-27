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
#include <limits.h>
#include "ifs.h"
#include "flip.h"
#include "castTypes.h"
#include "image.h"
using namespace std;

#define PI 3.14159265
#define POINTS 18
//char *name1 = "EB1_1.ifs";
//char *name2 = "EB1_2.ifs";
//char *name1 = "Hamlet1.ifs";
//char *name2 = "Hamlet2.ifs";
char *name1 = "CV1.ifs";
char *name2 = "CV2.ifs";

int main() {

//    Image img1((char *) "EB1_1.ifs");
//    Image img2((char *) "EB1_2.ifs");
    Image img1((char *) name1);
    Image img2((char *) name2);
    double **A = dmatrix(1, 2 * POINTS, 1, 8);
    double **At = dmatrix(1, 8, 1, 2 * POINTS);
    double **D = dmatrix(1, 2 * POINTS, 1, 1);
    double **AtA = dmatrix(1, 8, 1, 8);
    double **AtAinv = dmatrix(1, 8, 1, 8);
    double **AtAinvAt = dmatrix(1, 8, 1, 2 * POINTS);
    double **AtAinvAtD = dmatrix(1, 8, 1, 1);
    double **Hm = dmatrix(1, 3, 1, 3);
    double **H1 = dmatrix(1, 3, 1, 3);
    double **Hinv1 = dmatrix(1, 3, 1, 3);
    double H[3][3], Hinv[3][3];
    int xp = 0;
    int yp = 0;

    cout << sizeof(long double) << endl;
    cout << sizeof(int*) << endl;

//EB1
//    int imgx[POINTS] = { 716, 736, 794, 874, 1011, 878, 1014, 1597, 1552, 908, 1035, 909, 1035, 1018, 1106, 1867, 1603,
//            1466 };
//    int imgy[POINTS] = { 1294, 1802, 1802, 1404, 1402, 1700, 1700, 2095, 1281, 1903, 1904, 2011, 2013, 2780, 2926, 3174,
//            1854, 2610 };
//    int imgxp[POINTS] = { 588, 682, 746, 782, 937, 821, 969, 1548, 1557, 875, 1009, 888, 1018, 1054, 1141, 1808, 1605,
//            1462 };
//    int imgyp[POINTS] = { 98, 718, 717, 232, 223, 595, 590, 757, 28, 826, 822, 942, 939, 1645, 1758, 1886, 732, 1486 };

//hamlet
//    int imgx[POINTS] = { 186, 190, 209, 177, 502, 285, 244, 294, 457, 209, 351, 386, 178, 168, 467, 216, 236, 263 };
//    int imgy[POINTS] =
//            { 553, 600, 649, 766, 690, 679, 840, 807, 841, 970, 944, 951, 1069, 1095, 1092, 1261, 1242, 1265 };
//    int imgxp[POINTS] = { 187, 190, 211, 177, 502, 286, 244, 294, 458, 209, 352, 386, 179, 169, 468, 216, 236, 264 };
//    int imgyp[POINTS] = { 53, 100, 149, 266, 191, 179, 339, 307, 341, 471, 444, 451, 568, 595, 592, 761, 741, 764 };

//CV
    int imgx[POINTS] = { 1355, 1373, 1018, 811, 624, 1015, 364, 283, 598, 584, 878, 496, 748, 1378, 1725, 2118, 1845,
            2081 };
    int imgy[POINTS] = { 1603, 1369, 1518, 1693, 1887, 1886, 2197, 2397, 2265, 2691, 2703, 2913, 3017, 2289, 2886, 2824,
            3233, 3088 };
    int imgxp[POINTS] = { 1370, 1390, 1029, 849, 650, 1030, 406, 338, 634, 631, 897, 555, 793, 1392, 1718, 2098, 1829,
            2056 };
    int imgyp[POINTS] = { 323, 90, 231, 397, 590, 598, 876, 1062, 950, 1340, 1343, 1539, 1640, 994, 1549, 1500, 1866,
            1743 };
    Image img1dx = img1, img1dy = img1;
    Image img2dx = img2, img2dy = img2;

    img1dx.diffx();
    img1dy.diffy();
    img2dx.diffx();
    img2dy.diffy();

    img1dx.mul(img1dx);
    img1dy.mul(img1dy);
    img2dx.mul(img2dx);
    img2dy.mul(img2dy);

    img1.reset(0);
    img2.reset(0);

    img1.add(img1dx);
    img1.add(img1dy);
    img2.add(img2dx);
    img2.add(img2dy);
    img1.power(0.5);
    img2.power(0.5);

    img1.write((char *) "img1grad.ifs");
    img2.write((char *) "img2grad.ifs");

    int range = 5;
    double matrix[POINTS][range * 2 + 1][range * 2 + 1];
    for (int i = 0; i < POINTS; i++) {
        double error = 0;
        for (int j = -range; j <= range; j++) {
            for (int k = -range; k <= range; k++) {
                //cout << i << " " << j << " " << k << endl;
                int ix = imgx[i];
                int iy = imgy[i];
                int ixp = imgxp[i] + j;
                int iyp = imgyp[i] + k;

                error = pow(img1.img[ix - 1][iy - 1] - img2.img[ixp - 1][iyp - 1], 2);
                error += pow(img1.img[ix - 1][iy] - img2.img[ixp - 1][iyp], 2);
                error += pow(img1.img[ix - 1][iy + 1] - img2.img[ixp - 1][iyp + 1], 2);
                error += pow(img1.img[ix][iy - 1] - img2.img[ixp][iyp - 1], 2);
                error += pow(img1.img[ix][iy] - img2.img[ixp][iyp], 2);
                error += pow(img1.img[ix][iy + 1] - img2.img[ixp][iyp + 1], 2);
                error += pow(img1.img[ix + 1][iy - 1] - img2.img[ixp + 1][iyp - 1], 2);
                error += pow(img1.img[ix + 1][iy] - img2.img[ixp + 1][iyp], 2);
                error += pow(img1.img[ix + 1][iy + 1] - img2.img[ixp + 1][iyp + 1], 2);
                matrix[i][j + range][k + range] = error;
                error = 0;
            }
        }
    }

    for (int i = 0; i < POINTS; i++) {
        int min = 0x0fffffff;
        int minx = 0;
        int miny = 0;
        for (int j = 0; j <= 2 * range; j++) {
            for (int k = 0; k <= 2 * range; k++) {
                if (matrix[i][j][k] <= min) {
                    min = matrix[i][j][k];
                    minx = j;
                    miny = k;
                }
            }
        }
        imgxp[i] = imgxp[i] + (minx - range);
        imgyp[i] = imgyp[i] + (miny - range);
    }

    for (int i = 0; i < POINTS; i++) {
        cout << imgxp[i] << " " << imgyp[i] << endl;
    }

    for (int i = 1; i <= 2 * POINTS; i++) {
        int loc = (i - 1) / 2;
        A[i][1] = 0;
        A[i][2] = 0;
        A[i][3] = 0;
        A[i][4] = -imgx[loc];
        A[i][5] = -imgy[loc];
        A[i][6] = -1;
        A[i][7] = imgx[loc] * imgyp[loc];
        A[i][8] = imgy[loc] * imgyp[loc];

        D[i][1] = -imgyp[loc];

        i = i + 1;

        A[i][1] = imgx[loc];
        A[i][2] = imgy[loc];
        A[i][3] = 1;
        A[i][4] = 0;
        A[i][5] = 0;
        A[i][6] = 0;
        A[i][7] = -imgx[loc] * imgxp[loc];
        A[i][8] = -imgy[loc] * imgxp[loc];

        D[i][1] = imgxp[loc];
    }

    dtranspose(A, 2 * POINTS, 8, At);
    ifsdmatmult(At, A, AtA, 8, 2 * POINTS, 2 * POINTS, 8);
    ifsinverse(AtA, AtAinv, 8);
    ifsdmatmult(AtAinv, At, AtAinvAt, 8, 8, 8, 2 * POINTS);
    ifsdmatmult(AtAinvAt, D, AtAinvAtD, 8, 2 * POINTS, 2 * POINTS, 1);

    H1[1][1] = AtAinvAtD[1][1];
    H1[1][2] = AtAinvAtD[2][1];
    H1[1][3] = AtAinvAtD[3][1];
    H1[2][1] = AtAinvAtD[4][1];
    H1[2][2] = AtAinvAtD[5][1];
    H1[2][3] = AtAinvAtD[6][1];
    H1[3][1] = AtAinvAtD[7][1];
    H1[3][2] = AtAinvAtD[8][1];
    H1[3][3] = 1;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            Hm[i][j] = H1[i][j];
        }
    }
    ifsinverse(Hm, Hinv1, 3);

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            H[i - 1][j - 1] = H1[i][j];
            Hinv[i - 1][j - 1] = Hinv1[i][j];
        }
    }

//    double H[3][3] = { { 0.001135989131536, 0.000172062433909, -0.346203839824822 }, { -0.000199393998029,
//            0.001302967228997, -1.362664235329036 }, { -0.000000033880075, 0.000000101293835, 0.001000000000000 } };
//
//    double Hinv[3][3] = { { 0.008623983111858, -0.001239622588391, 1.296466701403721 }, { 0.001469618436192,
//            0.006728396203896, 9.677332413859368 }, { 0.000000143317910, -0.000000723543565, 0.009063670271996 } };

    int minx = 0, miny = 0;
    int maxx = img1.row, maxy = img1.col;

    for (int i = 0; i < img1.row; i++) {
        for (int j = 0; j < img1.col; j++) {
            float w = 0;
            w = H[2][0] * i + H[2][1] * j + H[2][2];
            xp = (H[0][0] * i + H[0][1] * j + H[0][2]) / w;
            yp = (H[1][0] * i + H[1][1] * j + H[1][2]) / w;
            if (xp < minx) {
                minx = xp;
            }
            if (yp < miny) {
                miny = yp;
            }
            if (xp > maxx) {
                maxx = xp;
            }
            if (yp > maxy) {
                maxy = yp;
            }
        }
    }

    Image pano(2, maxx - minx, maxy - miny);

    IFSIMG panorgb, img1rgb, img2rgb;
    int len[4];
    len[0] = 3;
    len[1] = maxy - miny;
    len[2] = maxx - minx;
    len[3] = 3;
    panorgb = ifscreate((char *) "double", len, IFS_CR_ALL, 0);
    img1rgb = ifspin((char *) name1);
    img2rgb = ifspin((char *) name2);

    for (int i = 0; i < pano.row; i++) {
        for (int j = 0; j < pano.col; j++) {
            int x = 0, y = 0;
            x = i + minx;
            y = j + miny;

            float w = 0;

            w = Hinv[2][0] * x + Hinv[2][1] * y + Hinv[2][2];
            xp = (Hinv[0][0] * x + Hinv[0][1] * y + Hinv[0][2]) / w;
            yp = (Hinv[1][0] * x + Hinv[1][1] * y + Hinv[1][2]) / w;

            if ((0 <= xp) && (img1.row > xp) && (0 <= yp) && (img1.col > yp)) {
                pano.img[i][j] = img1.img[xp][yp];
                ifsfpp3d(panorgb, 0, i, j, ifsfgp3d(img1rgb, 0, xp, yp));
                ifsfpp3d(panorgb, 1, i, j, ifsfgp3d(img1rgb, 1, xp, yp));
                ifsfpp3d(panorgb, 2, i, j, ifsfgp3d(img1rgb, 2, xp, yp));
            }

        }
    }

    cout << img1.row << " " << img1.col << " " << img2.row << " " << img2.col;
    for (int i = 0; i < img2.row; i++) {
        for (int j = 0; j < img2.col; j++) {
            xp = i - minx;
            yp = j - miny;
            if ((0 <= xp) && (pano.row > xp) && (0 <= yp) && (pano.col > yp)) {
                pano.img[xp][yp] = img2.img[i][j];
                ifsfpp3d(panorgb, 0, xp, yp, ifsfgp3d(img2rgb, 0, i, j));
                ifsfpp3d(panorgb, 1, xp, yp, ifsfgp3d(img2rgb, 1, i, j));
                ifsfpp3d(panorgb, 2, xp, yp, ifsfgp3d(img2rgb, 2, i, j));
            } else {
                cout << xp << " " << yp << endl;
                //ERROR_LOG;
            }
        }
    }

    cout << endl << minx << " " << miny << " " << maxx << " " << maxy;
    pano.write((char*) "pano.ifs");
    ifspot(img1rgb, (char*) "img1rgb.ifs");
    ifspot(img2rgb, (char*) "img2rgb.ifs");
    ifspot(panorgb, (char*) "panorgb.ifs");
    cout << endl << minx << " " << miny << " " << maxx << " " << maxy;
    return 0;

}

