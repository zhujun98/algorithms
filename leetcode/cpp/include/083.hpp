//
// Created by jun on 3/4/18.
//

#ifndef LEECODE_083_HPP
#define LEECODE_083_HPP

/**
 * 83. Remove Duplicates from Sorted List
 *
 * Given a sorted linked list, delete all duplicates such that each
 * element appear only once.

 * For example,
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
 */
#include "linked_list.hpp"


// time complexity O(N), space complexity O(1)
ListNode* deleteDuplicates(ListNode* head) {
  if (head != nullptr) {
    auto slow = head;
    auto fast = head->next;
    while (fast != nullptr) {
      if (fast->val != slow->val) {
        slow = slow->next;;
      } else {
        auto next = slow->next;
        slow->next = fast->next;
        delete next;
      }
  
      fast = slow->next;
    }
  }
  return head;
}


#endif //LEECODE_083_HPP
