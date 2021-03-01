//
// Created by jun on 10/15/17.
//

#ifndef LEECODE_039_H
#define LEECODE_039_H

#include <vector>
#include <algorithm>


/**
 * 39. Combination Sum
 *
 * Given a set of candidate positive integer numbers (C) (without
 * duplicates) and a target number (T), find all unique combinations
 * in C where the candidate numbers sums to T.

 * The same repeated number may be chosen from C unlimited number of times.
 * For example, given candidate set [2, 3, 6, 7] and target 7,
 * A solution set is:
 * [
 *  [7],
 *  [2, 2, 3]
 * ]
 */

using solution_set = std::vector<std::vector<int>>;
using solution = std::vector<int>;

void findNumbers(const std::vector<int>& x, size_t start, int sum, solution_set& slt_set, solution& slt) {
  if (sum == 0) {
    slt_set.push_back(slt);
    return;
  }

  for (size_t i=start; i < x.size(); ++i) {
    if (x[i] > sum) return;
    slt.push_back(x[i]);
    // try fill more of the ith element
    findNumbers(x, i, sum - x[i], slt_set, slt);
    // remove x[i] from slt, backtracking
    slt.pop_back();
  }
}

std::vector<std::vector<int>>
combinationSum(std::vector<int>& candidates, int target) {
  std::sort(candidates.begin(), candidates.end());
  // candidates.erase(std::unique(candidates.begin(), candidates.end()),
  //                  candidates.end());

  solution slt;
  solution_set slt_set;

  findNumbers(candidates, 0, target, slt_set, slt);

  return slt_set;
}

#endif //LEECODE_039_H
