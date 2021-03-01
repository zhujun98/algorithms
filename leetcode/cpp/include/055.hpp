//
// Created by jun on 10/17/17.
//

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

// This is similar to two pointers: keep tracking the current index and
// the max index that can reach
// Time complexity O(N), space complexity O(1)
bool canJump(std::vector<int>& nums) {
  int max_reach = 0;

  for (int i=0; i<nums.size() && i <= max_reach; ++i) {
    max_reach = std::max(max_reach , i + nums[i]);
  }
  return (max_reach >= nums.size() - 1);
}

#endif //LEECODE_055_H
