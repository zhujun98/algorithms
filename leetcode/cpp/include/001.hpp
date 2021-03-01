//
// Created by jun on 10/23/17.
//

#ifndef LEECODE_001_H
#define LEECODE_001_H

/**
 * 1. Two Sum
 *
 * Given an array of integers, return indices of the two numbers such
 * that they add up to a specific target.

 * You may assume that each input would have exactly one solution, and
 * you may not use the same element twice.

 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,

 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 */
#include <vector>
#include <unordered_map>


// time complexity O(N)
// space complexity O(N)
std::vector<int> twoSum2Passes(std::vector<int> nums, int target) {
  std::unordered_map<int, int> hash;
  for (int i=0; i<nums.size(); ++i) hash[nums[i]] = i;

  for (int i=0; i<nums.size(); ++i) {
    auto search = hash.find(target - nums[i]);
    if (search != hash.end() && search->second != i)
      return std::vector<int>{i, search->second};
  }
}

// This better implementation has the same time and space complexity.
// But it only goes throught the hash table once.
std::vector<int> twoSum(std::vector<int> nums, int target) {
  std::unordered_map<int, int> hash;
  for (int i=0; i<nums.size(); ++i) {
    auto search = hash.find(target - nums[i]);
    if (search != hash.end()) return std::vector<int>{i, search->second};
    hash[nums[i]] = i;
  }
}

#endif //LEECODE_001_H
