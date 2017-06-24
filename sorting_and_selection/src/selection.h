//
// Created by jun on 6/5/17.
//
// Implementations of selecting algorithms
//
// Functions:
// - rSelect()
// - m3Select()
//

#ifndef SORTING_AND_SELECTION_SELECTION_H
#define SORTING_AND_SELECTION_SELECTION_H


#include <iostream>
#include <random>
#include <vector>
#include <iterator>

#include "utilities.h"


//
// implementation of "random selection" method
//
// put the nth smallest element in the range [first, last) to the nth
// position in the container.
// Note: the original container will be changed!
//
// @param first: iterator to the first position
// @param last: iterator to the last position
// @param n: the rank of the number (smallest)
//
// @return: iterator to the selected number
//
template <class Iterator>
inline void rSelect(Iterator first, Iterator last, long unsigned n) {

  if ( n < 1 || n > last - first ) {
    throw std::invalid_argument("Out of range: n!");
  }

  // if the array has only 1 element
  if ( last - first == 1 ) { return; }

  // the function works without this condition, but will be slower!
  if ( last - first == 2) {
    myPartition(first, last, first);
    return;
  }

  Iterator pivot, boundary;

  // randomly pick the pivot

  std::random_device rd;

  /* Random number generator */
  std::default_random_engine generator(rd());

  /* Distribution on which to apply the generator */
  std::uniform_int_distribution<long unsigned> distribution(0, last - first - 1);

  long unsigned random_pivot = distribution(generator);
  pivot = first + random_pivot;

  // applying partition
  boundary = myPartition(first, last, pivot);

  if ( boundary - first == n - 1 ) {
    return;
  } else if ( boundary - first > n - 1) {
    // Important !!!
    // Here one must use "boundary + 1" as the second argument since "boundary - 1"
    // is not guaranteed to be the largest number int the array [first, boundary).
    // If it happens that "boundary - first - 1 == n - 1", the algorithm will return
    // "boundary - 1" if "boundary" were used as the second argument.
    rSelect(first, boundary + 1, n);
  } else {
    rSelect(boundary, last, n - (boundary - first));
  }

}


//
// implementation of "random selection" method with pivot being the median
// among the first, last and middle elements. Different from sorting, this
// implementation is slower than the implementation using random pivots.
//
// put the nth smallest element in the range [first, last) to the nth
// position in the container.
// Note: the original container will be changed!
//
// @param first: iterator to the first position
// @param last: iterator to the last position
// @param n: the rank of the number (smallest)
//
// @return: iterator to the selected number
//
template <class Iterator>
inline void m3Select(Iterator first, Iterator last, long unsigned n) {

  if ( n < 1 || n > last - first ) {
    throw std::invalid_argument("Out of range: n!");
  }

  // if the array has only 1 element
  if ( last - first == 1 ) { return; }

  if ( last - first == 2) {
    myPartition(first, last, first);
    return;
  }

  Iterator pivot, boundary;

  int middle_index = (last - first - 1)/2;
  pivot = medianOfThree(first, first + middle_index, last - 1);

  // applying partition
  boundary = myPartition(first, last, pivot);

  if ( boundary - first == n - 1 ) {
    return;
  } else if ( boundary - first > n - 1) {
    // Important !!!
    // Here one must use "boundary + 1" as the second argument since "boundary - 1"
    // is not guaranteed to be the largest number int the array [first, boundary).
    // If it happens that "boundary - first - 1 == n - 1", the algorithm will return
    // "boundary - 1" if "boundary" were used as the second argument.
    m3Select(first, boundary + 1, n);
  } else {
    m3Select(boundary, last, n - (boundary - first));
  }

}


#endif // SORTING_AND_SELECTION_SELECTION_H