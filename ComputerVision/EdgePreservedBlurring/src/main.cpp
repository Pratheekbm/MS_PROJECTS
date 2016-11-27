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

    char *a = "angio.ifs";
    Image temp((char *) a);
    int len[3];
    len[0] = 2;//temp.dimension;
    len[1] = temp.col;
    len[2] = temp.row;
    Image givenImage(len[0], len[2], len[1]);
    givenImage.read((char *) a);

    Image tem(givenImage),c(givenImage), cdx(givenImage), cdy(givenImage), givenImageX(givenImage), givenImageY(givenImage),
            givenImageXPlusY(givenImage);

    for (int i = 0; i < 50; i++) {
        cout << i << endl;
        cdx = givenImage;
        cdy = givenImage;
        givenImageX = givenImage;
        givenImageY = givenImage;
        c.reset(0);
        givenImageXPlusY.reset(0);


        cdx.diffx();
        cdy.diffy();
        cdx.mul(cdx);
        cdy.mul(cdy);
        c.add(cdx);
        c.add(cdy);
        c.div(-5);
        c.expo();
        givenImageX.diffx();
        givenImageY.diffy();
        givenImageX.mul(c);
        givenImageY.mul(c);
        givenImageX.diffx();
        givenImageY.diffy();
        givenImageXPlusY.add(givenImageX);
        givenImageXPlusY.add(givenImageY);

        givenImageXPlusY.div(10);

        givenImage.add(givenImageXPlusY);
    }

    tem.sub(givenImage);
    givenImage.write((char *) "givenImageBlurred.ifs");
    return 0;
}

