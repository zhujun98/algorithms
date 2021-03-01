//
// Created by jun on 10/19/17.
//

#ifndef LEECODE_144_H
#define LEECODE_144_H

#include <vector>
#include <stack>

#include "../test/binary_tree.h"

/**
 * 144. Binary Tree Preorder Traversal
 *
 * Given a binary tree, return the preorder traversal of its nodes' values.

 * For example:
 * Given binary tree {1,#,2,3},
 *   1
 *    \
 *     2
 *    /
 *   3
 * return [1,2,3].
 */

void preorderTraversal(TreeNode* root, std::vector<int>& vec) {
  if (root == nullptr) return;
  vec.push_back(root->val);

  preorderTraversal(root->left, vec);
  preorderTraversal(root->right, vec);
}

std::vector<int> preorderTraversal(TreeNode* root) {
  std::vector<int> ans;

  preorderTraversal(root, ans);

  return ans;
}

// Similar to in-order traverse, but store the right node in a stack
std::vector<int> preorderTraversalIterative(TreeNode* root) {
  std::vector<int> ans;
  if (root == nullptr) return ans;

  std::stack<TreeNode*> tracker;
  auto curr = root;
  while (curr != nullptr || !tracker.empty()) {
    if (curr == nullptr) {
      curr = tracker.top();
      tracker.pop();
    }

    ans.push_back(curr->val);

    if (curr->right != nullptr) tracker.push(curr->right);
    curr = curr->left;
  }

  return ans;
}

#endif //LEECODE_144_H
