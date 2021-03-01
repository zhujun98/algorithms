//
// Created by jun on 2/20/18.
//

#ifndef LEECODE_062_H
#define LEECODE_062_H

/**
 * 62. Unique Paths
 *
 * A robot is located at the top-left corner of a m x n grid
 * (marked 'Start' in the diagram below).
 *
 * The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner of the grid
 * (marked 'Finish' in the diagram below).
 *
 * How many possible unique paths are there?
 *
 */
#include <vector>


// time complexity O(m*n)
// space complexity O(min(m, n))
int uniquePaths(int m, int n) {
  if (m > n) return uniquePaths(n, m);
  // assume n>= m
  std::vector<int> s0(m, 1);
  std::vector<int> s1(m, 1);
  for (int i=1; i<n; ++i) {
    for (int j=1; j<m; ++j) s1[j] = s0[j] + s1[j-1];
    s0 = s1;
  }

  return s1[m-1];
}

#endif //LEECODE_062_H
