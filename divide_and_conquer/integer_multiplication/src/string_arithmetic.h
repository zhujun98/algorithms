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
  // reverse a string
  //
  void reverse(std::string& s) {
    for (int i=0, j=s.size()-1; i<j; ++i, --j) std::swap(s[i], s[j]);
  }

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

    reverse(result);

    return result;
  }

  //
  // subtract two strings arithmetically ( a - b )
  // We assume a >= b
  //
  // Note used here, just for fun:)
  //
  std::string strSub(std::string a, std::string b) {
    std::string result;
    int carry = 0;

    for (int i=a.size()-1, j=b.size()-1; i>=0 || j>=0 || carry<0; --i, --j) {
      if (i < 0 && carry < 0) throw std::invalid_argument("a is less than b!\n");

      int x = (i >= 0 ? a[i] - '0' : 0);
      int y = (j >= 0 ? b[j] - '0': 0);

      int diff = x - y + carry;

      if (diff < 0) {
        diff += 10;
        carry = -1;
      } else {
        carry = 0;
      }

      result.push_back(static_cast<char>(diff + '0'));
    }

    reverse(result);

    return result;
  }

  //
  // check is a string is all 0
  //
  bool isZero(const std::string& a) {
    for (auto c : a) {
      if (c != '0') return false;
    }
    return true;
  }

  //
  // Karatsuba multiplication
  //
  std::string strMul(std::string a, std::string b)
  {
    if (isZero(a) || isZero(b)) return std::to_string(0);

    std::string result;

    if (a.size() == 1 && b.size() == 1) {
      auto num = std::stoi(a) * std::stoi(b);
      return std::to_string(num);
    }

    // add '0' to the tail of both strings until they have equal length
    // and the length is even number
    size_t length = std::max(a.size(), b.size());
    if (length%2 == 1) ++length;

    // we will remove the added '0' in the end
    size_t diff = length - a.size();
    diff += length - b.size();

    while (a.size() < length) a.push_back('0');
    while (b.size() < length) b.push_back('0');

    size_t divide = length/2;

    std::string a1 = a.substr(0, divide);
    std::string a2 = a.substr(divide, length);

    std::string b1 = b.substr(0, divide);
    std::string b2 = b.substr(divide, length);

    std::string a1b1 = strMul(a1, b1);
    std::string a2b2 = strMul(a2, b2);
    std::string a1b2 = strMul(a1, b2);
    std::string b1a2 = strMul(b1, a2);

    for (int i=0; i<length; ++i) a1b1.push_back('0');
    auto tmp1 = strAdd(a1b1, a2b2);
    auto tmp2 = strAdd(a1b2, b1a2);
    for (int i=0; i<divide; ++i) tmp2.push_back('0');
    result = strAdd(tmp1, tmp2);

    // remove place-holder '0' in the tail
    for (size_t i=0; i<diff; ++i) result.pop_back();

    return result;
  }
}

#endif //ALGORITHM_STRING_ARITHMETIC_H
