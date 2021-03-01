//
// Created by jun on 10/17/17.
//

#ifndef LEECODE_113_H
#define LEECODE_113_H

#include <vector>

#include "../test/binary_tree.h"

/**
 * 113. Path Sum II
 *
 * Given a binary tree and a sum, find all root-to-leaf paths where
 * each path's sum equals the given sum.

 * For example:
 * Given the below binary tree and sum = 22,
                5
               / \
              4   8
             /   / \
            11  13  4
           /  \    / \
          7    2  5   1
 * return
   [
     [5,4,11,2],
     [5,8,4,5]
   ]
 */

// backtracking
void pathSum(TreeNode* root, int sum, std::vector<int>& vec, std::vector<std::vector<int>>& sum_set) {
  vec.push_back(root->val);
  sum -= root->val;
  if (root->left == nullptr && root->right == nullptr && sum == 0) sum_set.push_back(vec);

  if (root->left != nullptr) pathSum(root->left, sum, vec, sum_set);
  if (root->right != nullptr) pathSum(root->right, sum, vec, sum_set);
  vec.pop_back();
}

std::vector<std::vector<int>> pathSum(TreeNode* root, int sum) {
  std::vector<std::vector<int>> ans;
  if (root == nullptr) return ans;

  std::vector<int> vec;
  pathSum(root, sum, vec, ans);

  return ans;
}

#endif //LEECODE_113_H
