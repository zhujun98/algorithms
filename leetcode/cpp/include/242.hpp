//
// Created by jun on 10/22/17.
//

#ifndef LEECODE_242_H
#define LEECODE_242_H

#include <vector>
#include <string>
#include <algorithm>


/**
 * 242. Valid Anagram
 *
 * Given two strings s and t, write a function to determine if t is an
 * anagram of s.
 *
 * For example,
 * s = "anagram", t = "nagaram", return true.
 * s = "rat", t = "car", return false.
 *
 * @param s: string 1
 * @param t: string 2
 * @return:
 */

// time complexity O(NlogN), space complexity O(1)
bool isAnagramSort(std::string s, std::string t)
{
  if (s.size() != t.size()) { return false; }

  std::sort(s.begin(), s.end());
  std::sort(t.begin(), t.end());

  return (s == t);
}

// time complexity O(N), space complexity O(N)
bool isAnagram(const std::string& s, const std::string& t)
{
  if (s.size() != t.size()) { return false; }

  // The ASCII table has 128 characters, with values from 0 through 127.
  std::vector<int> count (256, 0);
  for (auto it1 = s.begin(), it2 = t.begin(); it1 != s.end(); ++it1, ++it2)
  {
    ++count[static_cast<int>(*it1)];
    --count[static_cast<int>(*it2)];
  }

  for (auto v : count)
  {
    if ( v!= 0) { return false; }
  }
  return true;
}

#endif //LEECODE_242_H