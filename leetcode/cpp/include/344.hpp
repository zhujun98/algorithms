//
// Created by jun on 2/13/18.
//

#ifndef LEECODE_344_H
#define LEECODE_344_H

#include <string>

/**
 * Write a function that takes a string as input and returns the string reversed.

 * Example:
 * Given s = "hello", return "olleh".
 *
*/

// Time complexity O(N), space complexity O(N)
std::string reverseString(std::string s) {
  for (auto it1=s.begin(), it2=s.end()-1; it1 < it2; ++it1, --it2) std::swap(*it1, *it2);
  return s;
}

#endif //LEECODE_344_H
