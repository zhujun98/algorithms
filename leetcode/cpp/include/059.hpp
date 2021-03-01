//
// Created by jun on 10/25/17.
//

#ifndef LEECODE_059_H
#define LEECODE_059_H

#include <vector>

/**
 * 59. Spiral Matrix II
 *
 * Given an integer n, generate a square matrix filled with elements
 * from 1 to n2 in spiral order.

 * For example,
 * Given n = 3,

 * You should return the following matrix:
 * [
 *  [ 1, 2, 3 ],
 *  [ 8, 9, 4 ],
 *  [ 7, 6, 5 ]
 * ]
 */
std::vector<std::vector<int>> generateMatrix(int n) {
  std::vector<std::vector<int>> ans(n, std::vector<int>(n, 0));

  int r0 = 0;
  int c0 = 0;
  int r1 = n-1;
  int c1 = n-1;

  int count = 1;
  while (r0 <= r1 && c0 <= c1) {
    for (int i=c0; i<=c1; ++i) ans[r0][i] = count++;
    for (int i=r0+1; i<=r1; ++i) ans[i][c1] = count++;
    if (r0 < r1 && c0 < c1) {
      for (int i=c1-1; i>c0; --i) ans[r1][i] = count++;
      for (int i=r1; i>r0; --i) ans[i][c0] = count++;
    }

    ++r0;
    ++c0;
    --r1;
    --c1;
  }

  return ans;
}

#endif //LEECODE_059_H
