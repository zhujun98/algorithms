//
// Created by jun on 12/5/17.
//

#ifndef LEECODE_006_H
#define LEECODE_006_H

#include <string>


/**
 * 6. ZigZag Conversion
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given
 * number of rows like this: (you may want to display this pattern in a
 * fixed font for better legibility)

    P   A   H   N
    A P L S I I G
    Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given
 * a number of rows:

 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 */
// time complexity O(N), space complexity O(N)
std::string convert(std::string s, int numRows) {
  if (numRows == 1) return s; // corner case

  std::string ans;
  int k = 2*numRows - 2; // one column plus the slope
  int m = s.size() / k; // No. substructure with k or less than k numbers
  if (s.size() % k == 0) --m;

  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j <= m; ++j) {
      int idx = j*k + i;
      if (idx < s.size()) ans.push_back(s[idx]);

      // except for first and last numbers in the column in a substructure
      if (i > 0 && i < numRows - 1) {
        idx = j*k + k - i;
        if (idx < s.size()) ans.push_back(s[idx]);
      }
    }
  }

  return ans;
}


#endif //LEECODE_006_H
