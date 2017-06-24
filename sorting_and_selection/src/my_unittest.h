//
// Created by jun on 6/24/17.
//
// Functions:
// - testQuickSort()
// - testRSort()
// - testHeapsort()
// - testRSelect()
// - testM3Select()
//

#ifndef SORTING_AND_SELECTION_MY_UNITTEST_H
#define SORTING_AND_SELECTION_MY_UNITTEST_H

#include <iostream>
#include <vector>

#include "utilities.h"
#include "selection.h"
#include "sorting.h"


//
// test quickSort()
//
void testQuickSort() {
  std::cout << "\nTesting my median-of-three random sort implementation..." << std::endl;

  std::vector<int> numbers  = {0, 9, 8, 2, 1, 3, 5, 7, 6, 4};
  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  quickSort(numbers.begin(), numbers.end());

  if ( numbers == expected ) {
    std::cout << "Passed!" << std::endl;
  } else {
    std::cout << "Failed!!!" << std::endl;
    std::cout << "The output is: " << std::endl;
    printContainer(numbers);
    std::cout << "The correct result is: " << std::endl;
    printContainer(expected);
  }

}


//
// test rSort()
//
void testRSort() {
  std::cout << "\nTesting my random sort implementation..." << std::endl;

  std::vector<int> numbers  = {0, 9, 8, 2, 1, 3, 5, 7, 6, 4};
  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  rSort(numbers.begin(), numbers.end());

  if ( numbers == expected ) {
    std::cout << "Passed!" << std::endl;
  } else {
    std::cout << "Failed!!!" << std::endl;
    std::cout << "The output is: " << std::endl;
    printContainer(numbers);
    std::cout << "The correct result is: " << std::endl;
    printContainer(expected);
  }
}


//
// test heapSort()
//
void testHeapSort() {

  std::cout << "\nTesting my heap sort implementation..." << std::endl;

  std::vector<int> numbers  = {0, 9, 8, 2, 1, 3, 5, 7, 6, 4};
  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  heapSort(numbers.begin(), numbers.end());

  if ( numbers == expected ) {
    std::cout << "Passed!" << std::endl;
  } else {
    std::cout << "Failed!!!" << std::endl;
    std::cout << "The output is: " << std::endl;
    printContainer(numbers);
    std::cout << "The correct result is: " << std::endl;
    printContainer(expected);
  }
}


//
// test rSelect()
//
void testRSelect() {
  std::cout << "\nTesting my random selection implementation..." << std::endl;

  std::vector<int> original_numbers  = {0, 9, 8, 2, 1, 3, 5, 7, 6, 4};
  std::vector<int> numbers;
  std::vector<int> expected = {0, 4, 9};
  std::vector<int> result;

  numbers = original_numbers;
  rSelect(numbers.begin(), numbers.end(), 1);
  result.push_back(*numbers.begin());

  numbers = original_numbers;
  rSelect(numbers.begin(), numbers.end(), 5);
  result.push_back(numbers[4]);

  numbers= original_numbers;
  rSelect(numbers.begin(), numbers.end(), numbers.size());
  result.push_back(*(numbers.end() - 1));

  if ( result != expected ) {
    std::cout << "Failed!!!" << std::endl;
    std::cout << "The output is: " << std::endl;
    printContainer(result);
    std::cout << "The correct result is: " << std::endl;
    printContainer(expected);
  } else {
    std::cout << "Passed!" << std::endl;
  }
}


//
// test M3Select()
//
void testM3Select() {
  std::cout << "\nTesting my median-of-three selection implementation..."
            << std::endl;

  std::vector<int> original_numbers  = {0, 9, 8, 2, 1, 3, 5, 7, 6, 4};
  std::vector<int> numbers;
  std::vector<int> expected = {0, 4, 9};
  std::vector<int> result;

  numbers = original_numbers;
  m3Select(numbers.begin(), numbers.end(), 1);
  result.push_back(*numbers.begin());

  numbers = original_numbers;
  m3Select(numbers.begin(), numbers.end(), 5);
  result.push_back(numbers[4]);

  numbers= original_numbers;
  m3Select(numbers.begin(), numbers.end(), numbers.size());
  result.push_back(*(numbers.end() - 1));

  if ( result != expected ) {
    std::cout << "Failed!!!" << std::endl;
    std::cout << "The output is: " << std::endl;
    printContainer(result);
    std::cout << "The correct result is: " << std::endl;
    printContainer(expected);
  } else {
    std::cout << "Passed!" << std::endl;
  }
}


#endif //SORTING_AND_SELECTION_MY_UNITTEST_H
