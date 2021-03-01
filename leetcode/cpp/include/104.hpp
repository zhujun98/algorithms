//
// Created by jun on 12/23/17.
//

#ifndef LEECODE_104_H
#define LEECODE_104_H

#include "../test/binary_tree.h"

/**
 * 104. Maximum Depth of Binary Tree
 *
 * Given a binary tree, find its maximum depth.
 */

// depth first search
// time complexity O(N), worst case space complexity O(N)
int maxDepth(TreeNode* root) {
  if (root == nullptr) return 0;
  return (std::max(maxDepth(root->left), maxDepth(root->right)) + 1);
}

#endif //LEECODE_104_H
