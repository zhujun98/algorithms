//
// Created by jun on 5/18/17.
//
// Functions:
// - strAdd()
// - strSub()
// - strAddZero()
// - strMul()
//

#ifndef ALGORITHM_STRING_ARITHMETIC_H
#define ALGORITHM_STRING_ARITHMETIC_H

namespace string_arithmetic
{
  //
  // add two strings arithmetically
  //
  std::string strAdd(std::string a, std::string b)
  {
    std::string result;
    int carry = 0;
    // add chars in the two strings one by one from right to left
    for (int i=a.size()-1, j=b.size()-1; i>=0 || j>=0 || carry>0; --i, --j)
    {
      int x = (i >= 0 ? a[i] - '0' : 0);
      int y = (j >= 0 ? b[j] - '0' : 0);
      int sum = x + y + carry;

      if (sum > 9)
      {
        sum -= 10;
        carry = 1;
      }
      else
      {
        carry = 0;
      }

      result.push_back(static_cast<char>(sum + '0'));
    }
    // reverse string
    for (int i=0, j=result.size()-1; i<j; ++i, --j) std::swap(result[i], result[j]);

    return result;
  }

  //
  // subtract two strings arithmetically ( a - b )
  // We assume a >= b
  //
  std::string strSub(std::string a, std::string b) {
    // calculate the difference of the length
    long diff = a.size() - b.size();

    // Add a number of "0" to make the strings have the same length
    if ( diff > 0 ) {
      for (std::size_t i=0; i<diff; ++i) { b = '0' + b; }
    } else if ( diff < 0 ) {
      throw std::invalid_argument("a is smaller than b!");
    }

    std::string result;
    int difference = 0;
    int carry = 0;

    // subtract chars in the two strings one by one from right to left
    for (long i = a.size() - 1; i >= 0; --i) {
      // Subtract '0' from the encoding to get the numeric value.
      // All chars are represented by a number and '0' is the first of them.
      difference = (a[i] - '0') - (b[i] - '0') + carry;

      if (difference < 0) {
        difference += 10;
        carry = -1;
      } else {
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
  std::string strAddZero(std::string a, long n) {
    for (int i=0; i < n; ++i) { a += "0"; }

    return a;
  }

  //
  // Karatsuba multiplication
  //
  std::string strMul(std::string a, std::string b)
  {
    std::string result;

    // do the arithmetic multiplication if the lengths of bot strings are 1.
    if ( a.size() == 1 && b.size() == 1 ) {
      long int_a;
      long int_b;

      std::stringstream(a) >> int_a;
      std::stringstream(b) >> int_b;

      std::stringstream ss;
      ss << int_a*int_b;

      return ss.str();
    }

    // calculate the difference of the length
    long diff = a.size() - b.size();

    // Add '0' to the left of the shorter string to make both the strings have
    // the same length
    if (diff > 0) {
      for (std::size_t i=0; i<diff; ++i) { b = '0' + b; }
    } else if ( diff < 0 ) {
      diff = - diff;
      for (std::size_t i=0; i<diff; ++i) { a = '0' + a; }
    }

    unsigned long size = a.size();
    // make the size of the string an even number
    if ( size % 2 == 1) {
      a = '0' + a;
      b = '0' + b;
      size += 1;
    }

    unsigned long divide = size/2;

    std::string a1 = a.substr(0, divide);
    std::string a2 = a.substr(divide, size);

    std::string b1 = b.substr(0, divide);
    std::string b2 = b.substr(divide, size);

    std::string a1b1 = strMul(a1, b1);
    std::string a2b2 = strMul(a2, b2);
    std::string a1b2 = strMul(a1, b2);
    std::string b1a2 = strMul(b1, a2);

    result = strAdd(strAdd(strAddZero(a1b1, size), a2b2),
                    strAddZero(strAdd(a1b2, b1a2), divide));

    // remove all the '0's on the left side
    while ( result[0] == '0' && result.size() > 1 ) { result.erase(0, 1); }

    return result;
  }
}

#endif //ALGORITHM_STRING_ARITHMETIC_H
