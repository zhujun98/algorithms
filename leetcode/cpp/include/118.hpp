//
// Created by jun on 10/27/17.
//

#ifndef LEECODE_108_H
#define LEECODE_108_H

#include <vector>

/**
 * 118. Pascal's Triangle
 *
 * Given numRows, generate the first numRows of Pascal's triangle.

 * For example, given numRows = 5,
 * Return

 * [
 *      [1],
 *     [1,1],
 *    [1,2,1],
 *   [1,3,3,1],
 *  [1,4,6,4,1]
 * ]
 */

// we can take advantage of the relationship that
// C(n, k) = C(n, k-1)*(n - k - 1)/k
//
// time complexity O(N^2)
// space complexity O(1) + space to store the answer
std::vector<std::vector<int>> generatePascalTriangle(int numRows) {
  std::vector<std::vector<int>> ans;

  for (int i=0; i<numRows; ++i) {
    std::vector<int> row(i+1, 1);
    // use long long here to avoid overflow when doing the following
    // multiplication
    long long num = 1;
    for (int j=1; j < i; ++j) {
      // we can not write num *= (i - j + 1)/j since the right hand
      // side will be zero when i - j + 1 < j.
      num = num*(i - j + 1)/j;
      row[j] = num;
    }
    ans.emplace_back(std::move(row));
  }

  return ans;
}

// time complexity O(N^2)
// space complexity O(N) + space to store the answer
std::vector<std::vector<int>> generatePascalTriangleAdd(int numRows) {
  std::vector<std::vector<int>> ans;

  std::vector<int> last_row(numRows, 1);
  for (int i=0; i<numRows; ++i) {
    std::vector<int> row(i+1, 1);
    for (int j=1; j < i; ++j) {
      row[j] = last_row[j-1] + last_row[j];
    }
    for (int j=0; j<row.size(); ++j) last_row[j] = row[j];
    ans.emplace_back(std::move(row));
  }

  return ans;
}

#endif //LEECODE_108_H
