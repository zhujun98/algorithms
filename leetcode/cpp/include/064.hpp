//
// Created by jun on 10/19/17.
//

#ifndef LEECODE_064_H
#define LEECODE_064_H

#include <iostream>
#include <vector>


/**
 * 64. Minimum Path Sum
 *
 * Given a m x n grid filled with non-negative numbers, find a path
 * from top left to bottom right which minimizes the sum of all
 * numbers along its path.

 * Note: You can only move either down or right at any point in time.

 * Example 1:
 *
 * [[1,3,1],
 * [1,5,1],
 * [4,2,1]]
 *
 * Given the above grid map, return 7. Because the path 1→3→1→1→1
 * minimizes the sum.
 */

// Note: the constraint that only moving down and right are allowed
//       greatly simplify the problem
int minPathSum(std::vector<std::vector<int>>& grid) {
  int m = grid.size();
  int n = grid[0].size();

  for (int i=0; i< m; ++i) {
    for (int j=0; j < n; ++j) {
      if (i==0 && j!=0) {
        grid[i][j] += grid[i][j-1];
      } else if (i!=0 && j==0) {
        grid[i][j] += grid[i-1][j];
      } else if (i!=0 && j!=0) {
        grid[i][j] += std::min(grid[i][j-1], grid[i-1][j]);
      }
    }
  }

  return grid[m-1][n-1];
}

#endif //LEECODE_064_H
