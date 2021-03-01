//
// Created by jun on 11/4/17.
//

#ifndef LEECODE_018_H
#define LEECODE_018_H

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


/**
 * 18. 4Sum
 *
 * Given an array S of n integers, are there elements a, b, c, and d
 * in S such that a + b + c + d = target? Find all unique quadruplets
 * in the array which gives the sum of target.

 * Note: The solution set must not contain duplicate quadruplets.

 * For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

 * A solution set is:
 * [
 *  [-1,  0, 0, 1],
 *  [-2, -1, 1, 2],
 *  [-2,  0, 0, 2]
 * ]
 */

// time complexity O(N^2logN), space complexity O(N^2)
//std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
//  if (nums.size() < 4) return {};
//  using index_pair = std::pair<int, int>; // store the indices!
//
//  // sort the original array, O(NlogN)
//  std::sort(nums.begin(), nums.end());
//
//  // build the indices pair array, O(N^2logN)
//  std::vector<index_pair> indices;
//  for (int i=0; i<nums.size(); ++i) {
//    for (int j=i+1; j<nums.size(); ++j) {
//      indices.emplace_back(std::make_pair(i, j));
//    }
//  }
//  std::sort(indices.begin(), indices.end(), [&nums](index_pair a, index_pair b)
//  {
//    return (nums[a.first] + nums[a.second] < nums[b.first] + nums[b.second]);
//  });
//
//
//  std::set<std::vector<int>> ans_set;
//  // two pointer method time complexity O(N^2)
//  for (auto it1=indices.begin(), it2=indices.end() - 1; it1 < it2;) {
//    int x1 = nums[it1->first];
//    int x2 = nums[it1->second];
//    int x3 = nums[it2->first];
//    int x4 = nums[it2->second];
//
//    int sum = x1 + x2 + x3 + x4;
//    if (sum == target) {
//      if (x2 <= x3 && it1->second != it2->first)
//        ans_set.insert(std::vector<int>{x1, x2, x3, x4});
//      ++it1;
//    } else if (sum > target) {
//      --it2;
//    } else {
//      ++it1;
//    }
//  }
//
//  std::vector<std::vector<int>> ans(ans_set.begin(), ans_set.end());
//  return ans;
//}

// time complexity O(N^3)
// space complexity is the space required to store the answer
// if heap sort is used.
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
  if (nums.size() < 4) return {};
  using index_pair = std::pair<int, int>; // store the indices!

  // sort the original array, O(NlogN)
  std::sort(nums.begin(), nums.end());

  std::set<std::vector<int>> ans_set;

  for (int i=0; i<nums.size(); ++i) {
    for (int j=i+1; j<nums.size(); ++j) {
      // two-pointer method
      for (int k=j+1, l=nums.size()-1; k<l;) {
        int sum = nums[i] + nums[j] + nums[k] + nums[l];
        if (sum == target) {
          ans_set.emplace(std::initializer_list<int>{nums[i], nums[j], nums[k], nums[l]});
          if (nums[i] + nums[j] + 2*nums[k] >= target) break;  // skip redundant loops
          ++k;
          --l;
        } else {
          sum > target ? --l : ++k;
        }
      }
      if (nums[i] + 3*nums[j] >= target) break;  // skip redundant loops
    }
    if (4*nums[i] >= target) break;  // skip redundant loops
  }

  std::vector<std::vector<int>> ans(ans_set.begin(), ans_set.end());
  return ans;
}


#endif //LEECODE_018_H
