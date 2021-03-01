//
// Created by jun on 10/30/17.
//

#ifndef LEECODE_130_H
#define LEECODE_130_H

#include <vector>


/**
 * 130. Surrounded Regions
 *
 * Given a 2D board containing 'X' and 'O' (the letter O), capture
 * all regions surrounded by 'X'.

 * A region is captured by flipping all 'O's into 'X's in that surrounded
 * region.

 * For example,
 * X X X X
 * X O O X
 * X X O X
 * X O X X

 * After running your function, the board should be:

 * X X X X
 * X X X X
 * X X X X
 * X O X X
 */
void dfsSearch130(std::vector<std::vector<char>>& board, int i, int j) {
  if (board[i][j] == 'X' || board[i][j] == 'S') return;
  board[i][j] = 'S';

  if (i > 1) dfsSearch130(board, i-1, j);
  if (i < board.size() - 1) dfsSearch130(board, i+1, j);
  if (j > 1) dfsSearch130(board, i, j-1);
  if (j < board[0].size() - 1) dfsSearch130(board, i, j+1);
}

// any 'O' connected to a 'O' at the four edges should survive!
void solve(std::vector<std::vector<char>>& board) {
  if (board.empty()) return;

  for (int i=0; i<board.size(); ++i) {
    dfsSearch130(board, i, 0);
    if (board[0].size() > 1) dfsSearch130(board, i, board[0].size() - 1);
  }

  for (int j=1; j<board[0].size()-1; ++j) {
    dfsSearch130(board, 0, j);
    if (board.size() > 1) dfsSearch130(board, board.size() - 1, j);
  }

  for (int i=0; i<board.size(); ++i) {
    for (int j=0; j<board[0].size(); ++j) {
      if (board[i][j] == 'S') board[i][j] = 'O';
      else
        board[i][j] = 'X';
    }
  }
}

#endif //LEECODE_130_H
