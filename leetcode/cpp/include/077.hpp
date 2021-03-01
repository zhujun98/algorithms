//
// Created by jun on 10/26/17.
//

#ifndef LEECODE_077_H
#define LEECODE_077_H

#include <vector>

/**
 * 77. Combinations
 *
 * Given two integers n and k, return all possible combinations of k
 * numbers out of 1 ... n.

 * For example,
 * If n = 4 and k = 2, a solution is:

 * [
    [2,4],
    [3,4],
    [2,3],
    [1,2],
    [1,3],
    [1,4],
 * ]
 */

void combine(std::vector<std::vector<int>>& ans,
             std::vector<int>& comb,
             int n, int k, int start) {
  if (comb.size() == k) {
    ans.push_back(comb);
    return;
  }

  while (++start <= n) {
    comb.push_back(start);
    combine(ans, comb, n, k, start);
    comb.pop_back();
  }
}

std::vector<std::vector<int>> combine(int n, int k) {
  std::vector<std::vector<int>> ans;
  std::vector<int> comb;

  combine(ans, comb, n, k, 0);

  return ans;
}

#endif //LEECODE_077_H
