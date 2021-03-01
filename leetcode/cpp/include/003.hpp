//
// Created by jun on 2/23/18.
//

#ifndef LEECODE_003_HPP
#define LEECODE_003_HPP

/**
 * 3. Longest Substring Without Repeating Characters
 *
 * Given a string, find the length of the longest substring without
 * repeating characters.
 *
 * Examples:
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 */
#include <string>
#include <unordered_map>

// sliding window method
// time complexity O(N)
// space complexity O(N)
int lengthOfLongestSubstring(std::string s) {
  int i = 0;
  int j = 0;
  int max_len = 0;
  std::unordered_map<char, int> hash;

  while (j < s.size()) {
    auto search = hash.find(s[j]);
    if (search != hash.end()) {
      if (search->second >= i) i = search->second + 1;
      hash.erase(search);
    }
    hash.insert({s[j], j});
    ++j;
    max_len = std::max(max_len, j - i);
  }

  return max_len;
}


// Still the sliding window method.
// Assume the chars are ASCII.
// time complexity O(N)
// space complexity O(1)
int lengthOfLongestSubstringASCII(std::string s) {
  int i = 0;
  int j = 0;
  int max_len = 0;
  std::vector<int> hash(255, -1);

  while (j < s.size()) {
    int num = static_cast<int>(s[j]);
    if (hash[num] >= i) i = hash[num] + 1;
    hash[num] = j;
    ++j;
    max_len = std::max(max_len, j - i);
  }

  return max_len;
}

#endif //LEECODE_003_HPP
