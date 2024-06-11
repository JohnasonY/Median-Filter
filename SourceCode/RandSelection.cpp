#include "RandSelection.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;


double RandSelectionTime(int A[], int i, int begin, int end)
{
  clock_t start=0, endT=0;
  double milsecs;
  start = clock();
  
  int p = RandPartition(A, begin, end);

  cout << "The " << i << "th smallest element is ";
  if(i <= p - begin)            // ith smallest number is in the left partition
    cout << RandSelection(A, i, begin, p - 1) << "\t";
  else if(i == p - begin + 1)  // ith smallest number is the pivot
    cout << A[p] << "\t";
  else                         // ith smallest number is in the right partition    
    cout << RandSelection(A, i - (p - begin + 1), p + 1, end) << "\t";

  endT = clock();
  milsecs = (double)(endT - start)/ CLOCKS_PER_SEC * 1000;    //calculate time in milliseconds
  return milsecs; 
}

int RandSelection(int A[], int i, int begin, int end)
{
  //return the index of pivot after partition
  int p = RandPartition(A, begin, end);
  //i is in the left partition
  if(i <= p - begin)
    return RandSelection(A, i, begin, p - 1);
  //i is in the pivot partition
  else if(i == p - begin + 1)
    return A[p];
  //i is in the right partition
  else
    return RandSelection(A, i - (p - begin + 1), p + 1, end);
}

int RandPartition(int A[], int begin, int end)
{
  int p = begin + rand() % (end - begin + 1);
  int temp = A[p];
  A[p] = A[end];
  A[end] = temp;
  int pivot = A[end];
  int i = begin;
  for(int j = begin; j < end; j++)
  {
    if(A[j] <= pivot)
    {
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      i++;
    }
  }
  temp = A[i];
  A[i] = A[end];
  A[end] = temp;
  return i;
}