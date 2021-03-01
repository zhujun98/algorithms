//
// Created by jun on 10/15/17.
//

#ifndef LEECODE_198_H
#define LEECODE_198_H

#include <iostream>
#include <vector>

/**
 * 198. House Robber
 *
 * You are a professional robber planning to rob houses along a street.
 * Each house has a certain amount of money stashed, the only
 * constraint stopping you from robbing each of them is that adjacent
 * houses have security system connected and it will automatically
 * contact the police if two adjacent houses were broken into on the
 * same night.

 * Given a list of non-negative integers representing the amount of money
 * of each house, determine the maximum amount of money you can rob
 * tonight without alerting the police.
 *
 */

// simple DP problem, time complexity O(N), space complexity O(1)
int rob(std::vector<int>& nums) {
  int s0 = 0;
  if (nums.empty()) return 0;
  int s1 = nums[0];
  if (nums.size() == 1) return s1;
  for (size_t i = 1; i < nums.size(); ++i) {
    int tmp = s1;
    s1 = std::max(s0 + nums[i], s1);
    s0 = tmp;
  }

  return s1;
}

#endif //LEECODE_198_H
