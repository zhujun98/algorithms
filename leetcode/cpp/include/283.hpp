//
// Created by jun on 12/21/17.
//

#ifndef LEECODE_283_H
#define LEECODE_283_H

#include <vector>

/**
 * 283. Move Zeroes
 *
 * Given an array nums, write a function to move all 0's to the end of
 * it while maintaining the relative order of the non-zero elements.

 * For example, given nums = [0, 1, 0, 3, 12], after calling your
 * function, nums should be [1, 3, 12, 0, 0].

 * Note:
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 *
 */
// time complexity O(N), space complexity O(1)
void moveZeroes(std::vector<int>& nums) {
  for (int i=0, j=0; i < nums.size(); ++i) {
    // if i == j, the swap costs nothing
    if (nums[i] != 0) std::swap(nums[i], nums[j++]);
  }
  return;
}

#endif //LEECODE_283_H
