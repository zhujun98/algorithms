//
// Created by jun on 10/22/17.
//

#ifndef LEECODE_036_H
#define LEECODE_036_H

#include <vector>

/**
 * 36. Valid Sudoku
 *
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles -
 * The Rules.

 * The Sudoku board could be partially filled, where empty cells are
 * filled with the character '.'.
 */

// time complexity O(N^2), space complexity O(N)
bool isValidSudoku(std::vector<std::vector<char>>& board) {
  for (int i = 0; i < 9; ++i) {
    std::vector<bool> used_row(9, false);
    std::vector<bool> used_col(9, false);
    std::vector<bool> used_box(9, false);

    for (int j = 0; j < 9; ++j) {
      int num = board[i][j] - '0' - 1;
      if (board[i][j] != '.') {
        if (used_row[num]) return false;
        used_row[num] = true;
      }

      num = board[j][i] - '0' - 1;
      if (board[j][i] != '.') {
        if (used_col[num]) return false;
        used_col[num] = true;
      }

      // Key part!
      int m = 3*(i/3) + j/3;
      int n = 3*(i%3) + j%3;
      num = board[m][n] - '0' - 1;
      if (board[m][n] != '.') {
        if (used_box[num]) return false;
        used_box[num] = true;
      }
    }

    std::fill(used_row.begin(), used_row.end(), false);
    std::fill(used_col.begin(), used_col.end(), false);
    std::fill(used_box.begin(), used_box.end(), false);
  }

  return true;
}

#endif //LEECODE_036_H
