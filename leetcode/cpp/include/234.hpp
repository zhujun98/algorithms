//
// Created by jun on 12/22/17.
//

#ifndef LEECODE_234_H
#define LEECODE_234_H

#include <stack>

/**
 * 234. Palindrome Linked List
 *
 * Given a singly linked list, determine if it is a palindrome.
 */


// time complexity O(N), space complexity O(N)
//bool isPalindromeStack(ListNode* head) {
//  if (head == nullptr || head->next == nullptr) return true;
//
//  auto slow = head;
//  auto fast = head;
//  std::stack<int> first_half;
//
//  // push the first half into a stack
//  while (fast != nullptr && fast->next != nullptr) {
//    first_half.push(slow->val);
//    slow = slow->next.get();
//    fast = fast->next->next.get();
//  }
//
//  if (fast != nullptr) slow = slow->next.get();
//
//  while (slow != nullptr) {
//    if (first_half.top() != slow->val) return false;
//    first_half.pop();
//    slow = slow->next.get();
//  }
//
//  return true;
//}

// FIXME
//class LinkedList234: public LinkedList {
//
//public:
//  LinkedList234() = default;
//
//  LinkedList234(std::initializer_list<int> init_list): LinkedList(init_list) {}
//
//  // time complexity O(N), space complexity O(1)
//  bool isPalindrome() {
//    if (head_ == nullptr || head_->next == nullptr) return true;
//
//    std::unique_ptr<ListNode> prev;
//    auto left = std::move(head_);
//    auto fast = left.get();
//    // reverse the first half of the linked list
//    while (fast != nullptr && fast->next != nullptr) {
//      fast = fast->next->next.get();
//
//      auto next = std::move(left->next);
//      left->next = std::move(prev);
//      prev = std::move(left);
//      left = std::move(next);
//    }
//
//    // Now fast represents the node moving from the middle to the right.
//    // If the linked list has odd elements, move fast to the right node
//    // of the middle node.
//    if (fast != nullptr) fast = left->next.get();
//    else fast = left.get();
//    std::swap(left, prev);
//
//    bool is_palindrome = true;
//    while (left != nullptr) {
//      if (fast->val != left->val) is_palindrome = false;
//      // we need to continue recover the reversed part even if we already
//      // found out that it is not palindrome.
//
//      fast = fast->next.get();
//
//      // reverse the node
//      auto next = std::move(left->next);
//      left->next = std::move(prev);
//      prev = std::move(left);
//      left = std::move(next);
//    }
//
//    head_ = std::move(prev);
//    return is_palindrome;
//  }
//};

#endif //LEECODE_234_H
