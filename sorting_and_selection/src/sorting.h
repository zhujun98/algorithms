//
// Created by jun on 5/25/17.
//
// Implementations of sorting algorithms
//
// TODO: implement the heapsort
//

#ifndef SORTING_AND_SELECTION_SORTING_H
#define SORTING_AND_SELECTION_SORTING_H

#include <iostream>

#include "utilities.h"


//
// implementation of quicksort method with random pivot:
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void rSort(Iterator first, Iterator last) {

  if ( last - first <= 1 ) { return; }

  // there are two elements
  if ( last - first == 2 ) {
    myPartition(first, last, first);
    return;
  }

  std::random_device rd;

  /* Random number generator */
  std::default_random_engine generator(rd());

  /* Distribution on which to apply the generator */
  std::uniform_int_distribution<long unsigned> distribution(0, last - first - 1);

  Iterator pivot, boundary;

  long unsigned random_pivot = distribution(generator);
  pivot = first + random_pivot;

  boundary = myPartition(first, last, pivot);

  // recursive sort the left and right array
  if ( boundary - first > 1 ) { rSort(first, boundary); }
  if ( last - boundary - 1 > 1 ) { rSort(boundary + 1, last); }

  return;
}


//
// implementation of quicksort method with pivot being the median among the
// first, last and middle elements
//
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void quicksort(Iterator first, Iterator last) {

  if ( last - first <= 1 ) { return; }

  // there are two elements
  if ( last - first == 2 ) {
    myPartition(first, last, first);
    return;
  }

  Iterator pivot, boundary;

  int middle_index = (last - first - 1)/2;
  pivot = medianOfThree(first, first + middle_index, last - 1);

  boundary = myPartition(first, last, pivot);

  // recursive sort the left and right array
  if ( boundary - first > 1 ) { quicksort(first, boundary); }
  if ( last - boundary - 1 > 1 ) { quicksort(boundary + 1, last); }

  return;
}

//
// implementation of heapsort algorithm
//
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void heapsort(Iterator first, Iterator last) {


}

#endif // SORTING_AND_SELECTION_SORTING_H
