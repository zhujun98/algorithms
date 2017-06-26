//
// Created by jun on 5/25/17.
//
// Implementations of sorting algorithms
//
// Functions:
// - rSort()
// - quickSort()
// - heapSort()
// - mergeSort()
//

#ifndef SORTING_AND_SELECTION_SORTING_H
#define SORTING_AND_SELECTION_SORTING_H

#include <iostream>
#include <queue>
#include <list>
#include <functional>

#include "utilities.h"


//
// implementation of quick sort method with random pivot:
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void rSort(Iterator first, Iterator last) {

  if ( last - first <= 1 ) { return; }

  // the function works without this condition, but will be slower!
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
// implementation of quick sort method with pivot being the median among the
// first, last and middle elements
//
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void quickSort(Iterator first, Iterator last) {

  if ( last - first <= 1 ) { return; }

  if ( last - first == 2 ) {
    myPartition(first, last, first);
    return;
  }

  Iterator pivot, boundary;

  int middle_index = (last - first - 1)/2;
  pivot = medianOfThree(first, first + middle_index, last - 1);

  boundary = myPartition(first, last, pivot);

  // recursive sort the left and right array
  if ( boundary - first > 1 ) { quickSort(first, boundary); }
  if ( last - boundary - 1 > 1 ) { quickSort(boundary + 1, last); }

  return;
}

//
// implementation of heap sort algorithm
//
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void heapSort(Iterator first, Iterator last) {

  typedef typename std::iterator_traits<Iterator>::value_type T;

  std::priority_queue<T, std::vector<T>, std::greater<T>> my_heap;

  // initialize a priority_queue (heap)
  for (Iterator i=first; i!=last; ++i) {
    my_heap.push(*i);
  }

  // change the value in the original container
  for (Iterator i=first; i!=last; ++i) {
    *i = my_heap.top();
    my_heap.pop();
  }

//  print_queue(my_heap);
}


//
// implementation of merge sort algorithm
//
// Sort the elements in the range [first, last) into ascending order.
//
// @param first: iterator to the first position
// @param last: iterator to the last position
//
template <class Iterator>
inline void mergeSort(Iterator first, Iterator last) {

  std::size_t length = last - first;

  if ( length == 1 ) { return; }

  std::size_t middle = length / 2;

  mergeSort(first, first + middle);
  mergeSort(first + middle, last);

  // merge the two sorted half arrays into a queue
  typedef typename std::iterator_traits<Iterator>::value_type T;

  // make a copy of initial container
  // this initialization is faster than copying the elements one by one
  std::vector<T> copy(first, last);

  Iterator i = copy.begin(), j = i + middle;
  for ( auto k = first; k != last; ++k ) {
    if ( i == copy.begin() + middle ) {
      *k = *j;
      ++j;
    } else if ( j == copy.end() ) {
      *k = *i;
      ++i;
    } else {
      if ( *i <= *j ) {
        *k = *i;
        ++i;
      } else {
        *k = *j;
        ++j;
      }
    }
  }

}

template <class Iterator>
inline void merge(Iterator first, Iterator middle, Iterator last) {

}

#endif // SORTING_AND_SELECTION_SORTING_H
