/** ***************************************************************************
 * @file
 *
 * @brief main execution of program and program logic
 *****************************************************************************/
 /** ***************************************************************************
  * @mainpage Take Home Programming Exam 1 - Image Manipulation
  *
  * @section course_section Course Information
  *
  * @authors Heidi Anderson
  *
  * @date October 15, 2023
  *
  * @par Instructor
  *         Roger Schrader
  *
  * @par Course
  *         CSC 215 - Section M02 - 1:00 pm
  *
  * @par Location
  *         McLaury - Room 205
  *
  * @section program_section Program Information
  *
  * @details This program reads in an image and will perform an operation based
  * on the user's input. if "--sharpen" is given the program will perform the 
  * sharpen operation. Same follows with "--smooth", "--contrast", 
  * "--grayscale", "--negate", and "--brighten". The program will also convert
  * the image to binary or ascii given what option the user gives. (Either 
  * "--ascii" or "--binary") After performing the operation the program will
  * write out the new modified image. 
  *
  * Because of space, the rest of the details have been omitted.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      None
  *
  * @par Usage
    @verbatim
    c:\> thpe01.exe [option] --[ascii | binary] basename image.ppm
        --smooth - smooth operation
        --sharpen - sharpen operation
        --contrast - contrast operation
        --grayscale - grayscale operation
        --negate - negate operation
        --brighten # - brighten operation and brighten value.
    @endverbatim
  *
  * @par Modifications and Development Timeline:
  *     <a href="https://gitlab.cse.sdsmt.edu/101061875/csc215f23programs/-/commits/main/" target=_blank>
  *     Gitlab Commit Log</a>
  *
  *****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include "netPBM.h"

using namespace std;

/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * This first checks the number of command-line arguments passed ('argc'). If 
 * there are fewer than 4 or more than 6 arguments, or if 'argc' is 0, it will
 * print out an error message and exit with a status of '0'. Depending on the 
 * number of arguments, it parses the input arguments. It also validates the
 * 'option' and 'outputType' arguments. If they are not recognized it prints 
 * and error message and exits with a code '0'.
 * 
 * The the function reads the image data form the file specified by 'fileName'
 * into the 'image' object using the 'readImage' function. If the image cannot
 * be read, it exits with a status of '1'. Depending on the option, the function
 * applies various images processing operations. 
 * 
 * After processing the image based on the specified operation, the function 
 * writes the processed image data to an output file specified by 'baseName' 
 * and 'outputType' using the 'writeImage' function. If the image cannot be
 * written it exits with a status '1'.
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 - after completion of execution
 * @returns 0 - if there is an error in reading or writing
 * 
 ******************************************************************************/
int main(int argc, char** argv)
{
    string outtype, option = argv[1], baseName = argv[argc - 2], 
           inputImage = argv[argc - 1], outputFile = " ";
    int brightVal = 0;
    image image;
    ifstream fin;
    ofstream fout;
    char* outputType = argv[argc - 3];
    
    errorCheck(argc, argv);

    if (argc == 6)
    {
        brightVal = stoi(argv[2]);
    }

    openInput(inputImage, fin);
    
    readHeader(fin, image);

    image.redgray = alloc2d(image.rows, image.cols);
    image.green = alloc2d(image.rows, image.cols);
    image.blue = alloc2d(image.rows, image.cols);
    
    asciiOrBinary(fin, image);
    
    if (option == "--brighten")
        brighten(image, brightVal);
    else if (option == "--negate")
        negateImage(image);
    else if (option == "--grayscale")
        grayscale(image);
    else if (option == "--contrast")
        contrast(image);
    else if (option == "--smooth")
        smooth(image);
    else if (option == "--sharpen")
        sharpen(image);

    if (option == "--grayscale" || option == "--contrast")
        outputFile = baseName + ".pgm";
    else
        outputFile = baseName + ".ppm";

    output(outputType, outputFile, fout, image, option);
        
    return 0;
}