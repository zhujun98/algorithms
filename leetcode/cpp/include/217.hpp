//
// Created by jun on 10/15/17.
//

#ifndef LEECODE_217_H
#define LEECODE_217_H

#include <algorithm>
#include <vector>
#include <unordered_map>


/**
 * 217. Contains Duplicate
 *
 * Given an array of integers, find if the array contains any
 * duplicates. Your function should return true if any value appears
 * at least twice in the array, and it should return false if every
 * element is distinct.
 */

// use heap sort
// time complexity O(NlogN), space complexity O(1)
bool containsDuplicate(std::vector<int>& nums) {
  if (nums.size() < 2) return false;

  std::make_heap(nums.begin(), nums.end());
  std::sort_heap(nums.begin(), nums.end());
  for (auto it=nums.begin()+1; it != nums.end(); ++it) {
    if (*it == *(it-1)) return true;
  }
  return false;
}

// use hash table
// time complexity O(N), space complexity O(N)
bool containsDuplicate1(std::vector<int>& nums) {
  std::unordered_map<int, int> hash;
  for (size_t i=0; i<nums.size(); ++i) {
    hash[nums[i]]++;
    if (hash[nums[i]] > 1) return true;
  }
  return false;
}

#endif //LEECODE_217_H
