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
#include "flip.h"
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
        dimension = dim;
        row = _row;
        col = _col;

        img = new double*[row];

        for (int i = 0; i < row; i++)
            img[i] = new double[col];

        if (NULL == img) {
            cout << "ER >> Memory allocation failed" << endl;
            ERROR_LOG;
        } else {
            // Initialize image to black image
            for (int x = 0; x < row; x++) {
                for (int y = 0; y < col; y++) {
                    img[x][y] = 0;
                }
            }
        }
    }
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

    this->dimension = obj.dimension;
    this->col = obj.col;
    this->row = obj.row;

    this->img = new double*[row];

    for (int i = 0; i < row; i++)
        this->img[i] = new double[col];

    if (NULL == img) {
        cout << "ER >> Memory allocation failed" << endl;
        ERROR_LOG;
    } else {
        // Initialize image to black image
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                this->img[x][y] = obj.img[x][y];
            }
        }
    }
}
/**********************************************************************************************************************
 * FUNCTION     : Image
 * CLASS        : Image
 * TYPE         : Constructor
 * IN           : None
 * OUT          : None
 * PROCESS      : Reads an image from disk
 *
 *********************************************************************************************************************/
Image::Image(char * fileName) {
    if ( NULL == fileName) {
        ERROR_LOG;
    } else {
        IFSIMG temp;
        int *len;
        temp = ifspin((char *) fileName);
        len = ifssiz(temp);
        dimension = len[0];
        col = len[1];
        row = len[2];

        img = new double*[row];

        for (int i = 0; i < row; i++)
            img[i] = new double[col];

        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                img[x][y] = ifsigp(temp, x, y);
            }
        }
    }
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

    if (NULL != img) {
        for (int i = 0; i < row; i++) {
            delete[] img[i];
            img[i] = NULL;
        }
        delete[] img;
        img = NULL;
    }

    row = 0;
    col = 0;
    dimension = 0;
}
/**********************************************************************************************************************
 * FUNCTION     : =
 * CLASS        : Image
 * TYPE         : object copy operator
 * IN           : copy object
 * OUT          : None
 * PROCESS      : Allocates new img and copies values form old
 *
 *********************************************************************************************************************/
Image & Image::operator=(const Image &obj) {

    if (NULL != img) {
        for (int i = 0; i < row; i++) {
            delete[] img[i];
            img[i] = NULL;
        }
        delete[] img;
        img = NULL;
    }

    this->dimension = obj.dimension;
    this->col = obj.col;
    this->row = obj.row;

    this->img = new double*[row];

    for (int i = 0; i < row; i++)
        this->img[i] = new double[col];

    if (NULL == img) {
        cout << "ER >> Memory allocation failed" << endl;
        ERROR_LOG;
    } else {
        // Initialize image to black image
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                this->img[x][y] = obj.img[x][y];
            }
        }
    }

    return *this;
}
/**********************************************************************************************************************
 * FUNCTION     : reset
 * CLASS        : Image
 * TYPE         : member function
 * IN           : None
 * OUT          : None
 * PROCESS      : Reads an image from disk
 *
 *********************************************************************************************************************/
