//
// Created by jun on 5/25/17.
//
// This is an implementation of the "quicksort" algorithms taught in the
// Stanford course in Coursera by Tim Roughgarden
//
// TODO: fix the *char argument issue in the function quicksort()
//

#ifndef SORTING_AND_SELECTION_SORTING_H
#define SORTING_AND_SELECTION_SORTING_H

#include <iostream>

#include "utilities.h"


//
// implementation of quicksort method
// Sort the elements in the range [first, last) into ascending order.
// Note: The return value is for the assignment in the course.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
// @return count: estimated number of total comparisons.
//                It is calculated by the following method: 
//                We assume there is m-1 comparisons in a recursive call on a 
//                sub-array of length m. (This is because the pivot element is 
//                compared to each of the other m−1 elements in the sub-array 
//                in this recursive call.)
//
template <typename Iterator>
inline int quicksort(Iterator first, Iterator last, char* method = "median_of_three") {

  long long count = 0;

  if ( last - first <= 1 ) { return count; }

  // there are two elements
  if ( last - first == 2 ) {
    myPartition(first, last, first);
    count += 1;
    return count;
  }

  Iterator pivot;
  if ( method == "first") {
    pivot = first;
  } else if ( method == "last") {
    pivot = last - 1;
  } else if ( method == "median_of_three") {
    int middle_index = (last - first - 1)/2;
    pivot = medianOfThree(first, first + middle_index, last - 1);
  } else {
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0, last - first - 1);

    long long unsigned random_pivot = distribution(generator);
    pivot = first + random_pivot;
  }

  pivot = myPartition(first, last, pivot);

  // recursive sort the left and right array
  if ( pivot - first > 1 ) { count += quicksort(first, pivot); }
  if ( last - pivot - 1 > 1 ) { count += quicksort(pivot + 1, last); }

  count += last - first - 1;

  return count;
}


#endif // SORTING_AND_SELECTION_SORTING_H
