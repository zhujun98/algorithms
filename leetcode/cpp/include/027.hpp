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

// time complexity O(N), space complexity O(1).
int removeElement(std::vector<int> nums, int val) {
  int n = 0;
  for (int i=0; i < nums.size(); ++i) {
    if (nums[i] != val) {
      nums[n++] = nums[i];
    }
  }
  return n;
}

// time complexity O(N), space complexity O(1)
// A faster solution if the elements to be removed are only a few.
int removeElement2(std::vector<int>& nums, int val) {
  int i = 0;
  int n = nums.size();
  while (i < n) {
    if (nums[i] == val) {
      // move the to-be-removed element to the end
      // Note: one can use std::swap(nums[i], nums[n-1]) to maintain all the elements.
      nums[i] = nums[n-1];
      // shrink the array
      --n;
    } else {
      ++i;
    }
  }

  return n;
}

#endif //LEECODE_027_H
