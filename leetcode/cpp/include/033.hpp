//
// Created by jun on 10/25/17.
//

#ifndef LEECODE_033_H
#define LEECODE_033_H

#include <vector>

/**
 * 33. Search in Rotated Sorted Array
 *
 * Suppose an array sorted in ascending order is rotated at some
 * pivot unknown to you beforehand.
 *
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 *
 * You are given a target value to search. If found in the array
 * return its index, otherwise return -1.
 *
 * You may assume no duplicate exists in the array.
 */

// standard binary search
// time complexity O(logN), space complexity O(1)
int searchInRotatedSortedArray(std::vector<int>& nums, int target) {
  if (nums.empty()) return -1;
  int left = 0;
  int right = nums.size() - 1;

  while (left < right) {
    int mid = (left + right) / 2;

    // the key step is to identify the three case in which the left
    // boundary should be updated by `mid + 1`
    if ((nums[mid] < target && (target <= nums[right] || nums[mid] >= nums[left])) ||
        (nums[right] >= target && nums[mid] > nums[right])) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return (nums[right] == target ? right : -1);
}

// A variation of binary search
// time complexity O(logN), space complexity O(1)
int searchInRotatedSortedArray1(std::vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = (left + right) / 2;

    if (nums[mid] == target) return mid;

    if ((nums[mid] < target && (target <= nums[right] || nums[mid] >= nums[left])) ||
        (nums[right] >= target && nums[mid] > nums[right])) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}


#endif //LEECODE_033_H
