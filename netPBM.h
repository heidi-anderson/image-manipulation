/** ***************************************************************************
 * @file
 *
 * @brief header file for take home programming exam 1
 *****************************************************************************/

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

/******************************************************************************
 *                              Typdef
 *****************************************************************************/
/**
 * @brief represents a pixel of an image
 */
typedef unsigned char pixel;


/******************************************************************************
 *                              Struct
 *****************************************************************************/
/**
 * @brief Holds data about the image
 */
struct image
{
    string magicNumber;     /**< Magic number to indicate image type */
    string comment;         /**< Comments in top of image file */
    int rows;               /**< Number of rows in the image */
    int cols;               /**< Number of columns in the image */
    pixel** redgray;        /**< 2D array for red/gray color values */
    pixel** green;          /**< 2D array for green color values */
    pixel** blue;           /**< 2D array for blue color values */
};


/******************************************************************************
 *                         Function Prototypes
 *****************************************************************************/
pixel** alloc2d(int row, int cols);
void asciiOrBinary(ifstream& fin, image& image);
void brighten(image& image, int value);
void contrast(image& picture);
void copy2d(pixel**& source, pixel**& dest, int rows, int cols);
int crop(int num);
int errorCheck(int& argc, char**& argv);
void free2d(pixel**& ptr, int r);
void grayscale(image& picture);
void negateImage(image& picture);
bool openInput(string fileName, ifstream& fin);
bool openOutput(string fileName, ofstream& fout);
void output(char* fileName, string outputFile, ofstream& fout, image& image, string option);
void readAscii(ifstream& fin, image& image);
void readBinary(ifstream& fin, image& image);
void readHeader(ifstream& fin, image& image);
bool sharpen(image& picture);
bool smooth(image& picture);
int usageStatement();
void writeAscii(ofstream& fout, image& image, string option);
void writeBinary(ofstream& fout, image& image, string option);
