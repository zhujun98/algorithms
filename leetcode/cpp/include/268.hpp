//
// Created by jun on 12/21/17.
//

#ifndef LEECODE_268_H
#define LEECODE_268_H

#include <vector>

/**
 * 268. Missing Number
 *
 * Given an array containing n distinct numbers taken from 0, 1, 2, ...
 * , n, find the one that is missing from the array.

 * The input array is not sorted. Pay attention to corner cases, e.g. 0
 * is missing or nothing is missing.

 * For example,
 * Given nums = [0, 1, 3] return 2.
 */

// time complexity O(N), space complexity O(1)
int missingNumber(std::vector<int> nums) {
  int sum = 0;
  for (int i=0; i<nums.size(); ++i) sum += i + 1 - nums[i];
  return sum;
}

#endif //LEECODE_268_H
