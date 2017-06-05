//
// Created by jun on 6/5/17.
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
inline Iterator randomSelect(Iterator first, Iterator last, long unsigned n) {

  if ( n > last - first ) {
    throw std::invalid_argument("n is larger than the length of the array!");
  }

  // the following two conditions ensured that the length of the array is
  // bigger than 2.
  if ( n == 0 ) { return first; }
  if ( n == last - first ) { return last - 1; }

  Iterator pivot;

  // randomly pick the pivot

  std::random_device rd;

  /* Random number generator */
  std::default_random_engine generator(rd());

  /* Distribution on which to apply the generator */
  std::uniform_int_distribution<long long unsigned> distribution(0, last - first - 1);

  long long unsigned random_pivot = distribution(generator);
  pivot = first + random_pivot;

  // applying partition
  pivot = myPartition(first, last, pivot);

  if ( pivot - first == n - 1 ) {
    return pivot;
  } else if ( pivot - first > n - 1) {
    return randomSelect(first, pivot, n);
  } else {
    return randomSelect(pivot + 1, last, n - (pivot - first + 1));
  }

}

#endif // SORTING_AND_SELECTION_SELECTION_H