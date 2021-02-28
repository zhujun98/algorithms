//
// Created by jun on 8/4/17.
//
#include <iostream>
#include <algorithm>

#include "knapsack.h"


Knapsack::Knapsack() {}

Knapsack::~Knapsack() {}

int Knapsack::solve(const int values[], const int weights[], int n_items, int capacity) {
  // allocate array in the heap for large data set
  int **tb = new int*[2];
  for ( int i=0; i<2; ++i) { tb[i] = new int[capacity+1]; }

  // initialization
  for ( int j=0; j<=capacity; ++j) { tb[0][j] = 0; }

  for ( int i=0; i<= n_items; ++i) {
    for ( int j=0; j<= capacity; ++j) {
      if ( weights[i-1] <= j ) {
        tb[1][j] = std::max(tb[0][j], tb[0][j - weights[i-1]] + values[i-1]);
      } else {
        tb[1][j] = tb[0][j]; // inherit from the left column
      }
    }

    for ( int j=0; j<= capacity; ++j) { tb[0][j] = tb[1][j]; }
  }

  int max_value = tb[1][capacity];

  for ( int i=0; i<2; ++i) { delete [] tb[i]; }
  delete [] tb;

  return max_value;
}
