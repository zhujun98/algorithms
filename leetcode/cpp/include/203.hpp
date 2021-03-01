//
// Created by jun on 10/14/17.
//

#ifndef LEECODE_203_H
#define LEECODE_203_H

#include "../test/linked_list.h"


/**
 * 203. Remove Linked List Elements
 *
 * Remove all elements from a linked list of integers that have value val.

 * Example
 * Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
 * Return: 1 --> 2 --> 3 --> 4 --> 5
 */
inline ListNode* removeElements(ListNode* head, int val) {
  ListNode dummy(0);
  dummy.next = head;

  auto prev = &dummy;
  auto curr = head;
  while (curr != nullptr) {
    if (curr->val == val) {
      prev->next = curr->next;
    } else {
      prev = prev->next;
    }
    curr = curr->next;
  }

  return dummy.next;
}

#endif //LEECODE_203_H
