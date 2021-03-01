//
// Created by jun on 11/10/17.
//

#ifndef LEECODE_028_H
#define LEECODE_028_H

#include <string>

/**
 * 28. Implement strStr()
 *
 * Returns the index of the first occurrence of needle in haystack,
 * or -1 if needle is not part of haystack.
 */

// brute force (sliding window): time complexity O([M - N]*N)
int strStr(std::string haystack, std::string needle) {
  if (needle.empty()) { return 0; }
  if (haystack.size() < needle.size()) { return -1; }

  for (int i=0; i < haystack.size() - needle.size() + 1; ++i) {
    int j = 0;
    for (; j < needle.size(); ++j) {
      if (haystack[i+j] != needle[j]) break;
    }
    if (j == needle.size()) return i;
  }
  return -1;
}

#endif //LEECODE_028_H
