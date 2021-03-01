//
// Created by jun on 11/1/17.
//

#ifndef LEECODE_127_H
#define LEECODE_127_H

#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <algorithm>


/**
 * 127. Word Ladder
 *
 * Given two words (beginWord and endWord), and a dictionary's word
 * list, find the length of shortest transformation sequence from
 * beginWord to endWord, such that:

 * Only one letter can be changed at a time.
 * Each transformed word must exist in the word list. Note that
 * beginWord is not a transformed word.
 *
 * For example,

 * Given:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log","cog"]
 * As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
 * return its length 5.

 * Note:
 * Return 0 if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 */

// BFS method
// Time complexity O(Nk)
// Space complexity O(N)
bool isTransformable(const std::string& s1, const std::string& s2)
{
  // if (s1.size() != s2.size()) return false;
  for (int i=0, diff=0; i<s1.size(); ++i)
  {
    if (s1[i] != s2[i]) ++diff;
    if (diff > 1) return false;
  }
  return true;
}


int ladderLength(std::string beginWord,
                 std::string endWord,
                 std::vector<std::string>& wordList)
{
  std::unordered_set<std::string> to_visit(wordList.begin(), wordList.end());
  std::queue<std::string> tracker;

  tracker.push(beginWord);

  int dist = 1;
  while (!tracker.empty())
  {
    int m = tracker.size();
    for (int i=0; i<m; ++i)
    {
      auto word = tracker.front();
      tracker.pop();

      // Since we cannot build a graph, the key point here is to
      // loop all the possible 'next word' (since we can only
      // have lower case letters). The number of loop is 26k, where
      // k is the length of the word. Otherwise, we will need to
      // loop over the whole rest word. If the wordList is a very
      // large dataset, then the implemented algorithm will be
      // much faster than the one which loop over the whole rest word.
      for (int i=0; i<word.size(); ++i) {
        auto letter = word[i];
        for (int j=0; j<26; ++j) {
          word[i] = 'a' + j;
          if (to_visit.erase(word) == 1)
          {
            if (word == endWord) return (dist+1);
            tracker.push(word);
          }
        }
        word[i] = letter;
      }
    }
    ++dist;
  }

  return 0;
}

#endif //LEECODE_127_H
