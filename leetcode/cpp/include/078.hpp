//
// Created by jun on 10/26/17.
//

#ifndef LEECODE_078_H
#define LEECODE_078_H

#include <vector>


/**
 * 78. Subsets
 *
 * Given a set of distinct integers, nums, return all possible subsets
 * (the power set).

 * Note: The solution set must not contain duplicate subsets.

 * For example,
 * If nums = [1,2,3], a solution is:

 * [
    [3],
    [1],
    [2],
    [1,2,3],
    [1,3],
    [2,3],
    [1,2],
    []
 * ]
 */

// time complexity O(2^N), because there are 2^N subsets in total
// the pop_back() operation will cost extra time
// space complexity O(2^N)
void subsets(const std::vector<int>& nums,
             std::vector<std::vector<int>>& ans,
             std::vector<int>& subset,
             int start) {
  if (subset.size() == nums.size()) return;

  for (int i = start; i < nums.size(); ++i) {
    subset.push_back(nums[i]);
    ans.push_back(subset);
    subsets(nums, ans, subset, i+1);
    subset.pop_back();
  }
}

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
  std::vector<std::vector<int>> ans;
  std::vector<int> subset;
  ans.push_back(subset);

  subsets(nums, ans, subset, 0);
  return ans;
}

// better solution than backtracking
// time complexity O(2^N), because there are 2^N subsets in total
// space complexity O(2^N)
std::vector<std::vector<int>> subsetsIterative(std::vector<int>& nums) {
  std::vector<std::vector<int>> ans(1, std::vector<int>());
  for (auto v : nums) {
    int m = ans.size();
    for (int i=0; i<m; ++i) {
      ans.push_back(ans[i]);
      ans.back().push_back(v);
    }
  }

  return ans;
}

#endif //LEECODE_078_H
