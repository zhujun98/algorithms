#ifndef LEECODE_058_H
#define LEECODE_058_H

/**
 * 58. Length of Last Word
 *
 * Given a string s consists of upper/lower-case alphabets and empty
 * space characters ' ', return the length of last word in the string.

 * If the last word does not exist, return 0.

 * Note: A word is defined as a character sequence consists of
 * non-space characters only.

 * Example:

 * Input: "Hello World"
 * Output: 5
 *
 */
#include <string>


// time complexity O(N), space complexity O(1)
int lengthOfLastWord(std::string s) {
  // skip the trailing spaces
  auto it1 = s.rbegin();
  for(; it1 != s.rend(); ++it1)
    if (*it1 != ' ') break;

  // count the length of the last words.
  int count = 0;
  for (auto it2 = it1; it2 != s.rend(); ++it2, ++count)
    if (*it2 == ' ') break;

  return count;
}

#endif //LEECODE_058_H
