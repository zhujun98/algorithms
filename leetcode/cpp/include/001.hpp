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

  std::vector<int> ret;
  for (int i=0; i<nums.size(); ++i) {
    auto search = hash.find(target - nums[i]);
    if (search != hash.end() && search->second != i) {
      // If the answer is a pair of equal numbers, it will be found when the loop
      // is at the second number.
      ret.push_back(search->second);
      ret.push_back(i);
      break;
    }
  }
  return ret;
}

// This better implementation has the same time and space complexity.
// But it only goes through the hash table once.
std::vector<int> twoSum(std::vector<int> nums, int target) {
  std::unordered_map<int, int> hash;
  std::vector<int> ret;
  for (int i=0; i<nums.size(); ++i) {
    auto search = hash.find(target - nums[i]);
    if (search != hash.end()) {
      ret.push_back(search->second);
      ret.push_back(i);
      break;
    }
    hash[nums[i]] = i;
  }
  return ret;
}

#endif //LEECODE_001_H
