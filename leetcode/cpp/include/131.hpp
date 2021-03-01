//
// Created by jun on 11/1/17.
//

#ifndef LEECODE_131_H
#define LEECODE_131_H

#include <vector>
#include <string>


/**
 * 131. Palindrome Partitioning
 *
 * Given a string s, partition s such that every substring of the
 * partition is a palindrome.

 * Return all possible palindrome partitioning of s.

 * For example, given s = "aab",
 * Return

 * [
 *   ["aa","b"],
 *   ["a","a","b"]
 * ]
 */

// backtracking solution

bool isPalindrome(const std::string& s, int start, int end) {
  for (int i=start, j=end; i<j; ++i, --j) {
    if (s[i] != s[j]) return false;
  }
  return true;
}

void searchPartitionPalindrome(const std::string& s,
                     std::vector<std::vector<std::string>>& ans,
                     std::vector<std::string>& comb,
                     int start) {
  if (start == s.size()) {
    ans.push_back(comb);
    return;
  }

  for (int i=start; i<s.size(); ++i) {
    if (isPalindrome(s, start, i)) {
      comb.push_back(s.substr(start, i-start+1));
      searchPartitionPalindrome(s, ans, comb, i+1);
      comb.pop_back();
    }
  }
}

std::vector<std::vector<std::string>> partitionPalindrome(std::string s) {
  std::vector<std::vector<std::string>> ans;
  std::vector<std::string> comb;

  searchPartitionPalindrome(s, ans, comb, 0);

  return ans;
}

#endif //LEECODE_131_H
