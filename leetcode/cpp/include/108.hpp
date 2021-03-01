//
// Created by jun on 10/29/17.
//

#ifndef LEECODE_108_H
#define LEECODE_108_H

#include <vector>

#include "../test/binary_tree.h"

/**
 * 108. Convert Sorted Array to Binary Search Tree
 *
 * Given an array where elements are sorted in ascending order, convert
 * it to a height balanced BST.
 */

// Time complexity T(N) = 2T(N/2) + C, apply the master method -> O(N)
//
// space complexity O(h), worst case O(N)
TreeNode* sortedArrayToBST(std::vector<int>& nums, int start, int end) {
  int mid = (start + end)/2;
  auto p = new TreeNode(nums[mid]);
  start < mid ? p->left = sortedArrayToBST(nums, start, mid-1) : p->left = nullptr;
  mid < end ? p->right = sortedArrayToBST(nums, mid+1, end) : p->right = nullptr;

  return p;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums) {
  if (nums.empty()) return nullptr;
  return sortedArrayToBST(nums, 0, nums.size()-1);
}

#endif //LEECODE_108_H
