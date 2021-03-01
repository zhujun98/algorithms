//
// Created by jun on 2/17/18.
//

#ifndef LEECODE_022_H
#define LEECODE_022_H

/**
 * 22. Generate Parentheses
 *
 * Given n pairs of parentheses, write a function to generate all
 * combinations of well-formed parentheses.
 *
 * For example, given n = 3, a solution set is:
 * [
 *  "((()))",
 *  "(()())",
 *  "(())()",
 *  "()(())",
 *  "()()()"
 * ]
 */
#include <vector>
#include <string>


void generateParenthesis(std::vector<std::string>& ans,
                         const std::string& current,
                         int left,
                         int right,
                         int n) {
  if (left == n && right == n) {
    ans.push_back(current);
    return;
  }

  if (left > right) generateParenthesis(ans, current + ')', left, right+1, n);

  if (left < n) generateParenthesis(ans, current + '(', left+1, right, n);
}


// time complexity O(n*Cat(n))
// space complexity O(n*Cat(n))
// where Cat(n) is the nth Catalan number.
// There are Cat(n) possible valid strings that are valid combinations
// of parenthesis, and for each a string of length n is created.
std::vector<std::string> generateParenthesis(int n) {
  std::vector<std::string> ans;
  std::string current;
  generateParenthesis(ans, current, 0, 0, n);

  return ans;
}


#endif //LEECODE_022_H
