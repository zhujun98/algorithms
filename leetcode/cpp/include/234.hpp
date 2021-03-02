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
 *
 * A palindrome is a word, number, phrase, or other sequence of characters
 * which reads the same backward as forward, such as madam or racecar.
 */


// time complexity O(N), space complexity O(N)
bool isPalindromeStack(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return true;

  auto slow = head;
  auto fast = head;
  std::stack<int> first_half;

  // push the first half into a stack
  while (fast != nullptr && fast->next != nullptr) {
    first_half.push(slow->val);
    slow = slow->next;
    fast = fast->next->next;
  }

  if (fast != nullptr) slow = slow->next;

  while (slow != nullptr) {
    if (first_half.top() != slow->val) return false;
    first_half.pop();
    slow = slow->next;
  }

  return true;
}

// time complexity O(N), space complexity O(1)
bool isPalindrome(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return true;

  ListNode* prev = nullptr;
  auto slow = head;
  auto fast = head;
  // reverse the first half of the linked list
  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;

    auto next = slow->next;
    slow->next = prev;
    prev = slow;
    slow = next;
  }

  // Now fast represents the node moving from the middle to the right.
  // If the linked list has odd elements, move fast to the right node
  // of the middle node.
  if (fast != nullptr) {
    fast = slow->next;
  } else {
    fast = slow;
  }
  std::swap(slow, prev);

  bool is_palindrome = true;
  while (slow != nullptr) {
    if (fast->val != slow->val) is_palindrome = false;

    // we need to continue recover the reversed part even if we already
    // found out that it is not palindrome.

    fast = fast->next;

    // reverse the node
    auto next = slow->next;
    slow->next = prev;
    prev = slow;
    slow = next;
  }

  return is_palindrome;
}

#endif //LEECODE_234_H
