//
// Created by jun on 11/3/17.
//

#ifndef LEECODE_020_H
#define LEECODE_020_H

#include <stack>
#include <string>

/**
 * 20. Valid Parentheses
 *
 * Given a string containing just the characters '(', ')', '{', '}',
 * '[' and ']', determine if the input string is valid. The brackets
 * must close in the correct order, "()" and "()[]{}" are all valid
 * but "(]" and "([)]" are not.
 *
 * @param s: input string
 * @return: true for valid and false for invalid.
 */

// time complexity O(N), space complexity O(N)
bool isValid(std::string s) {
  std::stack<char> tracker;

  for (auto c : s) {
    if (c == ')') {
      if (tracker.empty() || tracker.top() != '(') return false;
      else tracker.pop();
    } else if (c == '}') {
      if (tracker.empty() || tracker.top() != '{') return false;
      else tracker.pop();
    } else if (c == ']'){
      if (tracker.empty() || tracker.top() != '[') return false;
      else tracker.pop();
    } else {
      tracker.push(c);
    }
  }

  return tracker.empty();
}

#endif //LEECODE_020_H
