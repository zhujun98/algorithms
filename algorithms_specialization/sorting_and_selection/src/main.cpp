//
// Created by jun on 5/25/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "sorting.h"
#include "selection.h"
#include "my_unittest.h"


void compareSelectionSpeed() {

  std::cout << "\n" << std::string(80, '-') << "\n";
  std::cout << "Compare the speeds of different selection algorithms...";
  std::cout << "\n" << std::string(80, '-') << "\n" << std::endl;

  std::ifstream fin("../data/QuickSort.txt", std::fstream::in);
  std::vector<int> numbers;
  int number;
  // read data into numbers
  while (fin >> number) { numbers.push_back(number); }
  fin.close();
  std::cout << "Read in " << numbers.size() << " numbers." << std::endl;

  int index = 499;
  // std::sort()
  std::vector<int> sorted_numbers = numbers;
  clock_t t0 = clock();
  std::sort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing STL::sort for selection: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  int expected = sorted_numbers[index];

  // std::nth_element()
  sorted_numbers = numbers;
  t0 = clock();
  std::nth_element(sorted_numbers.begin(), sorted_numbers.begin() + 499, sorted_numbers.end());
  std::cout << "\nUsing STL::nth_element for selection: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  assert ( expected == sorted_numbers[index] );

  // rSelect()
  sorted_numbers = numbers;
  t0 = clock();
  rSelect(sorted_numbers.begin(), sorted_numbers.end(), 500);
  std::cout << "\nUsing my random selection implementation: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  assert ( expected == sorted_numbers[index] );

  // m3Select()
  sorted_numbers = numbers;
  t0 = clock();
  m3Select(sorted_numbers.begin(), sorted_numbers.end(), 500);
  std::cout << "\nUsing my median-of-three selection implementation: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;

  assert ( expected == sorted_numbers[index] );

}

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
  std::cout << "\nUsing STL::sort for sorting: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;
  std::vector<int> expected = sorted_numbers;

  // quickSort
  sorted_numbers = numbers;
  t0 = clock();
  quickSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my quick sort implementation: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;
  assert ( expected == sorted_numbers );


  // rSort
  sorted_numbers = numbers;
  t0 = clock();
  rSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my random sort implementation: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;
  assert ( expected == sorted_numbers );

  // heapSort
  sorted_numbers = numbers;
  t0 = clock();
  heapSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my heap sort implementation: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;
  assert ( expected == sorted_numbers );

  // mergeSort
  sorted_numbers = numbers;
  t0 = clock();
  mergeSort(sorted_numbers.begin(), sorted_numbers.end());
  std::cout << "\nUsing my merge sort implementation: "
            << 1.0*(clock() - t0)/CLOCKS_PER_SEC << " s" << std::endl;
  assert ( expected == sorted_numbers );
}

int main()
{
  std::cout << "hello!" << std::endl;

  // test my implementations

  testQuickSort();
  testRSort();
  testHeapSort();
  testMergeSort();

  testRSelect();
  testM3Select();

  // compare speed of different sorting algorithm

  compareSortingSpeed();

  compareSelectionSpeed();
}


