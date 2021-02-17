//
// Created by jun on 5/25/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>

#include "inversion_count.h"


//
// This file contains all of the 100,000 integers between 1 and 100,000
// (inclusive) in some order, with no integer repeated. Your task is to
// compute the number of inversions in the file given, where the ith row
// of the file indicates the ith entry of an array.
//
// Answer: 2407905288
//
void runInversionCountAssignment() {

  std::vector<int> numbers;

  // create an input file stream
  std::ifstream ifs("../data/IntegerArray.txt", std::ifstream::in);

  // read numbers from the input file
  int number;
  while (ifs >> number) { numbers.push_back(number); }
  ifs.close();

  std::cout << "No. of integers in read from the input file: "
            << numbers.size() << std::endl;

  clock_t t0;
  t0 = clock();
  long count = inversionCountBruteForce(numbers);
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  std::cout << "Number of inversions (by brute force) is: " << count << std::endl;

  t0 = clock();
  count = quickInversion(numbers);
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  std::cout << "Number of inversions (by splitting) is: " << count << std::endl;
}

int main() {
  std::cout << "hello!" << std::endl;

  runInversionCountAssignment();

  return 0;
}

