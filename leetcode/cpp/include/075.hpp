//
// Created by jun on 10/25/17.
//

#ifndef LEECODE_075_H
#define LEECODE_075_H

#include <vector>


/**
 * 75. Sort Colors
 *
 * Given an array with n objects colored red, white or blue, sort them
 * so that objects of the same color are adjacent, with the colors in
 * the order red, white and blue.

 * Here, we will use the integers 0, 1, and 2 to represent the color
 * red, white, and blue respectively.
 */

// Time complexity O(N), space complexity O(1)
// Note:: using count sort can also achieve O(N) time complexity, but
//        it requires traversing the array twice.
void sortColors(std::vector<int>& nums) {
  int left = 0;
  int right = nums.size() - 1;
  int mid = 0;
  while (mid <= right) {
    switch (nums[mid]) {
      case 0:
        std::swap(nums[left++], nums[mid++]);
        break;
      case 1:
        ++mid;
        break;
      case 2:
        std::swap(nums[mid], nums[right--]);
        break;
    }
  }
}

#endif //LEECODE_075_H
