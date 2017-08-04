//
// Created by jun on 8/4/17.
//
#include <iostream>
#include <algorithm>
#include <assert.h>

#include "knapsack.h"


Knapsack::Knapsack() {}

Knapsack::~Knapsack() {}

int Knapsack::solve(const int values[], const int weights[], int n_items, int capacity) {

  int tb[n_items + 1][capacity + 1];

  for ( int i=0; i<= n_items; ++i) {
    for ( int j=0; j<= capacity; ++j) {
      if (i == 0 || j == 0) {
        tb[i][j] = 0;
      } else if ( weights[i-1] <= j ) {
        tb[i][j] = std::max(tb[i-1][j], tb[i-1][j - weights[i-1]] + values[i-1]);
      } else {
        tb[i][j] = tb[i-1][j]; // inherit from the left column
      }
    }
  }

  return tb[n_items][capacity];
}
