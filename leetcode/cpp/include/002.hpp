//
// Created by jun on 3/4/18.
//

#ifndef LEECODE_002_HPP
#define LEECODE_002_HPP

/**
 * 2. Add Two Numbers
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their
 * nodes contain a single digit. Add the two numbers and return it as a
 * linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except
 * the number 0 itself.
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 */
#include "linked_list.hpp"

// time complexity O(N), space complexity O(N), where N is the length
// of the longer linked list

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
  auto dummy = ListNode(0);
  auto curr = &dummy;
  int carry = 0;
  while (l1 != nullptr || l2 != nullptr || carry != 0)
  {
    int x = 0;
    int y = 0;
    if (l1 != nullptr)
    {
      x = l1->val;
      l1 = l1->next;
    }
    if (l2 != nullptr)
    {
      y = l2->val;
      l2 = l2->next;
    }
    curr->next = new ListNode(x + y + carry);
    curr = curr->next;
    carry = curr->val / 10;
    curr->val %= 10;
  }
  
  return dummy.next;
}


#endif //LEECODE_002_HPP
