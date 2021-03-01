//
// Created by jun on 10/28/17.
//

#ifndef LEECODE_96_H
#define LEECODE_96_H

#include <vector>

/**
 * 96. Unique Binary Search Trees
 *
 * Given n, how many structurally unique BST's (binary search trees)
 * that store values 1...n?

 * For example,
 * Given n = 3, there are a total of 5 unique BST's.

 *  1         3     3      2      1
 *   \       /     /      / \      \
 *    3     2     1      1   3      2
 *   /     /       \                 \
 *  2     1         2                 3
 */

// DP solution:
// We change the root node from 1 to n, then we have two sorted array
// to form the left and right tree. The numbers of structures for
// sorted arrays are the same if the length of these sorted arrays are
// the same. Denoting f(i) as number of structures for an array with
// length i, then f(i+1) = f(0)*f(i) + f(1)*f(i-1) + ... + f(i)*f(0)
//
// time complexity O(N^2), space complexity O(N)
int numTrees(int n) {
  std::vector<int> count(n+1, 0);
  count[0] = 1;
  count[1] = 1;
  for (int i=2; i<=n; ++i) {
    for (int j=0; j<i; ++j) count[i] += count[j]*count[i-j-1];
  }
  return count.back();
}

#endif //LEECODE_96_H
