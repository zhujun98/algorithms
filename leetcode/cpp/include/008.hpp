//
// Created by jun on 4/26/18.
//

#ifndef LEECODE_008_HPP
#define LEECODE_008_HPP

/**
 * 8. String to Integer (atoi)
 *
 * Implement atoi which converts a string to an integer.

  The function first discards as many whitespace characters as necessary
  until the first non-whitespace character is found. Then, starting from
  this character, takes an optional initial plus or minus sign followed
  by as many numerical digits as possible, and interprets them as a
  numerical value.

  The string can contain additional characters after those that form the
  integral number, which are ignored and have no effect on the behavior
  of this function.

  If the first sequence of non-whitespace characters in str is not a
  valid integral number, or if no such sequence exists because either
  str is empty or it contains only whitespace characters, no conversion
  is performed.

  If no valid conversion could be performed, a zero value is returned.

  Note:

  Only the space character ' ' is considered as whitespace character.
  Assume we are dealing with an environment which could only store
  integers within the 32-bit signed integer range: [−2^31,  2^31 − 1].
  If the numerical value is out of the range of representable values,
  INT_MAX (2^31 − 1) or INT_MIN (−2^31) is returned.

  Example 1:

  Input: "42"
  Output: 42

  Example 2:

  Input: "   -42"
  Output: -42
  Explanation: The first non-whitespace character is '-', which is the minus sign.
               Then take as many numerical digits as possible, which gets 42.

  Example 3:

  Input: "4193 with words"
  Output: 4193
  Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

  Example 4:

  Input: "words and 987"
  Output: 0
  Explanation: The first non-whitespace character is 'w', which is not a numerical
               digit or a +/- sign. Therefore no valid conversion could be performed.
  Example 5:

  Input: "-91283472332"
  Output: -2147483648
  Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
               Thefore INT_MIN (−231) is returned.
 *
 */
#include <string>
#include <limits>

// constexpr does not work in leecode website
//
// See discussion:
// https://stackoverflow.com/questions/5605142/stdmax-and-stdmin-not-constexpr
constexpr long long MaxInt = std::numeric_limits<int>::max();
constexpr long long MinInt = std::numeric_limits<int>::min();


int _myAtoi(const std::string& str, bool is_positive)
{
  long long y = 0;
  for (size_t i = 0; i < str.size(); ++i)
  {
    int digit = str[i] - '0';
    if (digit <=9 && digit >=0) y = y*10 + digit;
    else break;

    if (y > MaxInt) break;  // it could also cause long long to overflow
  }

  if (!is_positive) {
    y = -y;
    if (y < MinInt) return MinInt;
  }

  if (is_positive && y >  MaxInt) return MaxInt;
  else return y;
}


int myAtoi(std::string str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ' ') continue;

    int digit = str[i] - '0';
    if (digit <= 9 && digit >=0) return _myAtoi(str.substr(i, str.size()), true);
    if (str[i] == '+') return _myAtoi(str.substr(i+1, str.size()), true);
    if (str[i] == '-') return _myAtoi(str.substr(i+1, str.size()), false);
    return 0;
  }

  return 0;
}


#endif //LEECODE_008_HPP
