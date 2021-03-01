//
// Created by jun on 10/30/17.
//

#ifndef LEECODE_148_H
#define LEECODE_148_H

#include "021.h"


/**
 * 148. Sort List
 *
 * Sort a linked list in O(n log n) time using constant space complexity.
 */
ListNode* sortList(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return head;

  // find the list length using a fast node
  int count = 0;
  auto fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    ++count;
  }
  count *= 2;
  count += (fast == nullptr ? 0 : 1);

  // find the tail of the first split
  auto slow = head;
  for (int i=0; i<count/2 - 1; ++i) slow = slow->next;

  // disconnect the two splits and apply merge sort recursively
  auto next = slow->next;
  slow->next = nullptr;

  auto l1 = sortList(head);
  auto l2 = sortList(next);

  return mergeTwoSortedLists(l1, l2);
}

#endif //LEECODE_148_H
