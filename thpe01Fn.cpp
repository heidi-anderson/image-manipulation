/** ***************************************************************************
 * @file 
 *
 * @brief demonstrates function for outputting the usage statement
 *****************************************************************************/

#include "netPBM.h"

 /** ***************************************************************************
  * @author Heidi Anderson
  *
  * @par Description:
  * Crops a number to be between 0 and 255 inclusive
  *
  * @param[in] num - number to be cropped
  *
  * @returns returns the cropped number
  *
  * @par Example:
    @verbatim
    crop(-14)
   
    Output:
    0
    @endverbatim
  * 
  *****************************************************************************/
int crop(int num)
{
    if ( num < 0 )    // crop to zero
    {
        num = 0;
    }

    if ( num > 255 )  // crop to 255
    {
        num = 255;
    }

    return num;
}



/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Does error checking for command line arguments
 *
 * @param[in,out] argc - number of arguments
 * @param[in,out] argv - character array of arguments
 *
 * @returns returns 0 if successful
 *
 * @par Example:
   @verbatim
   errorCheck(1, argv)
   
   Output:
< thpe01.exe [option] --outputtype basename image.ppm
< Output Type      Output Description
<     --ascii      integer text numbers will be written for the data
<     --binary     integer numbers will be written in binary form
< Option Code      Option Description
<     --smooth     Blur a color image
<     --sharpen    Enhance the lines in a color image
<     --negate     Create a negative of a color image
<     --brighten # Add the provide (+/-) number to each pixel
<     --grayscale  Convert image to grayscale
<     --contrast   Convert a color image to grayscale and scale the pixel values
   @endverbatim
 * 
 *****************************************************************************/
int errorCheck(int& argc, char**& argv)
{
    string outputType = argv[argc - 3];
    string option = argv[1];

    if (argc < 4 || argc > 6 || argc == 0)  // invalid num of args
    {
        usageStatement();
        exit(0);
    }

    if (outputType != "--ascii" && outputType != "--binary") // invalid output
    {
        cout << "Invalid output type" << endl;
        usageStatement();
        exit(0);
    }

    if (option != "--negate" && option != "--smooth" &&     // invalid option
        option != "--sharpen" && option != "--grayscale" && 
        option != "--brighten" && option != "--contrast" && 
        option != "--ascii" && option != "--binary")
    {
        cout << "Invalid option" << endl;
        usageStatement();
        exit(0);
    }

    return 0;
}



/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * This function is designed to provide users with information about how to
 * use the command-line. It print's the program's available options with their
 * descriptions to guide users on how to interact with the program.
 *
 * @returns returns 0 if successful
 *
 * @par Example:
   @verbatim
   usageStatement();
   
   Output:
< thpe01.exe [option] --outputtype basename image.ppm
< Output Type      Output Description
<     --ascii      integer text numbers will be written for the data
<     --binary     integer numbers will be written in binary form
< Option Code      Option Description
<     --smooth     Blur a color image
<     --sharpen    Enhance the lines in a color image
<     --negate     Create a negative of a color image
<     --brighten # Add the provide (+/-) number to each pixel
<     --grayscale  Convert image to grayscale
<     --contrast   Convert a color image to grayscale and scale the pixel values
   @endverbatim
 * 
 ******************************************************************************/
int usageStatement()
{
    cout << "thpe01.exe [option] --outputtype basename image.ppm" << endl;
    cout << endl;
    cout << "Output Type      Output Description" << endl;
    cout << "    --ascii      integer text numbers will be written for the data" << endl;
    cout << "    --binary     integer numbers will be written in binary form" << endl;
    cout << endl;
    cout << "Option Code      Option Description" << endl;
    cout << "    --smooth     Blur a color image" << endl;
    cout << "    --sharpen    Enhance the lines in a color image" << endl;
    cout << "    --negate     Create a negative of a color image" << endl;
    cout << "    --brighten # Add the provide (+/-) number to each pixel" << endl;
    cout << "    --grayscale  Convert image to grayscale" << endl;
    cout << "    --contrast   Convert a color image to grayscale and scale the pixel values" << endl;

    return 0;

}