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
bool validate(TreeNode* node, TreeNode* low, TreeNode* high) {
  if (node == nullptr) return true;

  if (low != nullptr && node->val <= low->val) return false;
  if (high != nullptr && node->val >= high->val) return false;

  return validate(node->left, low, node) && validate(node->right, node, high);
}

bool isValidBST(TreeNode* root) {
  return validate(root, nullptr, nullptr);
}

// In order search: Left -> node -> right, we validate the current element should
//                  be smaller than the next one
class IsValidBSTInorder {
  TreeNode* prev;

  bool validateInorder(TreeNode* node) {
    if (node == nullptr) return true;

    if (!validateInorder(node->left)) return false;

    if (prev != nullptr && node->val <= prev->val) return false;

    // This is the tricky part! The node 'prev' is shared by all
    // the recursively called functions. The 'prev' node is the left node of
    // the current node, whenever a function on the current left-most
    // node returns, the 'prev' will be set to this left-most node.
    prev = node;
    return validateInorder(node->right);
  }

public:
  bool operator()(TreeNode* root) {
    return validateInorder(root);
  }
};


#endif //LEETCODE_ALGO_CPP_098_H
