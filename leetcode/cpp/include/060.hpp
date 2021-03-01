//
// Created by jun on 10/17/17.
//

#ifndef LEECODE_060_H
#define LEECODE_060_H

#include <iostream>
#include <string>


/**
 * 60. Permutation Sequence
 *
 * The set [1,2,3,…,n] contains a total of n! unique permutations.

 * By listing and labeling all of the permutations in order,
 * We get the following sequence (ie, for n = 3):

  "123"
  "132"
  "213"
  "231"
  "312"
  "321"
  * Given n and k, return the kth permutation sequence.

  * Note: Given n will be between 1 and 9 inclusive.
 */

// time complexity O(N^2), sort the rest part of the string takes
// O(N) and the out loop is O(N)
// space complexity O(N)
std::string getPermutation(int n, int k) {
  std::string ans;
  size_t combs = 1;
  for (int i=1; i<=n; ++i) {
    ans.push_back('0' + i);
    combs *= i;
  }

  for (int i=0; i<n-1; ++i) {
    combs /= n - i;
    // Note use k - 1 here
    size_t m = (k - 1)/combs;
    std::swap(ans[i], ans[i+m]);
    // sort the rest part of the string
    for (size_t j = m; j > 1; --j) std::swap(ans[i+j], ans[i+j-1]);

    if (k > combs) {k -= m*combs; }
  }

  return ans;
}

#endif //LEECODE_060_H
