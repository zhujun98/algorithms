//
// Created by jun on 4/26/18.
//

#ifndef LEECODE_005_HPP
#define LEECODE_005_HPP

/**
 * 5. Longest Palindromic Substring
 *
 * Given a string s, find the longest palindromic substring in s.
 *
 * Examples:
 *
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 *
 * Input: "cbbd"
 * Output: "bb"
 */
#include <string>


using Palindrome = std::pair<size_t, size_t>;

// implementation without worrying about the size_t overflow
//Palindrome _searchLongestPalindrome(const std::string& str, long i, long j)
//{
//  for(;i >= 0 && j < str.size();--i, ++j)
//    if (str[i] != str[j]) break;
//  return std::make_pair(i+1, j-i-1);
//}

Palindrome _searchLongestPalindrome(const std::string& str, size_t i, size_t j)
{
  for(;;--i, ++j)
  {
    if (str[i] != str[j]) return std::make_pair(i+1, j-i-1);
    if (i == 0 || j == str.size() - 1) return std::make_pair(i, j-i+1);
  }
}

// time complexity O(N^2), space complexity O(1)
std::string longestPalindrome(std::string s) {
  Palindrome longest {0, 0};
  for (int i=0; i<s.size(); ++i) {
    Palindrome search = _searchLongestPalindrome(s, i, i);
    if (search.second > longest.second) longest = search;
    search = _searchLongestPalindrome(s, i, i+1);
    if (search.second > longest.second) longest = search;
  }

  return s.substr(longest.first, longest.second);
}

#endif //LEECODE_005_HPP
