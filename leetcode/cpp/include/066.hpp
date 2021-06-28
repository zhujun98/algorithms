#ifndef LEECODE_066_H
#define LEECODE_066_H

/**
 * 66. Plus One
 *
 * Given a non-negative integer represented as a non-empty array of
 * digits, plus one to the integer.
 *
 * You may assume the integer do not contain any leading zero, except
 * the number 0 itself.
 *
 * The digits are stored such that the most significant digit is at
 * the head of the list (on the left).
 */
#include <vector>

// time complexity O(N), space complexity O(N)
std::vector<int> plusOne(std::vector<int> digits) {
  for (int i=digits.size() - 1; i>=0; --i) {
    if (digits[i] == 9) {
      digits[i] = 0;
    } else {
      digits[i] += 1;
      return digits;
    }
  }
    // if all digits are number 9, the result must be
    // 1 followed by a number of 0.

//    digits.insert(digits.begin(), 1); // inefficient
    digits[0] = 1;
    digits.push_back(0);

    return digits;
}

#endif //LEECODE_066_H
