//
// Created by jun on 10/19/17.
//

#ifndef LEECODE_111_H
#define LEECODE_111_H

#include "../test/binary_tree.h"

/**
 * 111. Minimum Depth of Binary Tree
 *
 * Given a binary tree, find its minimum depth.

 * The minimum depth is the number of nodes along the shortest path from
 * the root node down to the nearest leaf node.
 */
int minDepth(TreeNode* root) {
  if (root == nullptr) return 0;

  if (root->left == nullptr) return (1 + minDepth(root->right));
  if (root->right == nullptr) return (1 + minDepth(root->left));

  return (1 + std::min(minDepth(root->right), minDepth(root->left)));
}

#endif //LEECODE_111_H
