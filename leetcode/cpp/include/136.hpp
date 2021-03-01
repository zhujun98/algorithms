//
// Created by jun on 11/2/17.
//

#ifndef LEECODE_136_H
#define LEECODE_136_H

#include <vector>
#include <unordered_map>

/**
 * 136. Single Number
 *
 * Given an array of integers, every element appears twice except for
 * one. Find that single one.
 */

// time complexity O(N), space complexity O(N)
int singleNumber(std::vector<int> nums) {
  std::unordered_map<int, int> hash;
  for (auto v : nums) hash[v]++;
  for (auto &v : hash) {
    if (v.second == 1) { return v.first; }
  }
}

// Bit trick: a XOR 0 = a, a XOR a = 0
// Moreover, XOR is commutative and associative
//
// time complexity O(N), space complexity O(1)
int singleNumberBit(std::vector<int> nums) {
  int x = 0;
  for (auto v : nums) x ^= v;

  return x;
}

#endif //LEECODE_136_H
