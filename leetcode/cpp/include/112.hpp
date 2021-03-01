//
// Created by jun on 10/17/17.
//

#ifndef LEECODE_112_H
#define LEECODE_112_H

#include "../test/binary_tree.h"

/**
 * 112. Path Sum
 *
 * Given a binary tree and a sum, determine if the tree has a
 * root-to-leaf path such that adding up all the values along the
 * path equals the given sum.
 *
 * Note: the leaf should have no further leaves
 */

bool hasPathSum(TreeNode* root, int sum) {
  if (root == nullptr) { return false; }

  if (root->left == nullptr && root->right == nullptr && sum == root->val) {
    return true;
  }

  return (hasPathSum(root->left, sum - root->val) ||
          hasPathSum(root->right, sum - root->val));
}

#endif //LEECODE_112_H
