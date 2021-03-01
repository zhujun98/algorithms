//
// Created by jun on 10/23/17.
//

#ifndef LEECODE_016_H
#define LEECODE_016_H

#include <vector>
#include <algorithm>

/**
 * 16. 3Sum Closest
 *
 * Given an array S of n integers, find three integers in S such that
 * the sum is closest to a given number, target. Return the sum of the
 * three integers. You may assume that each input would have exactly
 * one solution.

 * For example, given array S = {-1 2 1 -4}, and target = 1.

 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

// time complexity O(N^2), space complexity O(1)
int threeSumClosest(std::vector<int>& nums, int target) {
  std::sort(nums.begin(), nums.end());

  // use std::numeric_limit<int>::max() here could result in overflow
  int ans = nums[0] + nums[1] + nums[2];
  for (int i=0; i<nums.size(); ++i) {
    int j = i + 1;
    int k = nums.size() - 1;
    while (j < k) {
      int sum = nums[i] + nums[j] + nums[k];
      if (sum == target) return sum;
      if (sum > target) {
        --k;
      } else {
        ++j;
      }
      // update closest sum
      if (std::abs(sum - target) < std::abs(ans - target)) ans = sum;
    }
  }

  return ans;
}

#endif //LEECODE_016_H
