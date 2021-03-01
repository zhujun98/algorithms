//
// Created by jun on 10/25/17.
//

#ifndef LEECODE_082_H
#define LEECODE_082_H

#include "../test/linked_list.h"

/**
 * 82. Remove Duplicates from Sorted List II
 *
 * Given a sorted linked list, delete all nodes that have duplicate
 * numbers, leaving only distinct numbers from the original list.

 * For example,
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
 */

// time complexity O(N), space complexity O(1)
ListNode* deleteDuplicates(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return head;

  ListNode dummy(0);
  dummy.next = head;

  auto curr = head;
  auto prev = &dummy;
  while (curr != nullptr) {
    bool remove = false;
    while (curr->next != nullptr && curr->next->val == curr->val) {
      curr = curr->next;
      remove = true;
    }

    if (!remove) {
      prev = curr;
      curr = curr->next;
    } else {
      curr = curr->next;
      prev->next = curr;
    }
  }

  return dummy.next;
}

#endif //LEECODE_082_H
