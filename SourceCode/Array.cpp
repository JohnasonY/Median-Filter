#include "Array.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void RandArray(int A[], int n, int N)
{
  srand(time(0));
  for(int i = 0; i < n; i++)
  {
    A[i] = rand() % N + 1;
  }
}