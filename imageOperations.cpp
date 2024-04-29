/** ***************************************************************************
 * @file
 *
 * @brief demonstrates brighten, negate, contrast, grayscale, sharpen and 
 *        smooth.
 *****************************************************************************/

#include "netPBM.h"

 /** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * This function iterates over each pixel in the image using nested loops.
 * For each pixel, it adds the 'value' to the red, green and blue components
 * separately, creating a new red, green and blue values. The new red, green
 * and blue values are then clamped to the range [0,255]. After the execution
 * of the function the image will be brightened by increasing the red, green
 * and blue components.
 *
 * @param[in,out] image - structure for image information
 * @param[in] value - the value given by the user for amt of brightness
 *
 * @par Example:
   @verbatim
   brighten(image, 100)
   
   Output:
   a brightened image per the value 100
   @endverbatim
 *
 * *****************************************************************************/
void brighten(image& image, int value)
{
    int r, c;

    for (r = 0; r < image.rows; ++r)
    {
        for (c = 0; c < image.cols; ++c)
        {
            image.redgray[r][c] = crop(image.redgray[r][c] + value);
            image.green[r][c] = crop(image.green[r][c] + value);
            image.blue[r][c] = crop(image.blue[r][c] + value);

        }
    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * This function first converts the input image to grayscale using the
 * 'grayscale' function. The function then finds the maximum and minimum
 * intensity values in the grayscale image. It iterates through each pixel and
 * and keeps track of the maximum and minimum intensity values encountered.
 * After finding the maximum and minimum intensity values, the function
 * calculates a scaling factor 'scale' to stretch the intesntiy values to the
 * full range of [0.255]. This scaling factor ensures that the intensity values are
 * distributed across the entire range, effecrively enhancing the contrast.
 *
 * The function iterates through each pixzel of the grayscale imagte again. For
 * each pixel, it applies the contrast enhancement formula. The resulting
 * intensity values are then clamped to the range [0.255]. This ensures that the
 * intensity values do not go beyond the valid range. After the function
 * execution, the input grayscale image will have it's contrast enhanced.
 *
 * @param[in,out] image - structure for image information
 * 
 * @par Example:
   @verbatim
   contrast(image)
   
   Output:
   a contrasted image
   @endverbatim
 * 
 * *****************************************************************************/
void contrast(image& image)
{
    long maximum, minimum;
    int r, c;
    double scale;

    grayscale(image);

    maximum = image.redgray[0][0];
    minimum = image.redgray[0][0];

    for (r = 0; r < image.rows; r++)
    {
        for (c = 0; c < image.cols; c++)
        {
            if (image.redgray[r][c] > maximum)
                maximum = image.redgray[r][c];

            if (image.redgray[r][c] < minimum)
                minimum = image.redgray[r][c];
        }
    }

    scale = 255.0 / (maximum - minimum);

    for (r = 0; r < image.rows; r++)
    {
        for (c = 0; c < image.cols; c++)
        {
            image.redgray[r][c] = crop((int)round(scale * (image.redgray[r][c] - minimum)));

        }
    }
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * The function checks the 'magicNumber' attribute oif the image. If the number
 * is P3, it's updated to P2 and if the number is P6 it's updated to P5. The
 * function iterates over each pixel in the image using nested loops. For each
 * pixel, it calculates a new grayscale value. The resulting grayscale value
 * is clamped to the range [0,255]. After the function execution, the input
 * image will be converted to grayscale. Each pixel in the output image will
 * represent a shade of gray, and the color information from the original image
 * will be discarded. The updated magicNumber indicates the type of new image
 * file.
 *
 * @param[in,out] image - structure for image information
 * 
 * @par Example:
   @verbatim
   grayscale(image)
   
   Output:
   a grayscaled image
   @endverbatim
 * *****************************************************************************/
void grayscale(image& image)
{
    int r, c;
    pixel** grayscale = alloc2d(image.rows, image.cols);

    if (image.magicNumber == "P3")
        image.magicNumber = "P2";

    if (image.magicNumber == "P6")
        image.magicNumber = "P5";

    for (r = 0; r < image.rows; ++r)
    {
        for (c = 0; c < image.cols; ++c)
        {
            grayscale[r][c] = crop((pixel)round(0.3 * (double)image.redgray[r][c] +
                0.6 * (double)image.green[r][c] +
                0.1 * (double)image.blue[r][c]));
        }
    }

    copy2d(grayscale, image.redgray, image.rows, image.cols);

    free2d(grayscale, image.rows);
    image.blue = nullptr;
    image.green = nullptr;
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * This function iterates over each pixel in the image using nested loops. For
 * each pixel, it calculates a new red, green, and blue values using the
 * following formula: newColor = 255 - oldColor. This formula negates the color
 * value by subtracting the original color values from 255. In other words, it 
 * converts a bright pixel to a dark pixel and vice versa. After the function 
 * execution, the input image will be negated, meaning that all colors will be
 * inverted. White pixels become black, black becomes white, and so on.
 *
 * @param[in,out] image - structure for image information
 * 
 * @par Example:
   @verbatim
   negateImage(image)
   
   Output:
   a negated image
   @endverbatim
 * *****************************************************************************/
void negateImage(image& image)
{
    int r, c;

    for (r = 0; r < image.rows; ++r)    // for loop to implement negation
    {
        for (c = 0; c < image.cols; ++c)
        {
            image.redgray[r][c] = 255 - image.redgray[r][c];
            image.green[r][c] = 255 - image.green[r][c];
            image.blue[r][c] = 255 - image.blue[r][c];
        }
    }

}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * This function first allocates memory for three 2D arrays: 'newRed',
 * 'newGreen', and 'newBlue', which will store the smoothed pixel values. These
 * arrays have the same dimensions as the input image. The function then 
 * iterates over each pixel of the input image, excluding the border pixels.
 * For each inner pixel, it calculates the average of the red, green and blue
 * values of the pxiel and its 8 neighboring pixels (3x3 neighborhood). The
 * average values are stored in the 2D arrays after clamping the result to the
 * range [0,255]. After processing all pixels, the function updates the input
 * image's pixel arrays with the smoothed pixel values stored in the new 2D 
 * arrays. Finally, the function deallocates the memory occupied by the new 2D
 * arrayus using the free2d function.
 *
 * @param[in,out] image - structure for image information
 *
 * @returns true to indicate successful completion of smoothing operation
 * 
 * @par Example:
   @verbatim
   smooth(image)
   
   Output:
   a smoothed image
   @endverbatim
 *
 * *****************************************************************************/
bool smooth(image& image)
{
    pixel** newRed = alloc2d(image.rows, image.cols);
    pixel** newGreen = alloc2d(image.rows, image.cols);
    pixel** newBlue = alloc2d(image.rows, image.cols);
    double average;
    int r, c;

    for (r = 0; r < image.rows; r++)
    {
        for (c = 0; c < image.cols; c++)
        {
            if (r == 0 || c == 0 ||
                r == image.rows - 1 || c == image.cols - 1)
            {
                newRed[r][c] = 0;
                newBlue[r][c] = 0;
                newGreen[r][c] = 0;
            }
            else
            {
                average = ((unsigned long)image.redgray[r - 1][c - 1] +
                    image.redgray[r - 1][c] + image.redgray[r - 1][c + 1] +
                    image.redgray[r][c - 1] + image.redgray[r][c]
                    + image.redgray[r][c + 1] + image.redgray[r + 1][c - 1] +
                    image.redgray[r + 1][c] + image.redgray[r + 1][c + 1]) / 9.0;
                newRed[r][c] = crop((int)average);

                average = ((unsigned long)image.green[r - 1][c - 1] +
                    image.green[r - 1][c] + image.green[r - 1][c + 1] +
                    image.green[r][c - 1] + image.green[r][c]
                    + image.green[r][c + 1] + image.green[r + 1][c - 1] +
                    image.green[r + 1][c] + image.green[r + 1][c + 1]) / 9.0;
                newGreen[r][c] = crop((int)average);

                average = ((unsigned long)image.blue[r - 1][c - 1] +
                    image.blue[r - 1][c] + image.blue[r - 1][c + 1] +
                    image.blue[r][c - 1] + image.blue[r][c]
                    + image.blue[r][c + 1] + image.blue[r + 1][c - 1] +
                    image.blue[r + 1][c] + image.blue[r + 1][c + 1]) / 9.0;
                newBlue[r][c] = crop((int)average);;
            }
        }
    }

    copy2d(newRed, image.redgray, image.rows, image.cols);
    copy2d(newGreen, image.green, image.rows, image.cols);
    copy2d(newBlue, image.blue, image.rows, image.cols);

    free2d(newRed, image.rows), free2d(newBlue, image.rows), free2d(newGreen, image.rows);

    return true;

}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * The function allocates memory for three 2d arrays, 'newRed', 'newBlue', and
 * 'newGreen', which will store the sharpened pixel values. Then the function 
 * iterates over each pixel of the input image, excluding the border pixels.
 * For each inner pixel, it applies a sharpening kernal to the surrounding 3x3
 * neighborhood. The values in the kernal determine how much the pixel values
 * in the nieghborhood contribute to the sharpened pixel. The central pixel's
 * value is multiplied by 9 and the surrounding pixel's values are multiplied
 * by -1. This emphasizes the difference between the central pixel and its
 * neighbors, enhancing edges. The function calculates the sharpened red, green
 * and blue values and stores them in the new 2D arrays after clamping the 
 * result to the rang [0.255]. After processing all pixels, the function updates
 * the images pixel arrays with the sharpened pixel values stored in the new 2D
 * arrays. Finally, the function deallocates the memory occupied by the new 2D 
 * arrays's by using the free2d function.
 *
 * @param[in,out] image - structure for image information
 *
 * @returns true to indicate successful completion of sharpening operation
 * 
 * @par Example:
   @verbatim
   sharpen(image)
   
   Output:
   a sharpened image
   @endverbatim
 *
 * *****************************************************************************/
bool sharpen(image& image)
{
    pixel** newRed = alloc2d(image.rows, image.cols);
    pixel** newGreen = alloc2d(image.rows, image.cols);
    pixel** newBlue = alloc2d(image.rows, image.cols);
    int r, c;

    for (r = 0; r < image.rows; r++)
    {
        for (c = 0; c < image.cols; c++)
        {
            if (r == 0 || c == 0 || r == image.rows - 1 || c == image.cols - 1)
            {
                newRed[r][c] = 0;
                newBlue[r][c] = 0;
                newGreen[r][c] = 0;
            }
            else
            {
                newRed[r][c] = crop(5 * image.redgray[r][c] - image.redgray[r][c - 1] -
                    image.redgray[r - 1][c] - image.redgray[r + 1][c] -
                    image.redgray[r][c + 1]);

                newGreen[r][c] = crop(5 * image.green[r][c] - image.green[r][c - 1] -
                    image.green[r - 1][c] - image.green[r + 1][c] -
                    image.green[r][c + 1]);

                newBlue[r][c] = crop(5 * image.blue[r][c] - image.blue[r][c - 1] -
                    image.blue[r - 1][c] - image.blue[r + 1][c] -
                    image.blue[r][c + 1]);
            }
        }
    }

    copy2d(newRed, image.redgray, image.rows, image.cols);
    copy2d(newGreen, image.green, image.rows, image.cols);
    copy2d(newBlue, image.blue, image.rows, image.cols);

    free2d(newRed, image.rows);
    free2d(newBlue, image.rows);
    free2d(newGreen, image.rows);

    return true;

}

