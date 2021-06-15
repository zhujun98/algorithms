#ifndef LEECODE_048_H
#define LEECODE_048_H


/**
 * 48. Rotate Image
 *
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise) in-place.
 *
 * Given input matrix =
 * [
 *   [ 5, 1, 9,11],
 *   [ 2, 4, 8,10],
 *   [13, 3, 6, 7],
 *   [15,14,12,16]
 * ],
 *
 * rotate the input matrix in-place such that it becomes:
 * [
 *   [15,13, 2, 5],
 *   [14, 3, 4, 1],
 *   [12, 6, 8, 9],
 *   [16, 7,10,11]
 * ]
 *
 */
#include <vector>


// time complexity O(n^2)
// space complexity O(1)
// It is suggested to write down the index of a 4x4 array to test the
// index during implementation.
void rotate(std::vector<std::vector<int>>& matrix) {
  int n = matrix.size();
  // from the outer circumference to the inner one.
  for (int i=0; i<n/2; ++i) {
    for (int j=i; j<n-i-1; ++j) {
      int tmp = matrix[i][j];
      matrix[i][j] = matrix[n-j-1][i];
      matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
      matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
      matrix[j][n-i-1] = tmp;
    }
  }
}


#endif //LEECODE_048_H
