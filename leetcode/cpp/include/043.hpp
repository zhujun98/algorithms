//
// Created by jun on 11/9/17.
//

#ifndef LEECODE_043_H
#define LEECODE_043_H

#include <string>

/**
 * 43. Multiply Strings
 *
 * Given two non-negative integers num1 and num2 represented as strings,
 * return the product of num1 and num2.

 * Note:

 * 1. The length of both num1 and num2 is < 110.
 * 2. Both num1 and num2 contains only digits 0-9.
 * 3. Both num1 and num2 does not contain any leading zero.
 */

// Time complexity O(MN), where M and N are lengths of the two numbers
// respectively.
// Space complexity O(1).
std::string multiply(std::string num1, std::string num2) {
  if (num1 == "0" || num2 == "0") return "0";

  std::string product(num1.size() + num2.size(), '0');
  for (int i = num1.size() - 1; i >= 0; --i) {
    int carry = 0;
    for (int j = num2.size() - 1; j >= 0; --j) {
      int tmp = product[i+j+1] - '0' + (num1[i] - '0') * (num2[j] - '0') + carry;
      carry = tmp / 10;
      product[i+j+1] = tmp % 10 + '0';
    }
    // Do not forget to add the carry to the highest position
    product[i] += carry;
  }

  for (int i=0; i<product.size(); ++i) {
    if (product[i] != '0') return product.substr(i, product.size() - i);
  }
}

#endif //LEECODE_043_H
