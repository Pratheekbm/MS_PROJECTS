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

typedef enum _imgerr {
    FAIL = -1, SUCCESS = 0
} imgerr;

class Image {
protected:
    IFSIMG img; /*Declare pointers to headers */
public:
    int dimension;
    int row;
    int col;

    Image(int dim, int _row, int _col);
    Image(const Image &obj);
    ~Image();
    imgerr read(char*);
    imgerr write(char*);
    imgerr convl(float **kernel, int kernelX, int kernelY);
    double getValue(int _row, int _col);
    imgerr setValue(int _row, int _col, double value);
};

#endif /* INC_IMAGE_H_ */
