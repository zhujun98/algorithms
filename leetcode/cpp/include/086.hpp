//
// Created by jun on 4/25/18.
//

#ifndef LEECODE_086_HPP
#define LEECODE_086_HPP

/**
 * 86. Partition List
 *
 * Given a linked list and a value x, partition it such that all nodes
 * less than x come before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in
 * each of the two partitions.
 *
 * For example,
 * Given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->3->4->5.
 *
 * @param x: the number for partition
 * @return: head node of the new partitioned list
 */

// time complexity O(N),
// space complexity O(N) (require only extract space for pointers)
ListNode* partition(ListNode* head, int x) {
  ListNode l_dummy(0);
  ListNode r_dummy(0);
  auto l_head = &l_dummy;
  auto r_head = &r_dummy;

  auto curr = head;
  while (curr != nullptr) {
    if (curr->val < x) {
      l_head->next = curr;
      curr = l_head->next->next;
      l_head = l_head->next;
      l_head->next = nullptr;
    } else {
      r_head->next = curr;
      curr = r_head->next->next;
      r_head = r_head->next;
      r_head->next = nullptr;
    }
  }

  l_head->next = r_dummy.next;

  return l_dummy.next;
}

#endif //LEECODE_086_HPP
