//
// Created by jun on 10/29/17.
//

#ifndef LEECODE_107_H
#define LEECODE_107_H

#include <vector>
#include <queue>

#include "../test/binary_tree.h"

/**
 * 107. Binary Tree Level Order Traversal II
 *
 * Given a binary tree, return the bottom-up level order traversal of
 * its nodes' values. (ie, from left to right, level by level from leaf
 * to root).

 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *    3
 *   / \
 *  9  20
 *    /  \
 *   15   7
 * return its bottom-up level order traversal as:
 * [
 *  [15,7],
 *  [9,20],
 *  [3]
 * ]
 *
 */

// same as 102 except reverse the vector in the end
std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) {
  std::vector<std::vector<int>> ans;
  if (root == nullptr) return ans;

  std::queue<TreeNode*> tracker;

  tracker.push(root);
  while (!tracker.empty()) {
    int m = tracker.size();
    std::vector<int> level_elements;
    for (int i=0; i<m; ++i) {
      auto node = tracker.front();
      level_elements.push_back(node->val);
      tracker.pop();
      if (node->left != nullptr) tracker.push(node->left);
      if (node->right != nullptr) tracker.push(node->right);
    }
    ans.push_back(level_elements);
  }

  for (int i=0, j=ans.size()-1; i<j; ++i, --j) std::swap(ans[i], ans[j]);

  return ans;
}

#endif //LEECODE_107_H
