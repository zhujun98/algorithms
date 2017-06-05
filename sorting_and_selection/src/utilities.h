//
// Created by jun on 6/5/17.
//

#ifndef SORTING_AND_SELECTION_UTILITIES_H
#define SORTING_AND_SELECTION_UTILITIES_H


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


#endif // SORTING_AND_SELECTION_UTILITIES_H
