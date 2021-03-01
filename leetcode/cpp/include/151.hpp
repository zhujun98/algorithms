//
// Created by jun on 11/2/17.
//

#ifndef LEECODE_151_H
#define LEECODE_151_H

#include <string>
#include <algorithm>


/**
 * 151. Reverse Words in a String
 *
 * Given an input string, reverse the string word by word.

  For example,
  Given s = "the sky is blue",
  return "blue is sky the".
 */

// time complexity: depends on the number of space and words
// space complexity: O(1)
void reverseWords(std::string &s) {
  std::reverse(s.begin(), s.end());

  auto it=s.begin();
  while(it != s.end()) {
    auto j = it;
    while (*j == ' ' && j != s.end()) ++j;
    int count = 0;
    while (*j != ' ' && j != s.end()) {
      ++j;
      ++count;
    }
    std::reverse(it, j);
    std::advance(it, count);
    // before this step it should be at the fist space after the last
    // word if not reaching the end of the whole string
    if (it != s.end()) ++it;
  }

  // remove the trailing spaces
  it = s.end();
  for (auto rit = s.rbegin(); rit != s.rend() && *rit == ' '; ++rit, --it) {}
  s.erase(it, s.end());
}

#endif //LEECODE_151_H
