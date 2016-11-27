/*
 * image.h
 *
 *  Created on: Jan 24, 2015
 *      Author: pratheek
 */

#ifndef INC_IMAGE_H_
#define INC_IMAGE_H_

#include <stdio.h>
#include "ifs.h"
//#include "flip.h"

typedef enum _imgerr {
    FAIL = -1,
    SUCC = 0
} imgerr;

class Image {
public:
    double **img = NULL; /*Declare pointers to headers */
    int dimension = 0;
    int row = 0;
    int col = 0;

    Image(int dim, int _row, int _col);
    Image(const Image &obj);
    Image(char * fileName);
    ~Image();
    Image & operator=(const Image &obj);
    imgerr reset(double resetTo);
    imgerr read(char*);
    imgerr write(char*);
    imgerr convl(float **kernel, int kernelX, int kernelY);
    double getValue(int _row, int _col);
    imgerr setValue(int _row, int _col, double value);
    imgerr add(const Image &obj);
    imgerr sub(Image inImg);
    imgerr mul(Image inImg);
    imgerr div(double divisor);
    imgerr div(Image divisor);
    imgerr expo();
    imgerr diffx();
    imgerr diffy();
    imgerr centerOfGravity(double &meanX, double &meanY, int shapeValue);
    double etapq(int p, int q, int meanX, int meanY, int area);
    imgerr translate (int x, int y);
    imgerr rotate (float rotationInRad, double meanX, double meanY );
    imgerr power(double pow) ;
};

#endif /* INC_IMAGE_H_ */
