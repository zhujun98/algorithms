//
// Created by jun on 11/1/17.
//

#ifndef LEECODE_090_H
#define LEECODE_090_H

#include <vector>
#include <set>
#include <algorithm>

/**
 * 90. Subsets II
 *
 * Given a collection of integers that might contain duplicates, nums,
 * return all possible subsets (the power set).

 * Note: The solution set must not contain duplicate subsets.

 * For example,
 * If nums = [1,2,2], a solution is:

 * [
 *  [2],
 *  [1],
 *  [1,2,2],
 *  [2,2],
 *  [1,2],
 *  []
 * ]
 *
 */

// slow implementation using std::set container, the time complexity
// of insertion is log(N)
//
// space complexity of using set can be neglected by using
// std::make_move_iterator to move data from std::set to std::vector
void subsetsWithDupSet(std::vector<int>& nums,
                    std::set<std::vector<int>>& ans,
                    std::vector<int>& comb,
                    int start) {
  for (int i=start; i<nums.size(); ++i) {
    comb.push_back(nums[i]);
    ans.insert(comb);
    subsetsWithDupSet(nums, ans, comb, i+1);
    comb.pop_back();
  }
}

std::vector<std::vector<int>> subsetsWithDupSet(std::vector<int>& nums) {
  std::sort(nums.begin(), nums.end());

  std::set<std::vector<int>> ans_set;
  ans_set.insert(std::vector<int>());
  std::vector<int> comb;

  subsetsWithDupSet(nums, ans_set, comb, 0);

  // use std::make_move_iterator to reduce space complexity
  std::vector<std::vector<int>> ans(std::make_move_iterator(ans_set.begin()),
                                    std::make_move_iterator(ans_set.end()));;
  return ans;
}

#endif //LEECODE_090_H
