//
// Created by jun on 10/28/17.
//

#ifndef LEECODE_079_H
#define LEECODE_079_H

#include <vector>
#include <string>

/**
 * 79. Word Search
 *
 * Given a 2D board and a word, find if the word exists in the grid.

 * The word can be constructed from letters of sequentially adjacent
 * cell, where "adjacent" cells are those horizontally or vertically
 * neighboring. The same letter cell may not be used more than once.

 * For example,
 * Given board =

 * [
 *  ['A','B','C','E'],
 *  ['S','F','C','S'],
 *  ['A','D','E','E']
 * ]
 *
 * word = "ABCCED", -> returns true,
 * word = "SEE", -> returns true,
 * word = "ABCB", -> returns false.
 */

// time complexity worst case O(N^4), space complexity O(1)
bool searchWord(std::vector<std::vector<char>>& board, int i, int j,
                const std::string& word, int k) {
  if (k == word.size()) return true;
  if (i < 0 || i >= board.size() ||
      j < 0 || j >= board[0].size() ||
      board[i][j] != word[k]) return false;

  auto tmp = board[i][j];
  board[i][j] = '#';
  if (searchWord(board, i-1, j, word, k+1) ||
      searchWord(board, i+1, j, word, k+1) ||
      searchWord(board, i, j-1, word, k+1) ||
      searchWord(board, i, j+1, word, k+1)) {
    return true;
  }
  // back-tracking
  board[i][j] = tmp;
  return false;
}

bool existWord(std::vector<std::vector<char>>& board, std::string word) {

  for (int i=0; i<board.size(); ++i) {
    for (int j=0; j<board[0].size(); ++j) {
      if (searchWord(board, i, j, word, 0)) return true;
    }
  }
  return false;
}

#endif //LEECODE_079_H
