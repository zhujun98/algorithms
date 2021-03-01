//
// Created by jun on 2/19/18.
//

#ifndef LEECODE_011_H
#define LEECODE_011_H

/**
 * 11. Container With Most Water
 *
 * Given n non-negative integers a1, a2, ..., an, where each represents
 * a point at coordinate (i, ai). n vertical lines are drawn such that
 * the two endpoints of line i is at (i, ai) and (i, 0). Find two lines,
 * which together with x-axis forms a container, such that the container
 * contains the most water.
 *
 * Note: You may not slant the container and n is at least 2.
 *
 */
#include <vector>


// time complexity O(N)
// space complexity O(1)
int maxArea(std::vector<int> height) {
  int max_area = 0;
  for (int i=0, j=height.size()-1; i<j;) {
    max_area = std::max(max_area, (j - i)*std::min(height[i], height[j]));
    if (height[i] > height[j]) --j;
    else ++i;
  }

  return max_area;
}

#endif //LEECODE_011_H
