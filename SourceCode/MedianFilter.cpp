#include "MedianFilter.h"
#include <iostream>

using namespace std;

void MedianFilter(const char *infilename, int N, const char *outfilename)
{
  unsigned char **image;
  int rows, cols;
  int WindowPixels = N * N;
  
  if (read_pgm_image(infilename, &image, &rows, &cols) == 1)
  {
    cout << "Image read successfully" << endl;
    cout << "Image dimensions: " << rows << " * " << cols << endl;
  }
  else
  {
    cout << "Image read fail" << endl;
    return;
  }


  for(int curRowIndex = 0; curRowIndex < rows; curRowIndex++)   
  {
    for(int curColIndex = 0; curColIndex < cols; curColIndex++)
    {
      int* window = new int[WindowPixels];
      int i = 0;
      int shiftToBound = N/2;
      int rowBoundIndex = curRowIndex + shiftToBound;
      int colBoundIndex = curColIndex + shiftToBound;
      for(int winRowIndex = curRowIndex - shiftToBound; winRowIndex <= rowBoundIndex; winRowIndex++)
      {
        for(int winColIndex = curColIndex - shiftToBound; winColIndex <= colBoundIndex; winColIndex++)
        {
          if(winRowIndex < 0 || winRowIndex >= rows || winColIndex < 0 || winColIndex >= cols)
          {
            window[i] = 0;
          }
          else
          {
            window[i] = (int)image[winRowIndex][winColIndex];     
          }
          i++;
        }
      }

      int medianPosition = WindowPixels / 2 + 1;
      int median = RandSelection(window, medianPosition , 0, WindowPixels-1);
      
      image[curRowIndex][curColIndex] = static_cast<char>(median);

      delete[] window;
    }
  }
  write_pgm_image(outfilename, image, rows, cols, nullptr, 255);
  
}