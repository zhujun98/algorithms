//
// Created by jun on 10/18/17.
//

#ifndef LEECODE_046_H
#define LEECODE_046_H

#include <vector>
#include <algorithm>

/**
 * 46. Permutations
 *
 * Given a collection of distinct numbers, return all possible permutations.

 * For example,
 * [1,2,3] have the following permutations:
 * [
 *   [1,2,3],
 *   [1,3,2],
 *   [2,1,3],
 *   [2,3,1],
 *   [3,1,2],
 *   [3,2,1]
 * ]
 */

void permute(std::vector<int>& nums, int start, std::vector<std::vector<int>>& ans) {
  if (start == nums.size()) {
    ans.push_back(nums);
    return;
  }

  for (int i = start; i < nums.size(); ++i) {
    // swap nums[start] with the rest elements one by one and recursively
    std::swap(nums[start], nums[i]);
    permute(nums, start+1, ans);
    // backtracking
    std::swap(nums[start], nums[i]);
  }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
  std::vector<std::vector<int>> ans;

  permute(nums, 0, ans);

  return ans;
}

#endif //LEECODE_046_H
