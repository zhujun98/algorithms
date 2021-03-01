//
// Created by jun on 10/28/17.
//

#ifndef LEECODE_206_H
#define LEECODE_206_H

#include "../test/linked_list.h"

/**
 * 206. Reverse Linked List
 */

// time complexity O(N), space complexity O(1)
// Note: the linked list cannot contain a loop
ListNode* reverseList(ListNode* head) {
  ListNode* prev = nullptr;
  auto curr = head;
  while (curr != nullptr) {
    auto next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

// time complexity O(N), space complexity O(N)
ListNode* reverseListRecursive(ListNode* head) {

  if (head==nullptr || head->next==nullptr) return head;

  auto p = reverseList(head->next);
  head->next->next = head;
  head->next = nullptr;

  return p;
}

#endif //LEECODE_206_H
