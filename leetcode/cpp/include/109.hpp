//
// Created by jun on 10/31/17.
//

#ifndef LEECODE_109_H
#define LEECODE_109_H

#include "../test/binary_tree.h"
#include "../test/linked_list.h"

/**
 * 109. Convert Sorted List to Binary Search Tree
 *
 * Given a singly linked list where elements are sorted in ascending
 * order, convert it to a height balanced BST.
 */

// Time complexity T(N) = 2T(N/2) + N, apply the master method -> O(NlogN)
//
// space complexity O(h), worst case O(N)
TreeNode* sortedListToBST(ListNode* head) {
  if (head == nullptr) return nullptr;
  if (head->next == nullptr) return (new TreeNode(head->val));

  // This is the pattern to find the previous node of the mid node.
  auto slow = head;
  auto fast = head->next;
  // The second line ensures that fast->next != nullptr
  while (fast->next != nullptr && fast->next->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
  }

  auto mid = slow->next;
  slow->next = nullptr;

  auto root = new TreeNode(mid->val);
  root->left = sortedListToBST(head);
  root->right = sortedListToBST(mid->next);

  return root;
}


#endif //LEECODE_109_H
