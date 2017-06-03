//
// Created by jun on 5/25/17.
//
// This is an implementation of the "quicksort" algorithms taught in the
// Stanford course in Coursera by Tim Roughgarden
//

#ifndef QUICK_SORT_QUICKSORT_H
#define QUICK_SORT_QUICKSORT_H

#include <iostream>
#include <random>


namespace {

  //
  // swap the referenced value of two iterators
  //
  // @param first: first iterator
  // @param second: second iterator
  //
  template <typename Iterator>
  inline void partitionSwap(Iterator first, Iterator second) {
    auto tmp = *first;
    *first = *second;
    *second = tmp;

    return;
  }
}

//
// First move the pivot to the first place; then partition the rest elements
// into left (less than pivot) and right (greater than pivot) parts; finally
// move the pivot to the middle.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
// @param pivot: iterator to the position of the pivot
//
template <typename Iterator>
inline Iterator myPartition(Iterator first, Iterator last, Iterator pivot) {

  if ( last - first <= 1 ) { return first; }

  // there are only two elements
  if ( last - first == 2 ) {
    if ( *first > *(first + 1) ) { partitionSwap(first, first + 1); }
    return first;
  }

  //
  // if there are more than two elements in the array:
  //

  // first swap the first element and the pivot
  if ( first != pivot ) { partitionSwap(first, pivot); }


  // partition the rest elements into too parts
  Iterator boundary, unpartitioned_start;

  boundary = first + 1;
  unpartitioned_start = first + 1;

  while ( unpartitioned_start != last - 1) {

    if ( *first > *boundary ) {
      // this is an very important step and it is not mentioned in the
      // Coursera Stanford course
      boundary += 1;
      unpartitioned_start += 1;
    } else {
      unpartitioned_start += 1;
      if ( *first > *unpartitioned_start ) {
        partitionSwap(boundary, unpartitioned_start);
        boundary += 1;
      }
    }
  }

  // move the pivot to the correct place

  if ( *first > *boundary ) {
    // this happens when the pivot is greater than all the rest elements
    partitionSwap(first, boundary);
    return boundary;
  } else if ( boundary - first == 1 ) {
    // this happens when the pivot is smaller than all the rest elements
    return first;
  } else {
    partitionSwap(first, boundary - 1);
    return boundary - 1;
  }

}

//
// implementation of quicksort method
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <typename Iterator>
inline void quicksort(Iterator first, Iterator last) {

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
  std::uniform_int_distribution<long long unsigned> distribution(0, last - first - 1);

  long long unsigned random_pivot= distribution(generator);
  Iterator pivot = first + random_pivot;

  pivot = myPartition(first, last, pivot);

  // recursive sort the left and right array
  if ( pivot - first > 1 ) { quicksort(first, pivot); }
  if ( last - pivot - 1 > 1 ) { quicksort(pivot + 1, last); }

  return;
}


#endif //QUICK_SORT_QUICKSORT_H
