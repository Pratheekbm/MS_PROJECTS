/*
 * image.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: pratheek
 */
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ifs.h"
#include "../inc/image.h"
#include "castTypes.h"
#include"image.h"

using namespace std;

/**********************************************************************************************************************
 * FUNCTION		: Image
 * CLASS		: Image
 * TYPE			: Constructor
 * IN			: Dimensions of the Image
 * OUT			: None
 * PROCESS		: Allocates memory for Image data
 *
 *********************************************************************************************************************/
Image::Image(int dim, int _row, int _col) {

    dimension = 0;
    row = 0;
    col = 0;
    img = NULL;

    if (dim <= 0 || _row < 0 || _col < 0) {
        cout << "ER >> Size of the image is negative!" << endl;
        ERROR_LOG;
    } else {
        int len[3];
        dimension = dim;
        row = _row;
        col = _col;

        len[0] = dim; /*image to be created is two dimensional */
        len[1] = _col; /*image has 128 columns */
        len[2] = _row; /*image has 128 rows */

        img = ifscreate((char *) "double", len, IFS_CR_ALL, 0);/*image is unsigned 8bit */
        if (NULL == img) {
            cout << "ER >> ifscreate failed" << endl;
            ERROR_LOG;
        } else {
            // Initialize image to black image
            for (int x = 0; x < row; x++)
                for (int y = 0; y < col; y++) {
                    ifsipp(img, x, y, 0);
                }
        }
    }

    cout << "IN >> Image allocated Successfully" << endl;
}

/**********************************************************************************************************************
 * FUNCTION		: Image
 * CLASS		: Image
 * TYPE			: Copy constructor
 * IN			: copy object
 * OUT			: None
 * PROCESS		: Allocates new img and copies values form old
 *
 *********************************************************************************************************************/
Image::Image(const Image &obj) {

    int len[3];

    this->dimension = obj.dimension;
    this->col = obj.col;
    this->row = obj.row;

    len[0] = this->dimension;
    len[1] = this->col;
    len[2] = this->row;

    this->img = ifscreate((char *) "double", len, IFS_CR_ALL, 0);
    if (NULL == this->img) {
        cout << "ER >> ifscreate failed" << endl;
        ERROR_LOG;
    } else {
        // Initialize image to obj img
        for (int x = 0; x < row; x++)
            for (int y = 0; y < col; y++) {
                ifsipp(this->img, x, y, ifsigp(obj.img, x, y));
            }
    }
    cout << "IN >> Image copied Successfully" << endl;
}
/**********************************************************************************************************************
 * FUNCTION		: ~Image
 * CLASS		: Image
 * TYPE			: Destructor
 * IN			: None
 * OUT			: None
 * PROCESS		: Deallocates memory for Image data
 *
 *********************************************************************************************************************/
Image::~Image() {

    ifsfree(img, IFS_FR_ALL);
    row = 0;
    col = 0;
    dimension = 0;

    cout << "IN >> Image freed Successfully" << endl;
}

/**********************************************************************************************************************
 * FUNCTION		: read
 * CLASS		: Image
 * TYPE			: member function
 * IN			: None
 * OUT			: None
 * PROCESS		: Reads an image from disk
 *
 *********************************************************************************************************************/
imgerr Image::read(char * fileName) {
    if ( NULL == fileName) {
        return FAIL;
    } else {
        img = ifspin((char *) fileName);
    }
    return SUCCESS;
}
/**********************************************************************************************************************
 * FUNCTION		: write
 * CLASS		: Image
 * TYPE			: member function
 * IN			: None
 * OUT			: None
 * PROCESS		: Writes an image to the disk
 *
 *********************************************************************************************************************/
imgerr Image::write(char * fileName) {
    ifspot(img, fileName); /*write image 2 to disk */
    return SUCCESS;
}

/**********************************************************************************************************************
 * FUNCTION		: convl
 * CLASS		: Image
 * TYPE			: member function
 * IN			: Kernel, kernel dimensions
 * OUT			: None
 * PROCESS		: Performs convolution with the given kernel
 *
 *********************************************************************************************************************/
imgerr Image::convl(float **kernel, int kernelX, int kernelY) {
    float sum = 0;
    float kernelSum = 0;
    if ((0 == kernelX % 2) || (0 == kernelY % 2)) {
        cout << "Kernel dimensions should be ODD" << endl;
        ERROR_LOG;
        return FAIL;
    }

    for (int x = 0; x < kernelX; x++) {
        for (int y = 0; y < kernelY; y++) {
            cout << kernel[x][y] << " ";
            kernelSum += llabs(kernel[x][y]);
        }
        cout << endl;
    }
    int boundryX = (kernelX - 1) >> 1;
    int boundryY = (kernelY - 1) >> 1;
    float **tempImage = NULL;

    tempImage = new float*[row]();
    for (int i = 0; i < row; i++) {
        tempImage[i] = new float[col]();
    }

    for (int x = boundryX; x < row - boundryX; x++) {
        for (int y = boundryY; y < col - boundryY; y++) {
            for (int opX = -boundryX; opX <= boundryX; opX++) {
                for (int opY = boundryY; opY >= -boundryY; opY--) {
                    sum += ifsigp(img, x + opX, y - opY) * kernel[opX + boundryX][boundryY - opY];
                }
            }
            tempImage[x][y] = sum / kernelSum;
            sum = 0;
        }
    }

    for (int x = boundryX; x < row - boundryX; x++) {
        for (int y = boundryY; y < col - boundryY; y++) {
            ifsipp(img, x, y, tempImage[x][y]);
        }
    }

    for (int i = 0; i < row; i++) {
        delete[] tempImage[i];
    }
    delete[] tempImage;

    return SUCCESS;
}

/**********************************************************************************************************************
 * FUNCTION		: getValue
 * CLASS		: Image
 * TYPE			: member function
 * IN			: row, col
 * OUT			: None
 * PROCESS		: Return image value at row, col
 *
 *********************************************************************************************************************/
double Image::getValue(int _row, int _col) {
    return ifsigp(img, _row, _col);
}

/**********************************************************************************************************************
 * FUNCTION		: setValue
 * CLASS		: Image
 * TYPE			: member function
 * IN			: value, row, col
 * OUT			: None
 * PROCESS		: Sets image value at row, col with input value
 *
 *********************************************************************************************************************/
imgerr Image::setValue(int _row, int _col, double value) {

    ifsipp(img, _row, _col, value);
    return SUCCESS;
}

/* Nothing beyond this */
