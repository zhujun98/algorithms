//
// Created by jun on 11/4/17.
//

#include "data_structures/linked_list.hpp"

#include <vector>
#include <queue>

#ifndef LEECODE_023_H
#define LEECODE_023_H

/**
 * 23. Merge k Sorted Lists
 *
 * Merge k sorted linked lists and return it as one sorted list.
 */

// divide and conquer

// time complexity: O(kN), N is the total number of nodes and k is the
// total number of linked lists
// space complexity: O(1)
ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
  ListNode dummy(0);

  auto head = &dummy;

  while (l1 != nullptr && l2 != nullptr) {
    if (l1->val < l2->val) {
      head->next = l1;
      l1 = l1->next;
    } else {
      head->next = l2;
      l2 = l2->next;
    }
    head = head->next;
  }

  head->next = (l1 == nullptr ? l2 : l1);

  return dummy.next;
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
  while (lists.size() > 1) {
    // size() will change because of the pop_back() operation
    int m = lists.size();
    for (int i=0; i<m/2; ++i) {
      lists[i] = merge2Lists(lists[i], lists[m-1-i]);
      lists.pop_back();
    }
  }
  if (lists.empty()) return nullptr;
  return lists[0];
}


// using data structure priority_queue
// time complexity: O(Nlogk)
// space complexity: priority_queue O(k)
ListNode* mergeKListsPQ(std::vector<ListNode*>& lists) {
  auto comp = [] (ListNode* l1, ListNode*l2) { return (l1->val > l2->val); };

  std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comp)> pqueue(comp);
  ListNode dummy(0);

  for (auto &v : lists) {
    if (v != nullptr) pqueue.push(v);
  }

  auto curr = &dummy;
  while (!pqueue.empty()) {
    curr->next = pqueue.top();
    curr = curr->next;
    pqueue.pop();
    if (curr->next != nullptr) pqueue.push(curr->next);
  }

  return dummy.next;
}

#endif //LEECODE_023_H
