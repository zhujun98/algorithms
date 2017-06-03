//
// Created by jun on 5/25/17.
//
// This is an implementation of the "quicksort" algorithms taught in the
// Stanford course in Coursera by Tim Roughgarden
//
// TODO: fix the *char argument issue in the function quicksort()
//

#ifndef QUICK_SORT_QUICKSORT_H
#define QUICK_SORT_QUICKSORT_H

#include <iostream>
#include <random>


//
// swap the referenced value of two iterators
//
// @param first: first iterator
// @param second: second iterator
//
template <typename Iterator>
inline void mySwap(Iterator first, Iterator second) {
  auto tmp = *first;
  *first = *second;
  *second = tmp;

  return;
}


//
// return the iterator to the position with the median value
//
// @param first: iterator to the first position
// @param pivot: iterator to the middle position. For an array with 2m
//               elements, it refers to the mth element.
// @param last: iterator to the last position
//
template <typename Iterator>
inline Iterator medianOfThree(const Iterator first, const Iterator middle, const Iterator last) {
  if ( *last > *first ) {
    if ( *first > *middle ) {
      return first;
    } else {
      if ( *middle > *last ) {
        return last;
      } else {
        return middle;
      }
    }
  } else {
    if ( *last > *middle ) {
      return last;
    } else {
      if ( *middle > *first ) {
        return first;
      } else {
        return middle;
      }
    }
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
    if ( *first > *(first + 1) ) { mySwap(first, first + 1); }
    return first;
  }

  //
  // if there are more than two elements in the array:
  //

  // first swap the first element and the pivot
  if ( first != pivot ) { mySwap(first, pivot); }


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
        mySwap(boundary, unpartitioned_start);
        boundary += 1;
      }
    }
  }

  // move the pivot to the correct place

  if ( *first > *boundary ) {
    // this happens when the pivot is greater than all the rest elements
    mySwap(first, boundary);
    return boundary;
  } else if ( boundary - first == 1 ) {
    // this happens when the pivot is smaller than all the rest elements
    return first;
  } else {
    mySwap(first, boundary - 1);
    return boundary - 1;
  }

}


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


#endif //QUICK_SORT_QUICKSORT_H
