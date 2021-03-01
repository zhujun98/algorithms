//
// Created by jun on 10/22/17.
//

#ifndef LEECODE_015_H
#define LEECODE_015_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>


/**
 * 15. 3Sum
 *
 * Given an array S of n integers, are there elements a, b, c in S
 * such that a + b + c = 0? Find all unique triplets in the array
 * which gives the sum of zero.
 *
 * Note: The solution set must not contain duplicate triplets.
 *
 * For example, given array S = [-1, 0, 1, 2, -1, -4],

 * A solution set is:
 * [
 *     [-1, 0, 1],
 *     [-1, -1, 2]
 * ]
 */

// time complexity O(N^2)
// space complexity is the space required to store the answer
// if heap sort is used.
std::vector<std::vector<int>> threeSum(std::vector<int>& nums, int sum=0){
  if (nums.size() < 3) return {};

  std::sort(nums.begin(), nums.end());

  std::set<std::vector<int>> ans_set;

  for (int i=0; i<nums.size(); ++i) {
    for (int j=i+1, k=nums.size()-1; j < k;) {
      int sum_now = nums[i] + nums[j] + nums[k];
      if (sum_now == sum) {
        ans_set.emplace(std::initializer_list<int>{nums[i], nums[j], nums[k]});
        if (nums[i] + 2*nums[j] >= sum) break;  // skip redundant loops
        --k;
        ++j;
      } else {
        sum_now > sum ? --k : ++j;
      }
    }
    if (3*nums[i] >= sum) break; // skip redundant loops
  }

  std::vector<std::vector<int>> ans(ans_set.begin(), ans_set.end());
  return ans;
}

#endif //LEECODE_015_H
