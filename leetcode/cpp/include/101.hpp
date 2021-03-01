//
// Created by jun on 12/22/17.
//

#ifndef LEECODE_101_H
#define LEECODE_101_H

#include "../test/binary_tree.h"

/**
 * 101. Symmetric Tree
 *
 * Given a binary tree, check whether it is a mirror of itself (ie,
 * symmetric around its center).
 */

// time complexity O(N)
//
// The number of recursive calls is bound by the height of the tree.
// In the worst case, the tree is linear and the height is in O(N).
// Therefore, space complexity due to recursive calls on the stack
// is O(N) in the worst case.
bool isMirror(TreeNode* left, TreeNode* right) {
  if (left == nullptr && right == nullptr) return true;
  if (left == nullptr || right == nullptr) return false;
  if (left->val != right->val) return false;

  return (isMirror(left->left, right->right) && isMirror(left->right, right->left));
}

bool isSymmetric(TreeNode* root) {
  return isMirror(root, root);
}

#endif //LEECODE_101_H
