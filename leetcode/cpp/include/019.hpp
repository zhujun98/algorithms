//
// Created by jun on 2/22/18.
//

#ifndef LEECODE_019_H
#define LEECODE_019_H

/**
 * 19. Remove Nth Node From End of List
 *
 * Remove the nth-to-last element of a linked list and return the head.
 *
 * For example,

 * Given linked list: 1->2->3->4->5, and n = 2.
 * After removing the second node from the end, the linked list becomes 1->2->3->5.
 *
 * Note:
 *   Given n will always be valid.
 *   Try to do this in one pass.
 */
#include "linked_list.hpp"


ListNode* removeNthFromEnd(ListNode* head, int n) {
  if (n == 0) return head;
  
  auto slow = head;
  auto fast = head;
  for (int i=0; i<n; ++i) fast = fast->next;

  // If head node should be deleted
  if (fast == nullptr) {
    return head->next;
  }

  while (fast->next != nullptr) {
    fast = fast->next;
    slow = slow->next;
  }

  auto next = slow->next->next;
  delete slow->next;
  slow->next = next;
  return head;
}


#endif //LEECODE_019_H
