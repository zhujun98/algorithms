//
// Created by jun on 11/11/17.
//

#ifndef LEECODE_383_H
#define LEECODE_383_H

#include <unordered_map>
#include <string>


/**
 * 383. Ransom Note
 *
 * Given an arbitrary ransom note string and another string containing
 * letters from all the magazines, write a function that will return
 * true if the ransom note can be constructed from the magazines;
 * otherwise, it will return false.
 *
 * Each letter in the magazine string can only be used once in your
 * ransom note.
 *
 * For example:
 * canConstruct("a", "b") -> false
 * canConstruct("aa", "ab") -> false
 * canConstruct("aa", "aab") -> true
 */
bool canConstruct(std::string ransomNote, std::string magazine) {
  std::unordered_map<char, int> hash_node;
  for (auto v : magazine) { ++hash_node[v]; }
  for (auto v : ransomNote) {
    if (--hash_node[v] < 0) { return false; }
  }

  return true;
}

#endif //LEECODE_383_H
