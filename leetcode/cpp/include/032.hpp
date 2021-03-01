//
// Created by jun on 11/4/17.
//

#include <string>
#include <stack>

#ifndef LEECODE_032_H
#define LEECODE_032_H

/**
 * 32. Longest Valid Parentheses
 *
 * Given a string containing just the characters '(' and ')', find the
 * length of the longest valid (well-formed) parentheses substring.

 * For "(()", the longest valid parentheses substring is "()", which
 * has length = 2.

 * Another example is ")()())", where the longest valid parentheses
 * substring is "()()", which has length = 4.
 */

// stack solution
// time complexity O(N), space complexity O(N)
int longestValidParentheses(std::string s) {
  std::stack<int> tracker;

  int max_len = 0;
  for (int i=0; i<s.size(); ++i) {
    if (s[i] == '(') tracker.push(i);
    else {
      if (!tracker.empty() && s[tracker.top()] == '(') {
        tracker.pop();
        if (!tracker.empty()) {
          if (i - tracker.top() > max_len) max_len = i - tracker.top();
        } else {
          if (i+1 > max_len) max_len = i+1;
        }
      }
      else tracker.push(i);
    }
  }

  return max_len;
}

#endif //LEECODE_032_H
