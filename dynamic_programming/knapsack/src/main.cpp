//
// Created by jun on 8/4/17.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "knapsack.h"


/*
 * There are two data files which describe two knapsack instances,
 * one is small and the other is much bigger. The data has the
 * following format:
 *
 *  [knapsack_size][number_of_items]
 *
 *  [value_1] [weight_1]
 *
 *  [value_2] [weight_2]
 *
 *  All numbers are positive.
 *
 *  Answer for the small data set: 2493893
 */
void runKnapsackAssignment() {

  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the Knapsack assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/knapsack_small.txt", std::ifstream::in);
  std::string line;
  std::string number;

  std::getline(ifs, line);
  std::istringstream iss(line);
  iss >> number;
  int capacity = std::stoi(number);
  iss >> number;
  int n_items = std::stoi(number);

  int values [n_items];
  int weights [n_items];

  int i = 0;
  while ( std::getline(ifs, line) ) {
    std::istringstream iss(line);

    iss >> number;
    values[i] = std::stoi(number);
    iss >> number;
    weights[i] = std::stoi(number);

    ++i;
  }

  std::cout << "Read in " << n_items << " data!" << std::endl;
  ifs.close();

  clock_t t0 = clock();
  Knapsack knapsack;
  int solution = knapsack.solve(values, weights, n_items, capacity);
  std::cout << "The maximum value with the capacity of " << capacity
            << " is: " << solution << std::endl;
  std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
            << " ms" << std::endl;

  assert( solution == 2493893 );
  std::cout << "Passed!" << std::endl;
}

void testKnapsack() {

  int values[] = {3, 2, 4, 4};
  int weights[] = {4, 3, 2, 3};
  int capacity = 6;
  int n_items = 4;

  Knapsack knapsack;

  std::cout << "The maximum value with the capacity of " << capacity
            << " is: " << knapsack.solve(values, weights, n_items, capacity)
            << std::endl;
}

int main() {
  testKnapsack();

  runKnapsackAssignment();

  return 0;
}