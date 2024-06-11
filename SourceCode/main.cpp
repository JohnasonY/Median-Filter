#include "Array.h"
#include "RandSelection.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "MedianFilter.h"
#include "imageio.h"


using namespace std;

void combination(int N, int n)
{
  int* A = new int[n];
  RandArray(A, n, N);
  
  int* B = new int[n];      //iniatialize to the same array for later run 5 times Randomized Selection
  for(int i = 0; i < n; i++)
    B[i] = A[i];

  cout << "**************************************************************" << endl;
  cout << "N = " << N << "\t" << "n = " << n << endl;

  double totalTime = 0;
  srand(time(0));
  for(int m = 0; m < 5; m++)
  {
    int i = rand() % n + 1;
    double time = RandSelectionTime(B, i, 0, n-1);
    cout << "Time in milliseconds: " << time << endl;
    totalTime += time;

    if(m != 4)
    {
      for(int i = 0; i < n; i++)
        B[i] = A[i];
    }
  }
  cout << "The Average time: " << totalTime/5 << endl;
    cout << "**************************************************************" << endl << endl;

  delete []A;
  delete []B;
}



int main() 
{
  
  combination(5000, 100);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 100);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 100);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(5000, 300);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 300);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 300);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(5000, 500);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 500);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 500);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(5000, 1000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 1000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 1000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(5000, 2000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 2000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 2000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(5000, 3000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 3000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 3000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(5000, 4000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(8000, 4000);
  this_thread::sleep_for(chrono::milliseconds(1000));
  combination(10000, 4000);
  
  std::string infilename;
  std::string outfilename;
  cout << "Please enter the input image file name(must be .pgm format): ";
  cin >> infilename;
  cout << "Please enter the output image file name for doing the median filter(must include .pgm format): ";
  cin >> outfilename;

  cout << "Please enter the window size N for N*N window(must be an odd number >=3): ";
  int windowSize;
  cin >> windowSize;
  const char* infilename_cstr = infilename.c_str();
  const char* outfilename_cstr = outfilename.c_str();
  MedianFilter(infilename_cstr, windowSize, outfilename_cstr);

  /*
    https://people.sc.fsu.edu/~jburkardt/data/pgmb/pgmb.html
  */
  return 0;
}
