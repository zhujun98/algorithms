//
// Created by jun on 2/21/18.
//

#ifndef LEECODE_029_H
#define LEECODE_029_H

/**
 * 29. Divide Two Integers
 *
 * Divide two integers without using multiplication, division and
 * mod operator.
 *
 * If it is overflow, return MAX_INT.
 */
#include <iostream>
#include <limits>


// time complexity O(log(dividend))
// space complexity O(1)?
int divide(int dividend, int divisor) {
  constexpr int kMAX = std::numeric_limits<int>::max();
  constexpr int kMIN = std::numeric_limits<int>::min();

  if (divisor == 0) return kMAX;
  if (dividend == kMIN && divisor == -1) return kMAX;

  int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;

  long long ldividend = labs(dividend);
  long long ldivisor = labs(divisor);

  int ans = 0;
  while (ldividend >= ldivisor) {
    long long x = ldivisor;
    long long y = 1;
    while ((x << 1) <= ldividend) {
      x <<= 1;
      y <<= 1;
    }
    ans += y;
    ldividend -= x;
  }

  return (sign >0 ? ans : -ans);
}


#endif //LEECODE_029_H
