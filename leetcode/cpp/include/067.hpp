#ifndef LEECODE_067_H
#define LEECODE_067_H

/**
 * 67. Add Binary
 *
 * Given two binary strings, return their sum (also a binary string).
 *
 * For example,
 * a = "11"
 * b = "1"
 * Return "100".
 */

#include <string>
#include <algorithm>


std::string addBinary(std::string a, std::string b) {
  std::string ans;
  int carry = 0;
  for (int i=a.size()-1, j=b.size()-1; i>=0 || j>=0 || carry; --i, --j) {
    int x = (i >= 0 ? a[i] - '0' : 0);
    int y = (j >= 0 ? b[j] - '0' : 0);
    int sum = x + y + carry;
    carry = sum / 2;
    ans.push_back(static_cast<char>(sum%2 + '0'));
  }
  std::reverse(ans.begin(), ans.end());

  return ans;
}

#endif //LEECODE_067_H
