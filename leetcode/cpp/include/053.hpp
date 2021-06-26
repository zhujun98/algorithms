#ifndef LEECODE_053_H
#define LEECODE_053_H

#include <vector>
#include <algorithm>

/**
 * 53. Maximum Subarray
 *
 * Find the contiguous subarray within an array (containing at least *
 * one number) which has the largest sum.

 * For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 * the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 */

// DP solution, track two quantities
// time complexity O(N), space complexity O(1)
int maxSubArray(std::vector<int>& nums) {
  int max_sum = nums[0]; // maximum sum so far
  int max_ending_last = nums[0]; // maximum sum ending at the last

  for (int i=1; i<nums.size(); ++i) {
    max_ending_last = std::max(max_ending_last + nums[i], nums[i]);
    max_sum = std::max(max_sum, max_ending_last);
  }

  return max_sum;
}

#endif //LEECODE_053_H
