#ifndef LEECODE_026_H
#define LEECODE_026_H

#include <vector>

/**
 * 26. Remove Duplicates from Sorted Array
 *
 * Given a sorted array, remove the duplicates in place such that each
 * element appear only once and return the new length.
 *
 * Requirement: Do not allocate extra space for another array, you must
 * do this in place with constant memory.
 */

// This is in fact a two-pointer algorithm.
// time complexity O(N), space complexity O(1)
int removeDuplicates(std::vector<int>& nums) {
  if (nums.empty()) { return 0; }

  int count = 1;
  for (auto v : nums) {
    if ( v != nums[count-1] ) {
      nums[count] = v;
      ++count;
    }
  }

  return count;
}

#endif //LEECODE_026_H
