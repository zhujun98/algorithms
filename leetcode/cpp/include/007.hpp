//
// Created by jun on 2/15/18.
//

#ifndef LEECODE_007_H
#define LEECODE_007_H

/**
 * 7. Reverse Integer
 *
 * Reverse digits of an integer.
 * The input is assumed to be a 32-bit signed integer. Your function
 * should return 0 when the reversed integer overflows.
 *
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 *
 */
#include <limits>


int reverse(int x) {
  long long reversed = 0;
  while(x) {
    reversed = reversed*10 + x%10;
    x /= 10;
  }

  return ((reversed > std::numeric_limits<int>::max() ||
           reversed < std::numeric_limits<int>::min()) ? 0 : reversed);
}


#endif //LEECODE_007_H
