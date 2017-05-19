//
// Created by jun on 5/18/17.
// TODO:: generalize the implementation!
//

#ifndef ALGORITHM_STRING_ARITHMETIC_H
#define ALGORITHM_STRING_ARITHMETIC_H

namespace StringArithmetic
{
  //
  // add two strings arithmetically
  //
  std::string str_add(std::string a, std::string b) {
    // calculate the difference of the length
    int diff = a.size() - b.size();

    // Add a "0" to the longer string on the left
    // Add a number of "0" to make the strings have the same length
    if (diff >= 0)
    {
      a = '0' + a;
      for (int i=0; i<=diff; ++i) { b = '0' + b; }
    }
    else
    {
      b = '0' + b;
      diff = -diff;
      for (int i=0; i<=diff; ++i) { a = '0' + a; }
    }

    std::string result;
    int sum = 0;
    int carry = 0;

    // add chars in the two strings one by one from right to left
    for (int i=a.size()-1; i>=0; --i)
    {
      // Subtract '0' from the encoding to get the numeric value.
      // All chars are represented by a number and '0' is the first of them.
      sum = a[i] - '0' + b[i] - '0' + carry;

      // we do not want a zero in the highest position, which will cause
      // infinite loop
      if (sum == 0 && i == 0) { break; }

      if (sum > 9)
      {
        sum -= 10;
        carry = 1;
      }
      else
      {
        carry = 0;
      }

      // cannot use += here since it will append this_sum to sum
      result = std::to_string(sum) + result;
    }

    return result;
  }

  //
  // subtract two strings arithmetically
  //
  std::string str_sub(std::string a, std::string b) {
    // calculate the difference of the length
    int diff = a.size() - b.size();

    // Add a number of "0" to make the strings have the same length
    if (diff > 0)
    {
      for (int i=0; i<diff; ++i) { b = '0' + b; }
    }

    std::string result;
    int difference = 0;
    int carry = 0;

    // subtract chars in the two strings one by one from right to left
    for (int i=a.size()-1; i>=0; --i)
    {
      // Subtract '0' from the encoding to get the numeric value.
      // All chars are represented by a number and '0' is the first of them.
      difference = (a[i] - '0') - (b[i] - '0') + carry;

      if (difference < 0)
      {
        difference += 10;
        carry = -1;
      }
      else
      {
        carry = 0;
      }

      // cannot use += here since it will append this_sum to sum
      result = std::to_string(difference) + result;
    }

    return result;
  }

  //
  // add a number of "0" to the end of a string
  //
  std::string str_shift(std::string a, int n)
  {
    for (int i=0; i < n; ++i) { a += "0"; }

    return a;
  }

  //
  // Karatsuba multiplication
  //
  std::string karatsuba_mul(std::string a, std::string b)
  {
    std::string result;

    if (a.size() > 1 && b.size() > 1)
    {
      int len_a = a.size()/2;
      int len_b = a.size()/2;

      std::string a1 = a.substr(0, len_a);
      std::string a2 = a.substr(len_a, a.size() - len_a);

      std::string b1 = b.substr(0, len_b);
      std::string b2 = b.substr(len_b, b.size() - len_b);

      std::string a1b1 = karatsuba_mul(a1, b1);
      std::string a2b2 = karatsuba_mul(a2, b2);
      std::string a1b2 = karatsuba_mul(a1, b2);
      std::string b1a2 = karatsuba_mul(b1, a2);

      result = str_add(str_add(str_shift(a1b1, 2*len_a), a2b2), str_shift(str_add(a1b2, b1a2), len_a));
    }
    else
    {
      int int_a;
      int int_b;
      // do the arithmetic multiplication if the lengths of bot strings are 1.
      std::stringstream(a) >> int_a;
      std::stringstream(b) >> int_b;

      std::stringstream ss;
      ss << int_a*int_b;

      result = ss.str();
    }

    return result;
  }
}

#endif //ALGORITHM_STRING_ARITHMETIC_H
