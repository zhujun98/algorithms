#ifndef LEECODE_014_H
#define LEECODE_014_H

#include <vector>
#include <string>
#include <algorithm>


/**
 * 14. Longest Common Prefix
 *
 * Write a function to find the longest common prefix string amongst an
 * array of strings.
 */

// time complexity O(S), where S is the No. of all chars in all strings
// space complexity O(1)
std::string longestCommonPrefix(std::vector<std::string>& strs) {
  if (strs.empty()) return "";

  int min_length = std::min_element(strs.begin(),
                                    strs.end(),
                                    [] (const std::string& a, const std::string& b) {
                                      return a.size() < b.size();
                                    })->size();

  for (int i=0; i<min_length; ++i) {
    for (int j=1; j<strs.size(); ++j)
      if (strs[j][i] != strs[j-1][i]) return strs[0].substr(0, i);
  }

  return strs[0].substr(0, min_length);
}

#endif //LEECODE_014_H
