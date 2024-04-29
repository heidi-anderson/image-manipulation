/** ***************************************************************************
 * @file
 *
 * @brief handles all input/output operations such as read and write.
 *****************************************************************************/

#include "netPBM.h"

 /** ***************************************************************************
  * @author Heidi Anderson
  *
  * @par Description:
  * Writes out image data in Binary
  *
  * @param[in,out] fin - reference to ifstream
  * @param[in,out] image - image structure
  *
  * @par Example:
    @verbatim
    asciiOrBinary(fin, image);
    @endverbatim
  * 
  *****************************************************************************/
void asciiOrBinary(ifstream& fin, image& image)
{
    if (image.magicNumber == "P3" || image.magicNumber == "P2") // ascii
    {
        readAscii(fin, image);  // call to read ascii file
    }
    if (image.magicNumber == "P5" || image.magicNumber == "P6") // binary
    {
        readBinary(fin, image); // call to read binary file
    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Opens an ifstream for file input
 *
 * @param[in] fileName - name of file to be opened
 * @param[in,out] fin - reference to ifstream
 *
 * @returns true for success, false otherwise
 * 
 * @par Example:
   @verbatim
   openInput(InputFile.ppm, fin);
   @endverbatim
 *
 *****************************************************************************/
bool openInput(string fileName, ifstream& fin)
{
    fin.open(fileName, ios::in | ios::binary); // open input

    if (!fin.is_open())
    {
        cout << "Unable to open input file: " << fileName << endl;
        return false;
    }

    return true;
}



/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Opens an ofstream for file output
 *
 * @param[in,out] fout - reference to ofstream
 * @param[in] fileName - name of file to be opened
 *
 * @returns true for success, false otherwise
 * 
 * @par Example:
   @verbatim
   openOutput(outputFile.ppm, fout);
   @endverbatim
 * 
 *****************************************************************************/
bool openOutput(string fileName, ofstream& fout)
{
    fout.open(fileName, ios::binary);   // open output

    if (!fout.is_open())
    {
        cout << "Unable to open the file: " << fileName << endl;
        return false;
    }

    return true;

}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Determines how to write output.
 *
 * @param[in] outputType - type of output, ascii/binary
 * @param[in,out] outputFile - name of output file
 * @param[in,out] fout - reference to ofstream
 * @param[in,out] image - image structure
 * @param[in,out] option - image operation choice
 *
 * @par Example:
   @verbatim
   output("--ascii", outputFile.ppm, fout, image, "--negate");
   @endverbatim
 * 
 *****************************************************************************/
void output(char* outputType, string outputFile, ofstream& fout, image& image, string option)
{
    if (!openOutput(outputFile, fout))  // error check
    {
        exit(0);
    }

    if (strcmp(outputType, "--ascii") == 0) // compare strings
    {
        writeAscii(fout, image, option);
    }

    if (strcmp(outputType, "--binary") == 0)    // compare strings
    {
        writeBinary(fout, image, option);
    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Reads in ASCII image data
 *
 * @param[in] fin - reference to ifstream
 * @param[out] image - image structure
 *
 * @par Example:
   @verbatim
   readAscii(fin, image);
   @endverbatim
 * 
 *****************************************************************************/
void readAscii(ifstream& fin, image& image)
{
    int r, c, temp;

    for (r = 0; r < image.rows; ++r)    // for loop to step through pixels
    {
        for (c = 0; c < image.cols; ++c)
        {
            fin >> temp;
            image.redgray[r][c] = temp;

            fin >> temp;
            image.green[r][c] = temp;

            fin >> temp;
            image.blue[r][c] = temp;
        }

    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Reads in Binary image data
 *
 * @param[in] fin - reference to ifstream
 * @param[out] image - image structure
 * 
 * @par Example:
   @verbatim
   readBinary(fin, image);
   @endverbatim
 *
 *****************************************************************************/
void readBinary(ifstream& fin, image& image)
{
    int r, c;

    for (r = 0; r < image.rows; ++r)    // for loop to read pixels
    {
        for (c = 0; c < image.cols; ++c)
        {
            fin.read((char*)&image.redgray[r][c], sizeof(pixel));
            fin.read((char*)&image.green[r][c], sizeof(pixel));
            fin.read((char*)&image.blue[r][c], sizeof(pixel));
        }

    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Reads header
 *
 * @param[in] fin - reference to ifstream
 * @param[out] image - image structure
 *
 * @par Example:
   @verbatim
   readHeader(fin, image);
   @endverbatim
 *
 *****************************************************************************/
void readHeader(ifstream& fin, image& image)
{
    string comment;
    string placeHold;

    fin >> image.magicNumber;   // get magic number
    fin.ignore();

    while (fin.peek() == '#')   // get comments
    {
        getline(fin, comment);
        image.comment = image.comment + '\n' + comment;
    }

    fin >> image.cols >> image.rows;
    fin >> placeHold;
    fin.ignore();

}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Writes out image data in ASCII
 *
 * @param[in] fout - reference to ofstream
 * @param[in] image - image structure
 * @param[in] option - operation to be applied to the image
 * 
 * @par Example:
   @verbatim
   writeAscii(fin, image);
   @endverbatim
 * 
 *****************************************************************************/
void writeAscii(ofstream& fout, image& image, string option)
{
    int r, c;

    if (option == "--grayscale" || option == "--contrast")  // write header
        fout << "P2";
    else
        fout << "P3";

    fout << image.comment << "\n";
    fout << image.cols << " " << image.rows << "\n";
    fout << "255" << "\n";

    for (r = 0; r < image.rows; r++)    // write out pixels
    {
        for (c = 0; c < image.cols; c++)
        {
            if (image.magicNumber == "P2")
            {
                fout << (int)image.redgray[r][c] << "\n";

            }
            else
            {
                fout << (int)image.redgray[r][c] << " "
                    << (int)image.green[r][c] << " "
                    << (int)image.blue[r][c] << "\n";
            }
        }
    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Writes out image data in Binary
 *
 * @param[in] fout - reference to ofstream
 * @param[in] image - image structure
 * @param[in] option - image operation choice
 * 
 * @par Example:
   @verbatim
   writeBinary(fin, image, "--negate");
   @endverbatim
 * 
 *****************************************************************************/
void writeBinary(ofstream& fout, image& image, string option)
 {
    int r, c;

    if (option == "--grayscale" || option == "--contrast")  // write header
        fout << "P5";
    else
        fout << "P6";

    fout << image.comment << "\n";
    fout << image.cols << " " << image.rows << "\n";
    fout << "255" << "\n";


    for (r = 0; r < image.rows; r++)        // write out pixels
    {
        for (c = 0; c < image.cols; c++)
        {
            if (image.redgray != nullptr)
            {
                fout.write((char*)&image.redgray[r][c], sizeof(pixel));
            }

            if (image.green != nullptr)
            {
                fout.write((char*)&image.green[r][c], sizeof(pixel));
            }

            if (image.blue != nullptr)
            {
                fout.write((char*)&image.blue[r][c], sizeof(pixel));
            }
        }
    }
}