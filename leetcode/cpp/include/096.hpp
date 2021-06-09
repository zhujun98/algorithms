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
// to form the left and right trees. Assume the root note is i, then
// the number of structures is is G(i-1) * G(n-i) since the left tree
// has i-1 elements and the right tree has n-i elements. And G(n) is
// sum(G(i-1) * G(n-i)) for i = 1,..,n.
//
// time complexity O(N^2), space complexity O(N)
int numTrees(int n) {
  std::vector<int> count(n+1, 0);
  count[0] = 1;
  count[1] = 1;
  for (int i=2; i<=n; ++i) {
    for (int j=1; j<=i; ++j) {
      count[i] += count[j-1] * count[i-j];
    }
  }
  return count.back();
}

#endif //LEECODE_96_H
