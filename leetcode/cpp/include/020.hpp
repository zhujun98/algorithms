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
  std::unordered_map<char, char> mapping ({{')', '('}, {'}', '{'}, {']', '['}});
  for (auto c : s) {
    if (mapping.find(c) == mapping.end()) {
      tracker.push(c);
    } else {
      if (tracker.empty()) return false;
      if (tracker.top() != mapping[c]) {
        return false;
      } else {
        tracker.pop();
      }
    }
  }

  return tracker.empty();
}

#endif //LEECODE_020_H
