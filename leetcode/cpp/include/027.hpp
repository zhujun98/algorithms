//
// Created by jun on 12/21/17.
//

#ifndef LEECODE_027_H
#define LEECODE_027_H

#include <vector>

/**
 * 27. Remove Element
 *
 * Given an array and a value, remove all instances of that value
 * in-place and return the new length.

 * Do not allocate extra space for another array, you must do this by
 * modifying the input array in-place with O(1) extra memory.

 * The order of elements can be changed. It doesn't matter what you
 * leave beyond the new length.

 * Example:

 * Given nums = [3,2,2,3], val = 3,

 * Your function should return length = 2, with the first two elements
 * of nums being 2.
 */
// the vector is passed by value for the convenience of test

// Time complexity O(N) solution that does not maintain all the
// elements in the array.
int removeElement(std::vector<int> nums, int val) {
  int end = 0;
  for (int i=0; i < nums.size(); ++i) {
    if (nums[i] != val) nums[end++] = nums[i];
  }
  return end;
}

// Time complexity O(N) solution that maintains all the
// elements in the array.
int removeElement1(std::vector<int> nums, int val) {
  int end = nums.size() - 1;
  int i = 0;
  while (i <= end) {
    if (nums[end] == val) --end;
    else if (nums[i] == val) {
      std::swap(nums[i], nums[end]);
    } else ++i;
  }
  return end+1;
}



#endif //LEECODE_027_H
