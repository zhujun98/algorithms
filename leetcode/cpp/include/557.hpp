//
// Created by jun on 11/2/17.
//

#ifndef LEECODE_557_H
#define LEECODE_557_H

#include <string>


/**
 * 557. Reverse Words in a String III
 *
 * Given a string, you need to reverse the order of characters in each
 * word within a sentence while still preserving whitespace and initial
 * word order.

 * Example 1:
 * Input: "Let's take LeetCode contest"
 * Output: "s'teL ekat edoCteeL tsetnoc"
 * Note: In the string, each word is separated by single space and there
 * will not be any extra space in the string.
 */

// time complexity O(N), space complexity O(1)
std::string reverseWordsIII(std::string s) {
  for (auto it1 = s.begin(); ; ++it1) {
    auto it2 = it1;
    while (*it2 != ' ' && it2 != s.end()) ++it2;
    std::reverse(it1, it2);
    it1 = it2;
    // Must use this line here. Since "for" loop execute "++it1"
    // at the end of a loop, which will make it1 become s.end()+1!!!
    if (it2 == s.end()) break;
  }

  return s;
}

#endif //LEECODE_557_H
