//
// Created by jun on 10/22/17.
//

#ifndef LEECODE_049_H
#define LEECODE_049_H

#include <string>
#include <vector>
#include <unordered_map>


/**
 * 49. Group Anagrams
 *
 * Given an array of strings, group anagrams together.

 * For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Return:

 * [
 *  ["ate", "eat","tea"],
 *  ["nat","tan"],
 *  ["bat"]
 * ]
 */

// time complexity O(NKlogK) for quick sort,
//                 O(N(K + M)) for counting sort, where M is the total
//                             number of different characters
// Note:: counting sort is not guaranteed to be faster than quick sort
//        if the length of the word `K` is small
//
// space complexity O(N*K), which is the size of `ans`
std::string getKey(const std::string& str) {
  std::string key {str};

  std::vector<int> loc(128, 0);

  // std::sort(key.begin(), key.end());

  // count the number of each element
  for (auto c : str) ++loc[static_cast<int>(c)];

  // convert counting to the actual position of the element
  for (auto i=1; i < loc.size(); ++i) loc[i] += loc[i-1];

  for (auto c : str) {
    auto i_str = static_cast<int>(c);
    key[loc[i_str] - 1] = c;
    --loc[i_str];
  }

  return key;
}

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
  std::vector<std::vector<std::string>> ans;
  // value is the index of the corresponding entry in `ans`
  std::unordered_map<std::string, int> hash;

  for (const auto& v : strs) {
    std::string key = getKey(v);

    if (hash.find(key) == hash.end()) {
      hash.insert({key, hash.size()});
      ans.push_back({});
    }

    ans[hash[key]].push_back(v);
  }

  return ans;
}

#endif //LEECODE_049_H
