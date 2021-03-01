//
// Created by jun on 10/14/17.
//

#ifndef LEECODE_200_H
#define LEECODE_200_H

#include <iostream>
#include <vector>

/**
 * 200. Number of Islands
 *
 * Given a 2d grid map of '1's (land) and '0's (water), count the
 * number of islands. An island is surrounded by water and is formed
 * by connecting adjacent lands horizontally or vertically. You may
 * assume all four edges of the grid are all surrounded by water.

 * Example 1:

 * 11110
 * 11010
 * 11000
 * 00000
 * Answer: 1

 * Example 2:

 * 11000
 * 11000
 * 00100
 * 00011
 * Answer: 3

 */

// time complexity O(MN), space complexity O(MN)
inline void dfsMap(std::vector<std::vector<bool>>& visited,
            const std::vector<std::vector<char>>& grid, int i, int j) {
  if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size()) return;
  if (!visited[i][j] && grid[i][j] == '1') {
    visited[i][j] = true;
    dfsMap(visited, grid, i-1, j);
    dfsMap(visited, grid, i+1, j);
    dfsMap(visited, grid, i, j-1);
    dfsMap(visited, grid, i, j+1);
  }
}

inline int numIslands(std::vector<std::vector<char>>& grid) {
  if (grid.empty()) return 0;

  size_t w = grid.size();
  size_t h = grid[0].size();

  int count = 0;
  std::vector<std::vector<bool>> visited(w, std::vector<bool>(h, false));
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (grid[i][j] == '1' && !visited[i][j]) {
        ++count;
        dfsMap(visited, grid, i, j);
      }
    }
  }

  return count;
}

#endif //LEECODE_200_H
