//
// Created by jun on 4/20/18.
//

#ifndef LEECODE_141_HPP
#define LEECODE_141_HPP


/**
 * 141. Linked List Cycle
 *
 * Given a linked list, determine if it has a cycle in it.
 */

// time complexity O(N), space complexity O(1)
bool hasCycle(ListNode *head) {
  ListNode* slow = head;
  ListNode* fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
  }
  return false;
}


#endif //LEECODE_141_HPP
