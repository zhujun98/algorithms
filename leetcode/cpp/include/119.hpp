//
// Created by jun on 10/27/17.
//

#ifndef LEECODE_109_H
#define LEECODE_109_H

#include <vector>

/**
 * 119. Pascal's Triangle II
 *
 * Given an index k, return the kth row of the Pascal's triangle.

 * For example, given k = 3,
 * Return [1,3,3,1].
 */

// time complexity O(k), space complexity O(1) + space to store answer O(k)
std::vector<int> getRow(int rowIndex) {
  std::vector<int> ans(rowIndex+1, 1);
  for (int i=1; i<=rowIndex; ++i) {
    ans[i] = static_cast<long long>(ans[i-1])*(rowIndex - i + 1)/i;
  }

  return ans;
}

// time complexity O(k^2), space complexity O(k)
std::vector<int> getRowAdd(int rowIndex) {
  std::vector<int> ans(rowIndex+1, 1);
  for(int i=1; i<=rowIndex ; ++i) {
    for(int j=i-1; j>=1; --j) ans[j] += ans[j-1];
  }

  return ans;
}

#endif //LEECODE_109_H
