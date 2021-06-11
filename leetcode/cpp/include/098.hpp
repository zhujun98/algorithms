#ifndef LEETCODE_ALGO_CPP_098_H
#define LEETCODE_ALGO_CPP_098_H

/**
 * 98. Validate Binary Search Tree
 *
 * A valid BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 *
 * Caveat: The subtree of a node, for example, the left subtree can be a valid BST but
 *         contains nodes with keys greater than the node's key.
 */

// Iterative traverse with valid range
// Time complexity O(N), space complexity O(N)
bool validate(TreeNode* root, TreeNode* low, TreeNode* high) {
  if (root == nullptr) return true;

  if (low != nullptr && root->val <= low->val) return false;
  if (high != nullptr && root->val >= high->val) return false;

  return validate(root->left, low, root) && validate(root->right, root, high);
}

bool isValidBST(TreeNode* root) {
  return validate(root, nullptr, nullptr);
}

#endif //LEETCODE_ALGO_CPP_098_H
