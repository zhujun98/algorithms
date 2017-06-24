//
// Created by jun on 5/25/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "sorting.h"
#include "selection.h"
#include "my_unittest.h"


void compareSortingSpeed() {

  std::cout << "\n" << std::string(80, '-') << "\n";
  std::cout << "Compare the speeds of different sorting algorithms...";
  std::cout << "\n" << std::string(80, '-') << "\n" << std::endl;

  std::ifstream fin("../data/QuickSort.txt", std::fstream::in);
  std::vector<int> numbers;
  int number;
  // read data into numbers
  while (fin >> number) { numbers.push_back(number); }
  fin.close();
  std::cout << "Read in " << numbers.size() << " numbers." << std::endl;

  // std::sort()
  std::vector<int> sorted_numbers = numbers;
  clock_t t0 = clock();
  std::sort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing default sort algorithm: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  // quickSort
  sorted_numbers = numbers;
  t0 = clock();
  quickSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my quick sort algorithm: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  // rSort
  sorted_numbers = numbers;
  t0 = clock();
  rSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my random sort algorithm: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  // heapSort
  sorted_numbers = numbers;
  t0 = clock();
  heapSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my heap sort algorithm: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

}

int main()
{
  std::cout << "hello!" << std::endl;

  // test my implementations

  test_quicksort();

  test_rsort();

  test_heapsort();

  test_rselect();

  // compare speed of different sorting algorithm

  compareSortingSpeed();

}


