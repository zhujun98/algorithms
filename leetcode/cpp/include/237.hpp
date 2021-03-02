//
// Created by jun on 12/21/17.
//

#ifndef LEECODE_237_H
#define LEECODE_237_H

#include "linked_list.hpp"

/**
 * 237. Delete Node in a Linked List
 *
 * Write a function to delete a node (except the tail) in a singly
 * linked list, given only access to that node.
 *
 * Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third
 * node with value 3, the linked list should become 1 -> 2 -> 4 after
 * calling your function.
 *
 * @param node: to be deleted node
 */
void deleteNode(ListNode* node) {
  if (node == nullptr || node->next == nullptr) return;
  auto next = node->next;
  node->val = next->val;
  node->next = next->next;
  delete next;
}

#endif //LEECODE_237_H
