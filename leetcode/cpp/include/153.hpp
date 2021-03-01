//
// Created by jun on 10/29/17.
//

#ifndef LEECODE_153_H
#define LEECODE_153_H

#include <vector>

/**
 * 153. Find Minimum in Rotated Sorted Array
 *
 * Suppose an array sorted in ascending order is rotated at some pivot
 * unknown to you beforehand.

 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

 * Find the minimum element.

 * You may assume no duplicate exists in the array.
 */

int findMin(std::vector<int>& nums) {
  int left = 0;
  int right = nums.size() - 1;

  while (left < right) {
    if (nums[left] < nums[right]) return nums[left];

    int mid = (left + right)/2;

    if (nums[mid] <= nums[right])
      right = mid;
    else
      left = mid + 1;
  }

  return nums[right];
}

#endif //LEECODE_153_H
