//
// Created by jun on 10/17/17.
//

#ifndef LEECODE_061_H
#define LEECODE_061_H

#include "../test/linked_list.h"


/**
 * 61. Rotate List
 *
 * Given a list, rotate the list to the right by k places, where k is
 * non-negative.

 * For example:
 * Given 1->2->3->4->5->NULL
 * if k == 1, return 5->1->2->3->4->NULL
 * if k == 2, return 4->5->1->2->3-->NULL
 */

// Time complexity O(N), space complexity O(1)
ListNode* rotateRight(ListNode* head, int k) {
  if (head == nullptr || k == 0 ) { return head; }

  // find the tail and count the length
  int length = 1;
  auto tail = head;
  while (tail->next != nullptr) {
    tail = tail->next;
    ++length;
  }

  // determine the index of the new tail
  int new_tail_idx = length - k % length;
  if (new_tail_idx == length) return head;

  // find the new tail node
  auto new_tail = head;
  for (int i=0; i<new_tail_idx - 1; ++i) {
    new_tail = new_tail->next;
  }

  auto new_head = new_tail->next;
  // disconnect new tail with the rest node
  new_tail->next = nullptr;
  // connect the original tail to original head;
  tail->next = head;

  return new_head;
}

#endif //LEECODE_061_H
