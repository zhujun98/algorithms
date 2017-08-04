//
// Created by jun on 8/4/17.
//
// Given weights and values of n items, put these items in a knapsack
// of capacity to get the maximum total value in the knapsack.
//

#ifndef KNAPSACK_KNAPSACK_H
#define KNAPSACK_KNAPSACK_H

#include <vector>

typedef std::pair<std::vector<int>, std::vector<int>> sub_set;

class Knapsack {
private:
  sub_set solution_;  // store the solution (values, weights)

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
