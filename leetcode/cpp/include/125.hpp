//
// Created by jun on 2/15/18.
//

#ifndef LEECODE_125_H
#define LEECODE_125_H

/**
 * 125. Valid Palindrome
 *
 * Given a string, determine if it is a palindrome, considering only
 * alphanumeric characters and ignoring cases.
 *
 * For example,
 *    "A man, a plan, a canal: Panama" is a palindrome.
 *   "race a car" is not a palindrome.
 */
#include <string>

// time complexity O(N), space complexity O(1)
bool isPalindrome(std::string s) {
  for (auto it1=s.begin(), it2=s.end()-1; it1 < it2; ++it1, --it2) {
    while (!isalnum(*it1) && it1 < it2) ++it1;
    while (!isalnum(*it2) && it1 < it2) --it2;
    if (toupper(*it1) != toupper(*it2)) return false;
  }
  return true;
}

#endif //LEECODE_125_H
