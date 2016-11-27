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

    Image bright((char *) "b0.ifs");
    Image depth((char *) "d_box1c.ifs");

    Image brightDx = bright;
    Image brightDy = bright;
    Image brightEdge = bright;
    brightEdge.reset(0);

    Image depthDx = depth;
    Image depthDy = depth;
    Image depthEdge = depth;
    depthEdge.reset(0);

    brightDx.diffx();
    brightDy.diffy();
    brightDx.mul(brightDx);
    brightDy.mul(brightDy);
    brightEdge.add(brightDx);
    brightEdge.add(brightDy);

    depthDx.diffx();
    depthDy.diffy();
    depthDx.mul(depthDx);
    depthDy.mul(depthDy);
    depthEdge.add(depthDx);
    depthEdge.add(depthDy);

    brightEdge.write("diffBright.ifs");
    depthEdge.write("diffDepth.ifs");

    return 0;

}

