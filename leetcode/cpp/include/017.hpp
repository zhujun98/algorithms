//
// Created by jun on 11/6/17.
//

#include <vector>
#include <string>

#ifndef LEECODE_017_H
#define LEECODE_017_H

/**
 * 17. Letter Combinations of a Phone Number
 *
 * Given a digit string, return all possible letter combinations
 * that the number could represent.

 * A mapping of digit to letters (just like on the telephone buttons)
 * is given below.

 * Input:Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 */

// Standard backtracking solution
void letterCombinations(const std::string& digits,
                        const std::vector<std::string>& pattern,
                        std::vector<std::string>& ans,
                        std::string& comb,
                        int start)
{
  if (comb.size() == digits.size())
  {
    ans.push_back(comb);
    return;
  }

  for (int i=start; i<digits.size(); ++i)
  {
    int num = digits[i] - '0';
    for (int j=0; j<pattern[num].size(); ++j)
    {
      comb.push_back(pattern[num][j]);
      letterCombinations(digits, pattern, ans, comb, i+1);
      comb.pop_back();
    }
  }
}

std::vector<std::string> letterCombinations(std::string digits)
{
  if (digits.empty()) return {};
  for (auto c : digits)
  {
    if (c == '0' || c == '1') return {};
  }

  std::vector<std::string> ans;

  std::vector<std::string> pattern
      {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  std::string comb;

  letterCombinations(digits, pattern, ans, comb, 0);

  return ans;
}

#endif //LEECODE_017_H
