#ifndef LEECODE_055_H
#define LEECODE_055_H

#include <vector>


/**
 * 55. Jump Game
 *
 * Given an array of non-negative integers, you are initially positioned
 * at the first index of the array. Each element in the array represents
 * your maximum jump length at that position. Determine if you are able
 * to reach the last index.

 * For example:
 * A = [2,3,1,1,4], return true.

 * A = [3,2,1,0,4], return false.
 */

// dynamic programming
// Time complexity O(N^2), space complexity O(N)
bool canJumpDP(std::vector<int>& nums) {
  int l = nums.size();
  std::vector<bool> memo(l, false);
  memo[l-1] = true;

  for (int i = l - 2; i >= 0; --i) {
    // We search within the reach of location i, whether there is a point
    // marked true. If yes, it means that from location i we can also reach
    // the destination.
    int step_size = std::min(l - i - 1, nums[i]);
    for (int j = 1; j <= step_size; ++j) {
      if (memo[i+j]) {
        memo[i] = true;
        break;
      }
    }
  }
  return memo[0];
}

// Greedy solution
// Time complexity O(N), space complexity O(1)
bool canJump(std::vector<int>& nums) {
  int nearest_good_pos = nums.size() - 1;
  for (int i = nums.size() - 1; i >= 0; --i) {
    if (i + nums[i] >= nearest_good_pos) nearest_good_pos = i;
  }
  return nearest_good_pos == 0;
}

#endif //LEECODE_055_H
