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


//
// test quickSort() -- with pivot using median of three
//
template <class T>
void test_quicksort(T numbers, const T& sorted_numbers, long unsigned N) {

  clock_t t0 = clock();
  quickSort(numbers.begin(), numbers.begin() + N);
  std::cout << "\n-------------------------" << std::endl;
  std::cout << "Testing my median of three random sort algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool quicksort_ok = true;
  for ( int i=0; i< N; ++i) {
//    std::cout << numbers_sorted[i] << " " << numbers[i] << std::endl;
    if ( sorted_numbers[i] != numbers[i] ) { quicksort_ok = false; }
  }

  if (quicksort_ok) {
    std::cout << "correct implementation of quick sort!" << std::endl;
  } else {
    std::cout << "!!!incorrect implementation of quick sort" << std::endl;
  }

}


//
// test rSort()
//
template <class T>
void test_rsort(T numbers, const T& sorted_numbers, long unsigned N) {

  clock_t t0 = clock();
  rSort(numbers.begin(), numbers.begin() + N);
  std::cout << "\n-------------------------" << std::endl;
  std::cout << "Testing my random sort algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool rsort_ok = true;
  for ( int i=0; i< N; ++i) {
//    std::cout << numbers_sorted[i] << " " << numbers[i] << std::endl;
    if ( sorted_numbers[i] != numbers[i] ) { rsort_ok = false; }
  }

  if (rsort_ok) {
    std::cout << "correct implementation of random sort!" << std::endl;
  } else {
    std::cout << "!!!incorrect implementation of random sort" << std::endl;
  }

}


//
// test heapSort()
//
template <class T>
void test_heapsort(T numbers, const T& sorted_numbers, long unsigned N) {

  clock_t t0 = clock();
  heapSort(numbers.begin(), numbers.begin() + N);
  std::cout << "\n-------------------------" << std::endl;
  std::cout << "Testing my heap sort algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  bool heapsort_ok = true;
  for ( int i=0; i< N; ++i) {
//    std::cout << numbers_sorted[i] << " " << numbers[i] << std::endl;
    if ( sorted_numbers[i] != numbers[i] ) { heapsort_ok = false; }
  }

  if (heapsort_ok) {
    std::cout << "correct implementation of heap sort!" << std::endl;
  } else {
    std::cout << "!!!incorrect implementation of heap sort" << std::endl;
  }
}


//
// test rSelect()
//
template <class T>
void test_rselect(T numbers, T& sorted_numbers, long unsigned N, long unsigned n) {

  clock_t t0 = clock();
  std::vector<int>::iterator selected = rSelect(numbers.begin(), numbers.begin() + N, n);
  std::cout << "\n-------------------------" << std::endl;
  std::cout << "Testing my random selection algorithm" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  std::cout << sorted_numbers[n-1] << " " << *selected << std::endl;
  if ( sorted_numbers[n-1] == *selected ) {
    std::cout << "correct implementation of random selection!" << std::endl;
  } else {
    std::cout << "incorrect implementation of random selection!" << std::endl;
  }
}


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

  // use the sort algorithm implemented in <algorithm> library to get a
  // sorted vector
  long unsigned test_length = numbers.end() - numbers.begin();

  std::vector<int> sorted_numbers = numbers;
  clock_t t0 = clock();
  std::sort(sorted_numbers.begin(), sorted_numbers.begin() + test_length);
  std::cout << "\n-------------------------" << std::endl;
  std::cout << "Using default sort algorithm:" << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  // test my implementations

  test_quicksort(numbers, sorted_numbers, test_length);

  test_rsort(numbers, sorted_numbers, test_length);

  test_heapsort(numbers, sorted_numbers, test_length);

  test_rselect(numbers, sorted_numbers, test_length, 10000);

  // check whether the element sequence in the original container has been changed
  std::cout << "\n";
  for ( int i=0; i< 10; ++i) {
    std::cout << numbers[i] << ", ";
  }
  std::cout << std::endl;
}


