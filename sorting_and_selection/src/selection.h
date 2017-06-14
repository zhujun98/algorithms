//
// Created by jun on 6/5/17.
//
// Implementations of selecting algorithms
//

#ifndef SORTING_AND_SELECTION_SELECTION_H
#define SORTING_AND_SELECTION_SELECTION_H


#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <list>
#include <iterator>

#include "utilities.h"


//
// implementation of "random selection" method
// Select the nth smallest element in the range [first, last).
// Note:: the original container will be sorted.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
// @param n: the rank of the number (smallest)
//
// @return: iterator to the selected number
//
template <class Iterator>
inline Iterator rSelect_inplace(Iterator first, Iterator last, long unsigned n) {

  if ( n < 1 || n > last - first ) {
    throw std::invalid_argument("Out of range: n!");
  }

  // if the array has only 1 element
  if ( n == 1 && last - first == 1 ) { return first; }

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
    return boundary;
  } else if ( boundary - first > n - 1) {
    // Important !!!
    // Here one must use "boundary + 1" as the second argument since "boundary - 1"
    // is not guaranteed to be the largest number int the array [first, boundary).
    // If it happens that "boundary - first - 1 == n - 1", the algorithm will return
    // "boundary - 1" if "boundary" were used as the second argument.
    return rSelect_inplace(first, boundary + 1, n);
  } else {
    return rSelect_inplace(boundary, last, n - (boundary - first));
  }

}


//
// implementation of "random selection" method
// Select the nth smallest element in the range [first, last).
//
// @param first: iterator to the first position
// @param last: iterator to the last position
// @param n: the rank of the number (smallest)
//
// @return: iterator to the selected number
//
template <class Iterator>
inline Iterator rSelect(Iterator first, Iterator last, long unsigned n) {

  // copy the elements between first and last in the original container into a vector
  std::vector<typename std::iterator_traits<Iterator>::value_type> data(first, last);

  // another way to copy a container
//  const size_t N = last - first;
//  std::vector<typename std::iterator_traits<Iterator>::value_type> data(N);
//  std::copy(first, last, data.begin());

  return rSelect_inplace(data.begin(), data.end(), n);
}

#endif // SORTING_AND_SELECTION_SELECTION_H