//
// Created by jun on 10/30/17.
//

#ifndef LEECODE_021_H
#define LEECODE_021_H

#include "../data_structures/linked_list.h"

/**
 * 21. Merge Two Sorted Lists
 *
 * Merge two sorted linked lists and return it as a new list. The new
 * list should be made by splicing together the nodes of the first
 * two lists.
 *
 */

ListNode* mergeTwoSortedLists(ListNode* l1, ListNode* l2) {
  ListNode dummy = ListNode(0);

  auto curr = &dummy;
  while (l1 != nullptr && l2!= nullptr) {
    if (l1->val < l2->val) {
      curr->next = l1;
      l1 = l1->next;
    } else {
      curr->next = l2;
      l2 = l2->next;
    }
    curr = curr->next;
  }

  curr->next = l1 ? l1 : l2;

  return dummy.next;
}

ListNode* mergeTwoSortedListsRecursive(ListNode* l1, ListNode* l2) {
  if (l1 == nullptr) return l2;
  if (l2 == nullptr) return l1;

  if (l1->val < l2->val) {
    l1->next = mergeTwoSortedListsRecursive(l1->next, l2);
    return l1;
  }

  l2->next = mergeTwoSortedListsRecursive(l1, l2->next);
  return l2;
}

#endif //LEECODE_021_H
