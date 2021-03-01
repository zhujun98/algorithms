//
// Created by jun on 10/31/17.
//

#ifndef LEECODE_091_H
#define LEECODE_091_H

#include <string>

/**
 * 91. Decode Ways
 *
 * A message containing letters from A-Z is being encoded to numbers
 * using the following mapping:

 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the total
 * number of ways to decode it.

 * For example,
 * Given encoded message "12", it could be decoded as "AB" (1 2) or
 * "L" (12).

 * The number of ways decoding "12" is 2.
 */

// DP solution
// time complexity O(N), space complexity O(1)
int numDecodings(std::string s) {
  if (s.empty() || s[0] == '0') return 0;

  int fn_2 = 1, fn_1 = 1;
  for (int i=1; i<s.size(); ++i) {
    int tmp = fn_1;

    fn_1 = (s[i] == '0' ? 0 : fn_1);
    if (s[i-1] != '0' && (10*(s[i-1] - '0') + (s[i] - '0') <= 26))
      // if fn_2 + s[i-1] + s[i] is a solution, it must have been
      // included in fn_1 + s[i]
      fn_1 += fn_2;
    if (fn_1 == 0) return 0;

    fn_2 = tmp;
  }

  return fn_1;
}

#endif //LEECODE_091_H
