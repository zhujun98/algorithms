//
// Created by jun on 5/25/17.
//
// Implementations of counting inversions in a 1D array.
//
// functions:
//   - inversionCountBruteForce();
//   - splitInversion();
//   - quickInversion();
//
#ifndef INVERSION_COUNT_INVERSION_COUNT_H
#define INVERSION_COUNT_INVERSION_COUNT_H

#include <iostream>
#include <algorithm>


//
// count the number of inversions using brute force (double for-loops)
//
// @param a: input 1D array
//
template<typename T>
inline long inversionCountBruteForce(const T& a) {
  long count = 0;

  for (int i=0; i<a.size()-1; ++i) {
    for (int j=i+1; j<a.size(); ++j) {
      if (a[i] > a[j]) { ++count; }
    }
  }

  return count;
}


//
// computer the No. of split inversions in two arrays
//
// @param left: left 1D array
// @param right: right 1D array
//
// @return: number of split inversions
//
template <typename T>
inline long splitInversion(const T& left, const T& right) {
  long count = 0;

  int left_size = left.size();
  int right_size = right.size();

  if ( left_size < 1 || right_size < 1 ) { return 0; }

  int j = 0;
  int k = 0;
  for (int i=0; i<left_size + right_size; ++i) {
    if (left[j] > right[k]) {
      ++k;
      // If an element j in the left array is bigger than the element k
      // in the right array, it means that the element j and the rest
      // elements after it in the left array are all inversions to the
      // element k in the right array.
      count += left_size - j;
      if (k == right_size) { break; }
    } else if (left[j] < right[k]) {
      ++j;
      if (j == left_size) { break; }
    }

  }

  return count;
}

//
// compute the number of inversions by split algorithm
//
// @param a: input 1D array
//
// @return: number of inversions
//
template <typename T>
inline long quickInversion(const T& a) {
  long count = 0;

  if (a.size() < 2) { return 0; }

  int split = a.size()/2;

  // divide the original vector into the left and right arrays
  T left (a.begin(), a.begin() + split);
  T right (a.begin() + split, a.end());

  // recursively calculate the number of inversions in the left and right arrays
  count += quickInversion(left);
  count += quickInversion(right);

  // Add the number of split inversions between the left and right arrays
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());
  count += splitInversion(left, right);

  return count;
}

#endif //INVERSION_COUNT_INVERSION_COUNT_H
