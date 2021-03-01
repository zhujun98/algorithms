//
// Created by jun on 2/19/18.
//

#ifndef LEECODE_031_H
#define LEECODE_031_H


/**
 * 31. Next Permutation
 *
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 *
 * If such arrangement is not possible, it must rearrange it as the
 * lowest possible order (ie, sorted in ascending order).
 *
 * The replacement must be in-place, do not allocate extra memory.
 *
 * Here are some examples. Inputs are in the left-hand column and its
 * corresponding outputs are in the right-hand column.
 *  1,2,3 → 1,3,2
 *  3,2,1 → 1,2,3
 *  1, 5, 8, 4, 7, 6, 5, 3, 1 → 1, 5, 8, 5, 1, 3, 4, 6, 7
 *
 */
#include <vector>


// time complexity O(N)
// space complexity O(1)
std::vector<int> nextPermutation(std::vector<int> nums) {
  if (nums.empty()) return {};

  int i = nums.size() - 1;
  while (i > 0 && nums[i] <= nums[i-1]) --i;

  if (i > 0) {
    int j = i;
    while (j < nums.size() && nums[i-1] < nums[j]) ++j;
    std::swap(nums[i-1], nums[j-1]);
  }
  std::reverse(nums.begin() + i, nums.end());

  return nums;
}

#endif //LEECODE_031_H