imgerr Image::reset(double resetTo) {
    if ( NULL == img) {
        return FAIL;
    } else {
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                img[x][y] = resetTo;
            }
        }
    }
    return SUCC;
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
        int *len;
        IFSIMG temp;
        temp = ifspin((char *) fileName);
        len = ifssiz(temp);

        if (NULL != img) {
            for (int i = 0; i < row; i++) {
                delete[] img[i];
                img[i] = NULL;
            }
            delete[] img;
            img = NULL;
        }

        dimension = len[0];
        col = len[1];
        row = len[2];

        this->img = new double*[row];

        for (int i = 0; i < row; i++)
            this->img[i] = new double[col];

        if (NULL == img) {
            cout << "ER >> Memory allocation failed" << endl;
            ERROR_LOG;
        } else {
            // Initialize image to black image
            for (int x = 0; x < row; x++) {
                for (int y = 0; y < col; y++) {
                    this->img[x][y] = ifsigp(temp, x, y);
                }
            }
        }
    }
    return SUCC;
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
    IFSIMG temp;
    int len[3];
    len[0] = dimension; /*image to be created is two dimensional */
    len[1] = col; /*image has 128 columns */
    len[2] = row; /*image has 128 rows */

    temp = ifscreate((char *) "double", len, IFS_CR_ALL, 0);/*image is unsigned 8bit */
    if (NULL == temp) {
        cout << "ER >> ifscreate failed" << endl;
        ERROR_LOG;
    } else {
        // Initialize image to black image
        for (int x = 0; x < row; x++)
            for (int y = 0; y < col; y++) {
                ifsipp(temp, x, y, img[x][y]);
            }
    }

    ifspot(temp, fileName); /*write image 2 to disk */
    return SUCC;
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
            kernelSum += llabs(kernel[x][y]);
        }
    }
    int boundryX = (kernelX - 1) >> 1;
    int boundryY = (kernelY - 1) >> 1;
    double **tempImage = NULL;

    tempImage = new double*[row]();
    for (int i = 0; i < row; i++) {
        tempImage[i] = new double[col]();
    }

    for (int x = boundryX; x < row - boundryX; x++) {
        for (int y = boundryY; y < col - boundryY; y++) {
            for (int opX = -boundryX; opX <= boundryX; opX++) {
                for (int opY = boundryY; opY >= -boundryY; opY--) {
                    sum += img[x + opX][y - opY] * kernel[opX + boundryX][boundryY - opY];
                }
            }
            tempImage[x][y] = sum / kernelSum;
            sum = 0;
        }
    }

    for (int x = boundryX; x < row - boundryX; x++) {
        for (int y = boundryY; y < col - boundryY; y++) {
            img[x][y] = tempImage[x][y];
        }
    }

    for (int i = 0; i < row; i++) {
        delete[] tempImage[i];
    }
    delete[] tempImage;

    return SUCC;
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
    return img[_row][_col];
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

    img[_row][_col] = value;
    return SUCC;
}

/**********************************************************************************************************************
 * FUNCTION     : add
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image
 * OUT          : None
 * PROCESS      : Adds input image to current image
 *
 *********************************************************************************************************************/
imgerr Image::add(const Image &inImg) {

    if ((this->row == inImg.row) && (this->col == inImg.col) && (this->dimension == inImg.dimension)) {
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                img[x][y] = img[x][y] + inImg.img[x][y];
            }
        }
    } else {
        ERROR_LOG;
        return FAIL;
    }
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : sub
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image
 * OUT          : None
 * PROCESS      : Subtracts input image from current image
 *
 *********************************************************************************************************************/
imgerr Image::sub(Image inImg) {

    if ((this->row == inImg.row) && (this->col == inImg.col) && (this->dimension == inImg.dimension)) {
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                img[x][y] = img[x][y] - inImg.img[x][y];
            }
        }
    } else {
        ERROR_LOG;
        return FAIL;
    }
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : mul
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image
 * OUT          : None
 * PROCESS      : multiplies current image by input image
 *
 *********************************************************************************************************************/
imgerr Image::mul(Image inImg) {

    if ((this->row == inImg.row) && (this->col == inImg.col) && (this->dimension == inImg.dimension)) {
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                img[x][y] = img[x][y] * inImg.img[x][y];
            }
        }
    } else {
        ERROR_LOG;
        return FAIL;
    }
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : div
 * CLASS        : Image
 * TYPE         : member function
 * IN           : divisor
 * OUT          : None
 * PROCESS      : divides current image by divisor
 *
 *********************************************************************************************************************/
imgerr Image::div(double divisor) {

    if (0 != divisor) {
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                img[x][y] = img[x][y] / divisor;
            }
        }
    } else {
        ERROR_LOG;
        return FAIL;
    }
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : exp
 * CLASS        : Image
 * TYPE         : member function
 * IN           : divisor
 * OUT          : None
 * PROCESS      : calculates the exponential of each pixel
 *
 *********************************************************************************************************************/
