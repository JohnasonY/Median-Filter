/*******************************************************************************
* Program: imageio.c
* Purpose: This souce code file contains functions for dynamically allocating
* and freeing 8-bit (unsigned char) images. It also contains functions for
* reading and writing images to files in raw PGM format. This code was written
* to be used as a teaching resource.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "imageio.h"
#include <sstream>

/*******************************************************************************
* Function: allocate_image
* Purpose: This function allocates an image. The image is an array of pointers
* to arrays. The array of pointers will have a length of the number of rows,
* and each of these pointers will point to a separate one dimensional array
* whose length is the number of columns in the image. This scheme was used
* because it allows the image to be accessed using the syntax image[r][c]
* yet still allow the image to be any size.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
unsigned char **allocate_image(int rows, int cols)
{
   unsigned char **image = nullptr;
   int r, br;

   /****************************************************************************
   * Allocate an array of pointers of type (unsigned char *). The array is
   * allocated to have a length of the number of rows.
   ****************************************************************************/
   if ((image = new unsigned char *[rows]) == nullptr)
   {
      std::cerr << "Error allocating the array of pointers in allocate_image()." << std::endl;
      return nullptr;
   }

   /****************************************************************************
   * For each row, allocate an array of type (unigned char).
   ****************************************************************************/
   for (r = 0; r < rows; r++)
   {
     if ((image[r] = new unsigned char[cols]) == nullptr)
     {
       std::cerr << "Error allocating an array in allocate_image()." << std::endl;
       for (br = 0; br < r; br++)
        delete[] image[br];
       delete[] image;
       return nullptr;
     }
  }

   return image;
}

/*******************************************************************************
* Function: free_image
* Purpose: This function frees the memory that was previously allocated to
* store an image.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
*******************************************************************************/
void free_image(unsigned char **image, int rows)
{
   int r;

   /****************************************************************************
   * Free each row of the image.
   ****************************************************************************/
   for(r=0;r<rows;r++) delete[] image[r];;

   /****************************************************************************
   * Free the array of pointers.
   ****************************************************************************/
   delete[] image;
}

/******************************************************************************
* Function: read_pgm_image
* Purpose: This function reads in an image in raw PGM format. Because the PGM
* format includes the number of columns and the number of rows in the image,
* these are read from the file. Memory to store the image is allocated in this
* function. All comments in the header are discarded in the process of reading
* the image. Upon failure, this function returns 0, upon sucess it returns 1.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
******************************************************************************/
int read_pgm_image(const char *infilename, unsigned char ***image, int *rows, int *cols)
{
   std::ifstream fp(infilename, std::ios::binary);
   char buf[71];

   /***************************************************************************
   * Open the input image file for reading. If the file can not be opened for
   * reading return an error code of 0.
   ***************************************************************************/
   if (!fp)
   {
     std::cerr << "Error reading the file " << infilename << " in read_pgm_image()." << std::endl;
     return 0;
   }

   /***************************************************************************
   * Verify that the image is in PGM format, read in the number of columns
   * and rows in the image and scan past all of the header information.
   ***************************************************************************/
   fp.getline(buf, 70);
   if (strncmp(buf, "P5", 2) != 0)
   {
     std::cerr << "The file " << infilename << " is not in PGM format in read_pgm_image()." << std::endl;
     fp.close();
     return 0;
   }

  do
  {
      fp.getline(buf, 70);
  } while (buf[0] == '#'); /* skip all comment lines */

  std::istringstream iss(buf);
  if (!(iss >> *cols >> *rows)) 
  {
    std::cerr << "Failed to read image dimensions." << std::endl;
    fp.close();
    return 0;
  }

  do
  {
      fp.getline(buf, 70);
  } while (buf[0] == '#'); /* skip all comment lines */

   /***************************************************************************
   * Allocate memory to store the image.
   ***************************************************************************/
   *image = allocate_image(*rows, *cols);
   if (*image == nullptr)
   {
      fp.close();
      return 0;
   }
   /***************************************************************************
   * Read in the image from the file, one row at a time.
   ***************************************************************************/
   for (int r = 0; r < *rows; r++)
   {
      if (*cols != fp.read(reinterpret_cast<char *>((*image)[r]), *cols).gcount())
      {
        std::cerr << "Error reading the image data in read_pgm_image()." << std::endl;
        fp.close();
        free_image(*image, *rows);
        return 0;
      }
  }

  fp.close();
  return 1;
}

/******************************************************************************
* Function: write_pgm_image
* Purpose: This function writes an image in raw PGM format. A comment can be
* written to the header if coment != NULL. If there is a comment, it can
* be up to 70 characters long.
* Name: Michael Heath, University of South Florida
* Date: 1/7/2000
******************************************************************************/
int write_pgm_image(const char *outfilename, unsigned char **image, int rows,
int cols, const char *comment, int maxval)
{
   std::ofstream fp(outfilename, std::ios::binary);


   /***************************************************************************
   * Open the output image file for writing.
   ***************************************************************************/
   if (!fp)
   {
      std::cerr << "Error writing the file " << outfilename << " in write_pgm_image()." << std::endl;
      return 0;
   }

   /***************************************************************************
   * Write the header information to the PGM file.
   ***************************************************************************/
  fp << "P5\n";
  if (comment != nullptr)
  {
      if (strlen(comment) <= 70)
      {
          fp << "# " << comment << "\n";
      }
  }
  fp << cols << " " << rows << "\n";
  fp << maxval << "\n";

   /***************************************************************************
   * Write the image data to the file.
   ***************************************************************************/
  for (int r = 0; r < rows; r++)
  {
      fp.write(reinterpret_cast<char *>(image[r]), cols);
      if (!fp)
      {
          std::cerr << "Error writing the image data in write_pgm_image()." << std::endl;
          fp.close();
          return 0;
      }
  }

  fp.close();
  return 1;
}
