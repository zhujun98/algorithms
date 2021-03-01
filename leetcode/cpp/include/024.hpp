//
// Created by jun on 2/23/18.
//

#ifndef LEECODE_024_HPP
#define LEECODE_024_HPP

/**
 * 24. Swap Nodes in Pairs
 *
 * Given a linked list, swap every two adjacent nodes and return its
 * head.
 *
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 * Your algorithm should use only constant space. You may not modify
 * the values in the list, only nodes itself can be changed
 */
#include "linked_list.hpp"


// time complexity O(N), space complexity O(1)
ListNode* swapPairs(ListNode* head) {
  ListNode dummy(0);
  dummy.next = head;

  auto prev = &dummy;
  auto slow = dummy.next;
  while (slow != nullptr && slow->next != nullptr) {
    auto next = slow->next;
    slow->next = next->next;
    next->next = prev->next;  // prev->next is still slow
    prev->next = next;

    prev = slow;
    slow = slow->next;
  }

  return dummy.next;
}


#endif //LEECODE_024_HPP
