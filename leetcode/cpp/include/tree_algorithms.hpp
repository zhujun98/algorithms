//
// Created by jun on 10/13/17.
//

#ifndef TREE_TREE_ALGORITHMS_H
#define TREE_TREE_ALGORITHMS_H


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 98. Validate Binary Search Tree
 *
 * Given a binary tree, determine if it is a valid binary search
 * tree (BST).
 */

// use two node lb and rb to track the minimum and maximum allowed
// 'val' of the current root->val
inline bool isValidBST(TreeNode* root, TreeNode* lb, TreeNode* rb) {
  if (root == nullptr) { return true; }

  if (lb != nullptr && root->val <= lb->val) { return false; }
  if (rb != nullptr && root->val >= rb->val) { return false; }

  return (isValidBST(root->left, lb, root) &&
          isValidBST(root->right, root, rb));
}

// time complexity: worst case O(N), space complexity: worst case O(N)
inline bool isValidBST(TreeNode* root)
{
  return isValidBST(root, nullptr, nullptr);
}

// In-order traverse, pointer 'prev' is passed by reference since we are going
// to modify it.

// time complexity: worst case O(N), space complexity: worst case O(N)
// Also the space complexity is still linear, but we can save the effort
// to store the 'lb' and 'rb' nodes.
bool isValidBST(TreeNode* root, TreeNode* &prev) {
  if (root == nullptr) { return true; }

  // track down until the left most node
  if (!isValidBST(root->left, prev)) { return false; }

  // check the right node
  if (prev != nullptr && root->val <= prev->val) { return false; }

  prev = root;

  // check the tree rooted at the right node
  return isValidBST(root->right, prev);
}

bool isValidBSTInOrderTraverse(TreeNode* root) {
  TreeNode* prev = nullptr;

  return isValidBST(root, prev);
}


#endif //TREE_TREE_ALGORITHMS_H
