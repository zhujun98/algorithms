//
// Created by jun on 10/18/17.
//

#ifndef LEECODE_073_H
#define LEECODE_073_H

#include <vector>


/**
 * 73. Set Matrix Zeroes
 *
 * Given a m x n matrix, if an element is 0, set its entire row and
 * column to 0. Do it in place.
 */

// time complexity O(MN), space complexity O(1)
void setZeroes(std::vector<std::vector<int>>& matrix) {
  int col0 = matrix[0][0];
  for (int i=0; i<matrix.size(); ++i) {
    if (matrix[i][0] == 0) col0 = 0;
    for (int j=1; j<matrix[0].size(); ++j) {
      if (matrix[i][j] == 0) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }
    }
  }

  for (int i=matrix.size(); i-- > 0; ) {
    for (int j=matrix[0].size(); j-- > 1; ) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
    }
    if (col0 == 0) matrix[i][0] = 0;
  }
}

#endif //LEECODE_073_H
