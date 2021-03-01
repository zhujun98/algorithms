//
// Created by jun on 10/25/17.
//

#ifndef LEECODE_189_H
#define LEECODE_189_H

#include <vector>


/**
 * 189. Rotate Array
 *
 * Rotate an array of n elements to the right by k steps.

 * For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7]
 * is rotated to [5,6,7,1,2,3,4].
 */

// solution 1
// time complexity O(N), space complexity O(1)
void rotateArray1(std::vector<int>& nums, int k) {
  // move the element by k steps one by one
  for(int count=0, start=0; count<nums.size(); ++start) {
    int i = start;
    int prev = nums[i];
    do {
      i = (i+k)%nums.size();
      auto tmp = nums[i];
      nums[i] = prev;
      prev = tmp;
      ++count;
    }
    while (i != start);
  }
}

// solution 2
// time complexity O(N), space complexity O(1)
void reverseArray189(std::vector<int>& nums, int start, int end) {
  for (;start < end; ++start, --end) {
    std::swap(nums[start], nums[end]);
  }
}

void rotateArray2(std::vector<int>& nums, int k) {
  k %= nums.size(); // important!
  reverseArray189(nums, 0, nums.size()-1);
  reverseArray189(nums, 0, k-1);
  reverseArray189(nums, k, nums.size()-1);
}

#endif //LEECODE_189_H
