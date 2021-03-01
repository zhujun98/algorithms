//
// Created by jun on 2/20/18.
//

#ifndef LEECODE_063_H
#define LEECODE_063_H

/**
 * 63. Unique Paths II
 *
 * Follow up for "Unique Paths":
 *
 * Now consider if some obstacles are added to the grids. How many
 * unique paths would there be? An obstacle and empty space is marked
 * as 1 and 0 respectively in the grid.
 */
#include <vector>


// time complexity O(mn)
// space complexity O(m)
int uniquePathsWithObstacles(const std::vector<std::vector<int>>& obstacleGrid) {
  int m = obstacleGrid.size();
  int n = obstacleGrid[0].size();

  // initialize a two-column vector to store history
  std::vector<std::vector<int>> s (m, std::vector<int>(2, 0));

  // initialize the first column
  s[0][0] = !obstacleGrid[0][0];
  for (int j=1; j<m; ++j) s[j][0] = obstacleGrid[j][0] ? 0 : s[j-1][0];

  // if the obstacleGrid only has one column
  if (n == 1) return s[m-1][0];

  for (int i=1; i<n; ++i) {
    s[0][1] = obstacleGrid[0][i] ? 0 : s[0][0];
    for (int j=1; j<m; ++j) {
      s[j][1] = obstacleGrid[j][i] ? 0 : (s[j][0] + s[j-1][1]);
      s[j][0] = s[j][1];  // follow-up updating of the first column
    }
    s[0][0] = s[0][1];  // first element of the first column
  }

  return s[m-1][1];

}

#endif //LEECODE_063_H
