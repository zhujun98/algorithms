//
// Created by jun on 5/25/17.
// Calculate the number of inversions in a 1D array by using two algorithms:
// the brute force and the splitting algorithm
//
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "inversion_count.h"


int main()
{
  std::cout << "hello!" << std::endl;

  // a dynamic array to hold values
  std::vector<int> numbers;

  // create an input file stream
  std::ifstream in("../data/IntegerArray.txt", std::ios::in);

  // read numbers from the input file
  int number;
  while (in >> number) { numbers.push_back(number); }
  in.close();

  // show the first 10 numbers
  std::cout << "No. of integers in read from the input file: "
            << numbers.size() << std::endl;

//  for (int i=0; i < 10; ++i)
//  {
//    std::cout << numbers[i] << std::endl;
//  }

  std::vector<int> numbers_sub (numbers.begin(), numbers.end());

  clock_t t0;
  t0 = clock();
  long count = inversionCountBruteForce(numbers_sub);
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  std::cout << "Number of inversions (by brute force) is: " << count << std::endl;

  t0 = clock();
  count = quickInversion(numbers_sub);
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  std::cout << "Number of inversions (by splitting) is: " << count << std::endl;

  return 0;

}

