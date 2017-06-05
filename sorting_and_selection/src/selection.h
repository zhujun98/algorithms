//
// Created by jun on 6/5/17.
//
// Implementations of selecting algorithms
//

#ifndef SORTING_AND_SELECTION_SELECTION_H
#define SORTING_AND_SELECTION_SELECTION_H


#include <iostream>
#include <random>

#include "utilities.h"


//
// implementation of "random selection" method
// Select the nth biggest element in the range [first, last).
//
//
template <class Iterator>
inline Iterator rSelect(Iterator first, Iterator last, long unsigned n) {

  if ( n > last - first ) {
    throw std::invalid_argument("n is larger than the length of the array!");
  }

  // the following two conditions ensured that the length of the array is
  // bigger than 2.
  if ( n == 0 || n == 1 ) { return first; }
  if ( n == last - first ) { return last - 1; }

  Iterator pivot, boundary;

  // randomly pick the pivot

  std::random_device rd;

  /* Random number generator */
  std::default_random_engine generator(rd());

  /* Distribution on which to apply the generator */
  std::uniform_int_distribution<long long unsigned> distribution(0, last - first - 1);

  long long unsigned random_pivot = distribution(generator);
  pivot = first + random_pivot;

  // applying partition
  boundary = myPartition(first, last, pivot);

  if ( boundary - first == n - 1 ) {
    return boundary;
  } else if ( boundary - first > n - 1) {
    // Important !!!
    // Here one must use "boundary + 1" as the second argument since "boundary - 1"
    // is not guaranteed to be the largest number int the array [first, boundary).
    // If it happens that "boundary - first - 1 == n - 1", the algorithm will return
    // "boundary - 1" if "boundary" were used as the second argument.
    return rSelect(first, boundary + 1, n);
  } else {
    return rSelect(boundary, last, n - (boundary - first));
  }

}

#endif // SORTING_AND_SELECTION_SELECTION_H