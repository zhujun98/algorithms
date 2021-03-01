//
// Created by jun on 10/31/17.
//

#ifndef LEECODE_089_H_H
#define LEECODE_089_H_H

#include <vector>

/**
 * 89. Gray Code
 *
 * The gray code is a binary numeral system where two successive values
 * differ in only one bit.

 * Given a non-negative integer n representing the total number of bits
 * in the code, print the sequence of gray code. A gray code sequence
 * must begin with 0.

 * For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

 * 00 - 0
 * 01 - 1
 * 11 - 3
 * 10 - 2
 */

// Time complexity O(n), where n is the number of bits
// Space complexity O(2^n)
std::vector<int> grayCode(int n) {
  std::vector<int> vec{0};
  for (int i=0; i<n; ++i) {
    int m = vec.size();
    for (int j=m-1; j>=0; --j) {
      auto num = vec[j] + (1<<i);
      vec.push_back(num);
    }
  }

  return vec;
}

#endif //LEECODE_089_H_H
