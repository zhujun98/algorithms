//
// Created by jun on 12/23/17.
//

#ifndef LEECODE_100_H
#define LEECODE_100_H

#include "../test/binary_tree.h"

/**
 * 100. Same Tree
 *
 * Given two binary trees, write a function to check if they are equal
 * or not.
 */

// time complexity O(N), space complexity O(N)
bool isSameTree(TreeNode* p, TreeNode* q) {
  if (p == nullptr && q == nullptr) return true;
  if (p == nullptr || q == nullptr) return false;

  return (p->val == q->val &&
          isSameTree(p->left, q->left) &&
          isSameTree(p->right, q->right));
}

#endif //LEECODE_100_H
