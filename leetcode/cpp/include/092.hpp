#ifndef LEECODE_092_H
#define LEECODE_092_H

#include "../test/linked_list.h"


/**
 * 92. Reverse Linked List II
 *
 * Reverse a linked list from position m to n. Do it in-place and in
 * one-pass.

 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,

 * return 1->4->3->2->5->NULL.

 * Note:
 * Given m, n satisfy the following condition:
 * 1 ≤ m ≤ n ≤ length of list.
 */

// time complexity O(N), space complexity O(1)
ListNode* reverseBetween(ListNode* head, int m, int n) {
  ListNode dummy(0);
  dummy.next = head;

  auto prev = &dummy;

  for (int i=0; i < m - 1; ++i) prev = prev->next;
  auto curr = prev->next;
  // fix prev and curr, move prev->next and curr->next to control the
  // reverse
  for (int i=0; i < n - m; ++i) {
    auto tmp = curr->next;
    curr->next = tmp->next;
    tmp->next = prev->next;
    prev->next = tmp;
  }

  return dummy.next;
}

#endif //LEECODE_092_H
