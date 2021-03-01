//
// Created by jun on 10/26/17.
//

#ifndef LEECODE_080_H
#define LEECODE_080_H

#include <vector>

/**
 * 80. Remove Duplicates from Sorted Array II
 *
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?

 * For example,
 * Given sorted array nums = [1,1,1,2,2,3],

 * Your function should return length = 5, with the first five elements
 * of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave
 * beyond the new length.
 */

// two pointer algorithm
// time complexity O(N), space complexity O(1)
int removeDuplicatesII(std::vector<int>& nums) {
  if (nums.size() <= 2) return nums.size();

  int count = 2;
  for (int runner=2; runner<nums.size(); ++runner) {
    // key point, compare `runner` and `count - 2`
    if (nums[runner] > nums[count-2]) nums[count++] = nums[runner];
  }

  return count;
}

#endif //LEECODE_080_H
