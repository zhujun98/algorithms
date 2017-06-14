//
// Created by jun on 5/25/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
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
  for (auto it=numbers.begin(); it <numbers.begin()+10; ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  long test_length = numbers.end() - numbers.begin();

  //
  // test the sort algorithm implemented in <algorithm> library
  //
  std::vector<int> numbers_cp1 = numbers;
  clock_t t0 = clock();
  std::sort(numbers_cp1.begin(), numbers_cp1.begin() + test_length);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Using default sort algorithm:" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  //
  // test my quicksort (median of three)
  //
  std::vector<int> numbers_cp2 = numbers;
  t0 = clock();
  quicksort(numbers_cp2.begin(), numbers_cp2.begin() + test_length);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Testing my median of three sorting algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool quicksort_ok = true;
  for ( int i=0; i< test_length; ++i) {
//    std::cout << numbers_cp1[i] << " " << numbers_cp2[i] << std::endl;
    if ( numbers_cp1[i] != numbers_cp2[i] ) { quicksort_ok = false; }
  }

  if (quicksort_ok) {
    std::cout << "correct implementation of sorting!" << std::endl;
  } else {
    std::cout << "incorrect implementation of sorting!" << std::endl;
  }

  //
  // test my rSort
  //
  std::vector<int> numbers_cp3 = numbers;
  t0 = clock();
  rSort(numbers_cp3.begin(), numbers_cp3.begin() + test_length);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Testing my random sorting algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool rsort_ok = true;
  for ( int i=0; i< test_length; ++i) {
//    std::cout << numbers_cp1[i] << " " << numbers_cp2[i] << std::endl;
    if ( numbers_cp1[i] != numbers_cp2[i] ) { rsort_ok = false; }
  }

  if (rsort_ok) {
    std::cout << "correct implementation of sorting!" << std::endl;
  } else {
    std::cout << "incorrect implementation of sorting!" << std::endl;
  }

  // test my selection algorithm

  t0 = clock();
  long unsigned n = 10000;
  std::vector<int>::iterator selected = rSelect(numbers.begin(), numbers.begin() + test_length, n);
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

  for ( int i=0; i< 10; ++i) {
    std::cout << numbers[i] << ", ";
  }
  std::cout << std::endl;
}


