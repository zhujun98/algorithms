//
// Created by jun on 5/25/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <time.h>

#include "sorting.h"
#include "selection.h"


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
  std::vector<int> numbers_cp1 = numbers;
  clock_t t0 = clock();
  std::sort(numbers_cp1.begin(), numbers_cp1.begin() + test_length);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Using default sort algorithm:" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  // test my sorting algorithm
  std::vector<int> numbers_cp2 = numbers;
  t0 = clock();
  long long total_comparison = quicksort(
      numbers_cp2.begin(), numbers_cp2.begin() + test_length);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Testing my sorting algorithm" << std::endl;
  std::cout << "Estimated total comparisons: " << total_comparison << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool sorting_ok = true;
  for ( int i=0; i< test_length; ++i) {
//    std::cout << numbers_cp1[i] << " " << numbers_cp2[i] << std::endl;
    if ( numbers_cp1[i] != numbers_cp2[i] ) { sorting_ok = false; }
  }

  if (sorting_ok) {
    std::cout << "correct implementation of sorting!" << std::endl;
  } else {
    std::cout << "incorrect implementation of sorting!" << std::endl;
  }

  // test my selection algorithm
  t0 = clock();
  long unsigned n = 709;
  std::vector<int>::iterator selected = randomSelect(numbers.begin(), numbers.end(), n);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Testing my selection algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool selection_ok;
  std::cout << numbers_cp1[n-1] << " " << *selected << std::endl;
  if ( numbers_cp1[n-1] == *selected ) {
    selection_ok = true;
    std::cout << "correct implementation of selection!" << std::endl;
  } else {
    selection_ok = false;
    std::cout << "incorrect implementation of selection!" << std::endl;
  }

}


