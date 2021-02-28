//
// Created by jun on 8/4/17.
//
// Given weights and values of n items, put these items in a knapsack
// of capacity to get the maximum total value in the knapsack.
//
// TODO: retrieve the detailed solution, i.e. values and weights
//

#ifndef KNAPSACK_KNAPSACK_H
#define KNAPSACK_KNAPSACK_H


class Knapsack {

public:

  //
  // constructor
  //
  Knapsack();

  //
  // destructor
  //
  ~Knapsack();

  int solve(const int values[], const int weights[], int n_items, int capacity);
};


#endif //KNAPSACK_KNAPSACK_H