imgerr Image::expo() {

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            img[x][y] = exp(img[x][y]);
        }
    }
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : diffx
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image
 * OUT          : None
 * PROCESS      : Differentiates current image in x direction
 *
 *********************************************************************************************************************/
imgerr Image::diffx() {
    float **kernel;
    float hx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    kernel = new float*[3];

    for (int i = 0; i < 3; i++)
        kernel[i] = new float[3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = hx[i][j];
        }
    }

    convl((float **) kernel, 3, 3);

    for (int i = 0; i < 3; i++) {
        delete[] kernel[i];
    }
    delete[] kernel;
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : diffy
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image
 * OUT          : None
 * PROCESS      : Differentiates current image in y direction
 *
 *********************************************************************************************************************/
imgerr Image::diffy() {
    float **kernel;
    float hy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
    kernel = new float*[3];

    for (int i = 0; i < 3; i++)
        kernel[i] = new float[3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = hy[i][j];
        }
    }

    convl((float **) kernel, 3, 3);

    for (int i = 0; i < 3; i++) {
        delete[] kernel[i];
    }
    delete[] kernel;
    //fldy(img, img);
    return SUCC;
}
/**********************************************************************************************************************
 * FUNCTION     : centerOfGravity
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image
 * OUT          : None
 * PROCESS      : Calculated Center of Gravity of the shape with 0
 *
 *********************************************************************************************************************/
imgerr Image::centerOfGravity(double &meanX, double &meanY, int shapeValue) {

    double totalPixels = 0;
    meanX = 0;
    meanY = 0;

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            if (shapeValue == img[x][y]) {
                meanX += x;
                meanY += y;
                totalPixels++;
            }
        }
    }
    meanX = round (meanX / totalPixels);
    meanY = round (meanY / totalPixels);
    //cout << "Total Pixels " << totalPixels << " meanX " << meanX << " meanY " << meanY << endl;

    return SUCC;
}

/**********************************************************************************************************************
 * FUNCTION     : etapq
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image, p q, meanX, meanY, ETA00
 * OUT          : None
 * PROCESS      : Calculates ETApq
 *
 *********************************************************************************************************************/
double Image::etapq(int p, int q, int meanX, int meanY, int area) {
    double eta = 0;

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            if (0 == img[x][y]) {
                eta += pow((x - meanX), p) * pow((y - meanY), q);
            }
        }
    }

    return eta / (pow(area, (p + q + 2) / 2));
}

/**********************************************************************************************************************
 * FUNCTION     : translate
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image, x, y
 * OUT          : None
 * PROCESS      : Performs translation operation in Image
 *
 *********************************************************************************************************************/
imgerr Image::translate(int xTr, int yTr) {

    Image temp(dimension, row, col);

    for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                temp.img[x][y] = img[x][y];
            }
    }

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            int xTrans = x - xTr;
            int yTrans = y - yTr;
            if (xTrans >= 0 && xTrans < row && yTrans >= 0 && yTrans < row) {
                temp.img[x][y] = img[xTrans][yTrans];
            }
        }
    }

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            img[x][y] = temp.img[x][y];
        }
    }

    return SUCC;
}

/**********************************************************************************************************************
 * FUNCTION     : rotate
 * CLASS        : Image
 * TYPE         : member function
 * IN           : input Image, rotationInRad
 * OUT          : None
 * PROCESS      : Performs Rotation around shape with 0s in it operation in Image
 *
 *********************************************************************************************************************/
imgerr Image::rotate(float rotationInRad, double meanX, double meanY) {

    Image temp(dimension, row, col);

    for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                temp.img[x][y] = img[x][y];
            }
    }

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            int xrot = (int) round((cos(rotationInRad) * (x - meanX) - sin(rotationInRad) * (y - meanY) + meanX));
            int yrot = (int) round((sin(rotationInRad) * (x - meanX) + cos(rotationInRad) * (y - meanY) + meanY));

            if (xrot >= 0 && xrot < row && yrot >= 0 && yrot < row) {
                temp.img[x][y] = img[xrot][yrot];
            }
        }
    }

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            img[x][y] = temp.img[x][y];
        }
    }

    return SUCC;
}

/* Nothing beyond this */
