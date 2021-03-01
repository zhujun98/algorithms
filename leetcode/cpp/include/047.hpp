//
// Created by jun on 10/23/17.
//

#ifndef LEECODE_047_H
#define LEECODE_047_H

#include <vector>
#include <set>

/**
 * 47. Permutations II
 *
 * Given a collection of numbers that might contain duplicates, return
 * all possible unique permutations.

 * For example,
 * [1,1,2] have the following unique permutations:
 * [
 *  [1,1,2],
 *  [1,2,1],
 *  [2,1,1]
 * ]
 */

// Naive implementation on the basis of 047. Here a `set` container is
// used to remove duplicates. the time complexity of insertion is log(N)
//
// space complexity of using set can be neglected by using
// std::make_move_iterator to move data from std::set to std::vector
void permuteUniqueSet(std::vector<int>& nums,
                      int start,
                      std::set<std::vector<int>>& ans_set) {
  if (start == nums.size() - 1) {
    ans_set.insert(nums);
    return;
  }

  for (int i = start; i < nums.size(); ++i) {
    std::swap(nums[start], nums[i]);
    permuteUniqueSet(nums, start+1, ans_set);
    std::swap(nums[start], nums[i]);
  }
}

std::vector<std::vector<int>> permuteUniqueSet(std::vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  std::set<std::vector<int>> ans_set;
  permuteUniqueSet(nums, 0, ans_set);

  std::vector<std::vector<int>> ans(std::make_move_iterator(ans_set.begin()),
                                    std::make_move_iterator(ans_set.end()));

  return ans;
}

#endif //LEECODE_047_H
