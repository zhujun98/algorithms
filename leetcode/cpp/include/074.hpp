//
// Created by jun on 10/18/17.
//

#ifndef LEECODE_074_H
#define LEECODE_074_H

#include <vector>

/**
 * 74. Search a 2D Matrix
 *
 * Write an efficient algorithm that searches for a value in an m x n
 * matrix. This matrix has the following properties:

 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of
 * the previous row.
 *
 * For example,

 * Consider the following matrix:

 * [
    [1,   3,  5,  7],
    [10, 11, 16, 20],
    [23, 30, 34, 50]
 * ]
 * Given target = 3, return true.
 */

// binary search
// time complexity O(log(MN)), space complexity O(1)
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
  if (matrix.size() == 0 || matrix[0].size() == 0) return false;
  int m = matrix.size();
  int n = matrix[0].size();

  int left = 0;
  int right = m*n - 1;

  while (left < right) {
    int mid = (left + right)/2;
    if (matrix[mid/n][mid%n] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return (matrix[right/n][right%n] == target);
}

#endif //LEECODE_074_H
