//
// Created by jun on 10/19/17.
//

#ifndef LEECODE_034_H
#define LEECODE_034_H

#include <vector>
#include <algorithm>

/**
 * 34. Search for a Range
 *
 * Given an array of integers sorted in ascending order, find the
 * starting and ending position of a given target value.

 * Your algorithm's runtime complexity must be in the order of O(logN).

 * If the target is not found in the array, return [-1, -1].

 * For example,
 * Given [5, 7, 7, 8, 8, 10] and target value 8,
 * return [3, 4].
 */

std::vector<int> searchRange(std::vector<int>& nums, int target) {
  std::vector<int> ans {-1, -1};
  if (nums.empty()) return ans;

  int left =0;
  int right = nums.size();
  while (right - left > 0) {
    int mid = left + (right - left)/2;
    if (nums[mid] < target) {
      left = std::max(left+1, mid);
    } else {
      right = mid;
    }
  }
  if (left >= nums.size() || nums[left] != target) return ans;
  ans[0] = left;

  left = 0;
  right = nums.size();
  while (right - left > 0) {
    int mid = left + (right - left)/2;
    if (nums[mid] <= target) {
      left = std::max(left+1, mid);
    } else {
      right = mid;
    }
  }
  ans[1] = left - 1;

  return ans;
}


// Implementation using the standard library
std::vector<int> searchRangeSTL(std::vector<int>& nums, int target) {
  std::vector<int> ans {-1, -1};
  auto p0 = std::lower_bound(nums.begin(), nums.end(), target);
  auto p1 = std::upper_bound(nums.begin(), nums.end(), target);

  if (p0 == nums.end() || *p0 != target) return ans;

  ans[0] = std::distance(nums.begin(), p0);
  ans[1] = std::distance(nums.begin(), p1) - 1;

  return ans;
}

#endif //LEECODE_034_H
