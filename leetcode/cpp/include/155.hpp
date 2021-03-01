//
// Created by jun on 12/23/17.
//

#ifndef LEECODE_155_H
#define LEECODE_155_H

#include <stack>

/**
 * 155. Min Stack
 *
 * Design a stack that supports push, pop, top, and retrieving the
 * minimum element in constant time.

 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * getMin() -- Retrieve the minimum element in the stack.
 *
 */
class MinStack {
  std::stack<int> data_;
  std::stack<int> min_data_;
public:
  void push(int x) {
    data_.push(x);
    if (min_data_.empty() || x <= min_data_.top()) min_data_.push(x);
  }

  void pop() {
    if (data_.empty()) return;
    if (data_.top() == min_data_.top()) min_data_.pop();
    data_.pop();
  }

  int top() {
    if (data_.empty()) throw std::out_of_range("Empty stack!");
    return data_.top();
  }

  int getMin() {
    return min_data_.top();
  }
};

#endif //LEECODE_155_H
