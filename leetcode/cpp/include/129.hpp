//
// Created by jun on 10/31/17.
//

#ifndef LEECODE_129_H
#define LEECODE_129_H

#include "../test/binary_tree.h"


/**
 * 129. Sum Root to Leaf Numbers
 *
 * Given a binary tree containing digits from 0-9 only, each
 * root-to-leaf path could represent a number.

 * An example is the root-to-leaf path 1->2->3 which represents
 * the number 123.

 * Find the total sum of all root-to-leaf numbers.

 * For example,

 *    1
 *   / \
 *  2   3

 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.

 * Return the sum = 12 + 13 = 25.
 *
 */

// Time complexity O(N)
// Space complexity O(h), where h is the height of the tree
int sumNumbers(TreeNode* root, int x) {
  int num = 10 * x + root->val;
  if (root->right == nullptr && root->left == nullptr) return num;

  int val = 0;
  if (root->left != nullptr) val += sumNumbers(root->left, num);
  if (root->right != nullptr) val += sumNumbers(root->right, num);

  return val;
}

int sumNumbers(TreeNode* root) {
  if (root == nullptr) return 0;
  return sumNumbers(root, 0);
}



#endif //LEECODE_129_H
