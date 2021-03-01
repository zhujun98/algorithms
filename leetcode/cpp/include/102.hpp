//
// Created by jun on 10/16/17.
//

#ifndef LEECODE_101_H
#define LEECODE_101_H

#include <vector>
#include <queue>

#include "../test/binary_tree.h"


/**
 * 102. Binary Tree Level Order Traversal
 *
 * Given a binary tree, return the level order traversal of its nodes'
 * values. (ie, from left to right, level by level).

 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
      3
     / \
    9  20
      /  \
     15   7
 * return its level order traversal as:
  [
    [3],
    [9,20],
    [15,7]
  ]
 */

// Iterative solution
// time complexity O(N), space complexity O(N)
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
  std::vector<std::vector<int>> ans;

  if (root == nullptr) return ans;

  std::queue<TreeNode*> tracker; // use queue for level order traverse
  tracker.push(root);

  while (!tracker.empty()) {
    std::vector<int> level_elements;
    // tracker.size() will change in the following loop
    size_t m = tracker.size();
    for (size_t i = 0; i < m; ++i) {
      auto curr = tracker.front();
      tracker.pop();
      level_elements.push_back(curr->val);
      if (curr->left != nullptr) tracker.push(curr->left);
      if (curr->right != nullptr) tracker.push(curr->right);
    }

    ans.emplace_back(std::move(level_elements));
  }

  return ans;
}

#endif //LEECODE_101_H
