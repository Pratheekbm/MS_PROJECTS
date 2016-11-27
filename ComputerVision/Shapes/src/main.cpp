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
#include "flip.h"
#include "castTypes.h"
#include "image.h"
using namespace std;

int main() {

    Image img((char *) "blob.ifs");

    Image temp = img;
    double meanX = 0, meanY = 0;
    double eta00 = 0, eta20 = 0, eta02 = 0, eta11 = 0, eta30 = 0, eta12 = 0, eta21 = 0, eta03 = 0;
    double pi1 = 0, pi2 = 0, pi3 = 0;

    img.centerOfGravity(meanX, meanY, 0);
    eta00 = img.etapq(0, 0, meanX, meanY, 1);
    cout << "Original Image" << endl;

    eta20 = img.etapq(2, 0, meanX, meanY, eta00);
    eta02 = img.etapq(0, 2, meanX, meanY, eta00);
    eta11 = img.etapq(1, 1, meanX, meanY, eta00);
    eta30 = img.etapq(3, 0, meanX, meanY, eta00);
    eta12 = img.etapq(1, 2, meanX, meanY, eta00);
    eta21 = img.etapq(2, 1, meanX, meanY, eta00);
    eta03 = img.etapq(0, 3, meanX, meanY, eta00);

    pi1 = eta20 + eta02;
    pi2 = pow(eta20 + eta02, 2) + 4 * eta11 * eta11;
    pi3 = pow((eta30 - (3 * eta12)), 2) + pow(((3 * eta21) - eta03), 2);
    cout << "pi1 " << pi1 << endl;
    cout << "pi2 " << pi2 << endl;
    cout << "pi3 " << pi3 << endl;

    img.translate(10, 10);
    cout << "Translated by 10,10 Image" << endl;
    img.centerOfGravity(meanX, meanY, 0);
    eta00 = img.etapq(0, 0, meanX, meanY, 1);

    eta20 = img.etapq(2, 0, meanX, meanY, eta00);
    eta02 = img.etapq(0, 2, meanX, meanY, eta00);
    eta11 = img.etapq(1, 1, meanX, meanY, eta00);
    eta30 = img.etapq(3, 0, meanX, meanY, eta00);
    eta12 = img.etapq(1, 2, meanX, meanY, eta00);
    eta21 = img.etapq(2, 1, meanX, meanY, eta00);
    eta03 = img.etapq(0, 3, meanX, meanY, eta00);

    pi1 = eta20 + eta02;
    pi2 = pow(eta20 + eta02, 2) + 4 * eta11 * eta11;
    pi3 = pow((eta30 - (3 * eta12)), 2) + pow(((3 * eta21) - eta03), 2);
    cout << "pi1 " << pi1 << endl;
    cout << "pi2 " << pi2 << endl;
    cout << "pi3 " << pi3 << endl;

    img.write((char *) "translatedBlob.ifs");

    img = temp;
    cout << "Rotation by 10 degrees Image" << endl;
    img.centerOfGravity(meanX, meanY, 0);
    img.rotate(3.1416 / 18.0, meanX, meanY);

    img.centerOfGravity(meanX, meanY, 0);
    eta00 = img.etapq(0, 0, meanX, meanY, 1);

    eta20 = img.etapq(2, 0, meanX, meanY, eta00);
    eta02 = img.etapq(0, 2, meanX, meanY, eta00);
    eta11 = img.etapq(1, 1, meanX, meanY, eta00);
    eta30 = img.etapq(3, 0, meanX, meanY, eta00);
    eta12 = img.etapq(1, 2, meanX, meanY, eta00);
    eta21 = img.etapq(2, 1, meanX, meanY, eta00);
    eta03 = img.etapq(0, 3, meanX, meanY, eta00);

    pi1 = eta20 + eta02;
    pi2 = pow(eta20 + eta02, 2) + 4 * eta11 * eta11;
    pi3 = pow((eta30 - (3 * eta12)), 2) + pow(((3 * eta21) - eta03), 2);
    cout << "pi1 " << pi1 << endl;
    cout << "pi2 " << pi2 << endl;
    cout << "pi3 " << pi3 << endl;
    img.write((char *) "rotate10Blob.ifs");

    cout << "Rotation by 20 degrees Image" << endl;
    img = temp;
    img.centerOfGravity(meanX, meanY, 0);
    img.rotate(3.1416 / 9.0, meanX, meanY);

    img.centerOfGravity(meanX, meanY, 0);
    eta00 = img.etapq(0, 0, meanX, meanY, 1);

    eta20 = img.etapq(2, 0, meanX, meanY, eta00);
    eta02 = img.etapq(0, 2, meanX, meanY, eta00);
    eta11 = img.etapq(1, 1, meanX, meanY, eta00);
    eta30 = img.etapq(3, 0, meanX, meanY, eta00);
    eta12 = img.etapq(1, 2, meanX, meanY, eta00);
    eta21 = img.etapq(2, 1, meanX, meanY, eta00);
    eta03 = img.etapq(0, 3, meanX, meanY, eta00);

    pi1 = eta20 + eta02;
    pi2 = pow(eta20 + eta02, 2) + 4 * eta11 * eta11;
    pi3 = pow((eta30 - (3 * eta12)), 2) + pow(((3 * eta21) - eta03), 2);
    cout << "pi1 " << pi1 << endl;
    cout << "pi2 " << pi2 << endl;
    cout << "pi3 " << pi3 << endl;
    img.write((char *) "rotate20Blob.ifs");

    cout << "Rotation by 30 degrees Image" << endl;
    img = temp;
    img.centerOfGravity(meanX, meanY, 0);
    img.rotate(3.1416 / 6.0, meanX, meanY);

    img.centerOfGravity(meanX, meanY, 0);
    eta00 = img.etapq(0, 0, meanX, meanY, 1);
    cout << "eta00 " << eta00 << endl;

    eta20 = img.etapq(2, 0, meanX, meanY, eta00);
    eta02 = img.etapq(0, 2, meanX, meanY, eta00);
    eta11 = img.etapq(1, 1, meanX, meanY, eta00);
    eta30 = img.etapq(3, 0, meanX, meanY, eta00);
    eta12 = img.etapq(1, 2, meanX, meanY, eta00);
    eta21 = img.etapq(2, 1, meanX, meanY, eta00);
    eta03 = img.etapq(0, 3, meanX, meanY, eta00);

    pi1 = eta20 + eta02;
    pi2 = pow(eta20 + eta02, 2) + 4 * eta11 * eta11;
    pi3 = pow((eta30 - (3 * eta12)), 2) + pow(((3 * eta21) - eta03), 2);
    cout << "pi1 " << pi1 << endl;
    cout << "pi2 " << pi2 << endl;
    cout << "pi3 " << pi3 << endl;
    img.write((char *) "rotate30Blob.ifs");

    return 0;

}

