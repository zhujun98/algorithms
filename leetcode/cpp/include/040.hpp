//
// Created by jun on 10/15/17.
//

#ifndef LEECODE_040_H
#define LEECODE_040_H

#include <vector>
#include <iostream>
#include <algorithm>

/**
 * 40. Combination Sum II
 *
 * Given a collection of candidate numbers (C) and a target number (T),
 * find all unique combinations in C where the candidate numbers sums
 * to T.

 * Each number in C may only be used once in the combination.

 * Note:
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.

 * For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8,
 * A solution set is:
 * [
 *  [1, 7],
 *  [1, 2, 5],
 *  [2, 6],
 *  [1, 1, 6]
 * ]
 */

using solution_set = std::vector<std::vector<int>>;
using solution = std::vector<int>;

void findNumbers2(const std::vector<int>& x, size_t start, int sum, solution_set& slt_set, solution& slt) {

  if (sum == 0) {
    slt_set.push_back(slt);
    return;
  }

  for (size_t i=start; i < x.size(); ++i) {
    if (x[i] > sum) return;
    if (i > start && x[i] == x[i-1]) continue;
    slt.push_back(x[i]);
    findNumbers(x, i+1, sum - x[i], slt_set, slt);
    slt.pop_back();
  }
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
  std::sort(candidates.begin(), candidates.end());

  solution slt;
  solution_set slt_set;

  findNumbers2(candidates, 0, target, slt_set, slt);

  return slt_set;
}

#endif //LEECODE_040_H
