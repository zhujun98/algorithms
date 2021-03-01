//
// Created by jun on 10/24/17.
//

#ifndef LEECODE_054_H
#define LEECODE_054_H

#include <vector>

/**
 * 54. Spiral Matrix
 *
 * Given a matrix of m x n elements (m rows, n columns), return all
 * elements of the matrix in spiral order.

 * For example,
 * Given the following matrix:

 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 *
 * You should return [1,2,3,6,9,8,7,4,5].
 */

// time complexity O(MN)
// space complexity O(N): for storing the answer
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
  std::vector<int> ans;
  if (matrix.empty()) return ans;

  int m = matrix.size();
  int n = matrix[0].size();

  // uppper left corner
  int r0 = 0;
  int c0 = 0;
  // lower right corner
  int r1 = m - 1;
  int c1 = n - 1;

  while (r1 >= r0 && c1 >= c0) {
    for (int i=c0; i<=c1; ++i) ans.push_back(matrix[r0][i]);
    for (int i=r0+1; i<=r1; ++i) ans.push_back(matrix[i][c1]);
    if (r1 > r0 && c1 > c0) {
      for (int i=c1-1; i>c0; --i) ans.push_back(matrix[r1][i]);
      for (int i=r1; i>r0; --i) ans.push_back(matrix[i][c0]);
    } // else the layer has only one row or one column
    ++r0;
    ++c0;
    --r1;
    --c1;
  }

  return ans;
}

#endif //LEECODE_054_H
