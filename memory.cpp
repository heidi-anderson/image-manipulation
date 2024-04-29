/** ***************************************************************************
 * @file memory.cpp
 *
 * @brief demonstrates allocating and deallocating a 2D array
 *****************************************************************************/

#include "netPBM.h"

 /** ***************************************************************************
  * @author Barney Rubble
  *
  * @par Description:
  * The function first checks if the pointer is nullptr. If ptr is nullptr it
  * means that no memory was allocated, so the function simply returns without
  * doing anything. If ptr is not nullptr, the function enters a loop that 
  * iterates through each row of the 2D array. For each row, it calls delete[]
  * to deallocate the memory allocated for that row. After deallocating the 
  * memory for each row, the function calls 'delete[]' again to deallocate the
  * memory occupied by the array of pointers ('ptr'). After the function 
  * execution, the ptr is now dangling, meaning it points to a location in 
  * memory that has been deallocated.
  *
  * @param[in] ptr - reference to a pointer of 'pixel' type
  * @param[in] rows - the number of rows in the 2D array
  * 
  * @par Example:
   @verbatim
   free2d(ptr, 4);
   @endverbatim
  * 
  ******************************************************************************/
void free2d(pixel**& ptr, int rows)
{
    int i;
    if (ptr == nullptr)
        return;

    for (i = 0; i < rows; i++)  // loop to step through ptr
        delete[] ptr[i];        // free ptr[i]

    delete[] ptr;
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description
 * This function dynamically allocates memory for a 2D array of pixels. It
 * first allocates memory for an array of pointers to 'pixel', and then, for
 * each row, it allocates memory for an array of 'pixel' type. If any memory
 * allocation fails during this process, it frees the previously allocated 
 * memory and returns false.
 *
 * @param[in] row - the number of rows in the 2D array
 * @param[in] cols - the number of columns in the 2D array
 *
 * @returns true to indicate successful memory allocation
 * 
 * @par Example:
   @verbatim
   alloc2d(2, 3);
   @endverbatim
 *
 * *****************************************************************************/
pixel** alloc2d(int row, int cols)
{
    int i;
    pixel** ptr = nullptr;

    ptr = new (nothrow) pixel * [row];

    if (ptr == nullptr)
    {
        return nullptr;
    }

    for (i = 0; i < row; i++)
    {
        ptr[i] = new (nothrow) pixel[cols]; // allocation step
        if (ptr[i] == nullptr)              // free if necessary
        {
            free2d(ptr, row);
            return nullptr;
        }
    }
    return ptr;
}


/** ***************************************************************************
 * @author Heidi Anderson
 *
 * @par Description:
 * Copies the values from one array into another
 *
 * @param[in] source - pointer to the source 2D array
 * @param[out] dest - pointer to the destination 2D array
 * @param[in] rows - rows in the array
 * @param[in] cols - columns in the array
 * 
 * @par Example:
   @verbatim
   copy2d(source, dest, 12, 14);
   @endverbatim
 *
 *****************************************************************************/
void copy2d(pixel**& source, pixel**& dest, int rows, int cols)
{
    int r, c;

    for (r = 0; r < rows; ++r)
    {
        for (c = 0; c < cols; ++c)
        {
            dest[r][c] = source[r][c];  // copy source to destination
        }
    }
}