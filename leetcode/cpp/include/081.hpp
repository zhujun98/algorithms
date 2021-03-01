//
// Created by jun on 10/26/17.
//

#ifndef LEECODE_081_H
#define LEECODE_081_H

#include <vector>


/**
 * 81. Search in Rotated Sorted Array II
 *
 * Suppose an array sorted in ascending order is rotated at some pivot
 * unknown to you beforehand.

 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

 * Write a function to determine if a given target is in the array.

 * The array may contain duplicates.
 */

// standard binary search
// time complexity O(logN) / worse case O(N), space complexity O(1)
bool searchInRotatedSortedArrayII(std::vector<int>& nums, int target) {
  if (nums.empty()) return false;
  int left = 0;
  int right = nums.size() - 1;

  while (left < right) {
    int mid = (left + right) / 2;

    // On the basis of the non-duplicate case, the key step to deal with
    // duplicates, e.g. [1, 1, 3, 1, 1, 1] is to shift the left boundary
    // until left != right. Otherwise you have no ideal how to update the
    // boundary.
    if (nums[left] == nums[right]) {
      ++left;
      continue;
    }

    // the key step is to identify the three case in which the left
    // boundary should be updated by `mid + 1`
    if ((nums[mid] < target && (target <= nums[right] || nums[mid] >= nums[left])) ||
        (nums[right] >= target && nums[mid] > nums[right])) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return (nums[right] == target);
}

// A variation of binary search
// time complexity O(logN) / worst case O(N), space complexity O(1)
bool searchInRotatedSortedArrayII1(std::vector<int>& nums, int target) {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {

    int mid = (left + right) / 2;

    if (nums[mid] == target) return true;

    // On the basis of the non-duplicate case, the key step to deal with
    // duplicates, e.g. [1, 1, 3, 1, 1, 1] is to shift the left boundary
    // until left != right. Otherwise you have no ideal how to update the
    // boundary.
    if (nums[left] == nums[right]) {
      ++left;
      continue;
    }

    if ((nums[mid] < target && (target <= nums[right] || nums[mid] >= nums[left])) ||
        (nums[right] >= target && nums[mid] > nums[right])) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return false;
}

#endif //LEECODE_081_H
