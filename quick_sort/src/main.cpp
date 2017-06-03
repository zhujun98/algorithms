//
// Created by jun on 5/25/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <time.h>

#include "quicksort.h"


int main()
{
  std::cout << "hello!" << std::endl;

  // a dynamic array to hold values
  std::vector<int> numbers;

  // create an input file stream
  std::ifstream in("../data/QuickSort.txt", std::ios::in);

  int number;
  // read data into numbers
  while (in >> number) { numbers.push_back(number); }
  in.close();

  // show the first 10 numbers
//  for (auto it=numbers.begin(); it <numbers.begin()+10; ++it) {
//    std::cout << *it << std::endl;
//  }

  unsigned long long test_length = numbers.end() - numbers.begin();

  // test the sort algorithm implemented in <algorithm> library
  std::vector<int> numbers_cp = numbers;
  clock_t t0 = clock();
  std::sort(numbers_cp.begin(), numbers_cp.begin() + test_length);
  std::cout << "Using default sort algorithm:" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  // test my quicksort algorithm
  t0 = clock();
  long long total_comparison = quicksort(numbers.begin(), numbers.begin() + test_length);
  std::cout << "Testing my quicksort algorithm" << std::endl;
  std::cout << "Estimated total comparisons: " << total_comparison << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool ok = true;
  for ( int i=0; i< test_length; ++i) {
//    std::cout << numbers_cp[i] << " " << numbers[i] << std::endl;
    if ( numbers_cp[i] != numbers[i] ) { ok = false; }
  }

  if (ok) {
    std::cout << "correct implementation!" << std::endl;
  } else {
    std::cout << "wrong implementation!" << std::endl;
  }

}


