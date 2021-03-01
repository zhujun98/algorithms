//
// Created by jun on 10/16/17.
//

#ifndef LEECODE_94_H_H
#define LEECODE_94_H_H

#include <vector>
#include <stack>

#include "../test/binary_tree.h"

/**
 * 94. Binary Tree In-order Traversal
 *
 * Given a binary tree, return the inorder traversal of its nodes'
 * values.

 * For example:
 * Given binary tree [1,null,2,3],
     1
      \
       2
      /
     3
 * return [1,3,2].
 *
 */

void inorderTraversal(TreeNode* root, std::vector<int>& vals) {
  if (root == nullptr) return;
  inorderTraversal(root->left, vals);
  vals.push_back(root->val);
  inorderTraversal(root->right, vals);
}

// time complexity O(N),
// worst case space complexity O(N), average O(logN)
std::vector<int> inorderTraversal(TreeNode* root) {
  std::vector<int> ans;

  inorderTraversal(root, ans);

  return ans;
}

// time complexity O(N), space complexity O(N)
std::vector<int> inorderTraversalIterative(TreeNode* root) {
  std::vector<int> ans;
  if (root == nullptr) return ans;

  std::stack<TreeNode*> tracker;

  auto curr = root;
  while (curr!= nullptr || !tracker.empty()) {
    if (curr != nullptr) {
      tracker.push(curr);
      curr = curr->left;
    } else {
      curr = tracker.top();
      tracker.pop();
      ans.push_back(curr->val);
      curr = curr->right;
    }
  }

  return ans;
}

#endif //LEECODE_94_H_H
