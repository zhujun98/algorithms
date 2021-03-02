//
// Created by jun on 9/28/19.
//

#ifndef LEETCODE_ALGORITHMS_CPP_160_HPP
#define LEETCODE_ALGORITHMS_CPP_160_HPP

#include "linked_list.hpp"

/**
 * 160. Intersection of Two Linked Lists.
 *
 * Write a program to find the node at which the intersection of two
 * singly linked lists begins.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
// time complexity O(m + n), space complexity O(1)
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

  ListNode* pa = headA;
  ListNode* pb = headB;
  
  // count lengths
  int la = 0;
  while (pa != nullptr) {
      ++la;
      pa = pa->next;
  }
  int lb = 0;
  while (pb != nullptr) {
      ++lb;
      pb = pb->next;
  }
  
  pa = headA;
  pb = headB;
  if (la > lb) {
      for (int i=0; i<la - lb; ++i) pa = pa->next;
  } else if (lb > la) {
      for (int i=0; i<lb - la; ++i) pb = pb->next;
  }
  
  while (pa != pb) {
      pa = pa->next;
      pb = pb->next;
  }
  
  return pa;
}

#endif //LEETCODE_ALGORITHMS_CPP_160_HPP
