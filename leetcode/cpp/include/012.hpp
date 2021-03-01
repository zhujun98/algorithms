//
// Created by jun on 12/6/17.
//

#ifndef LEECODE_012_H
#define LEECODE_012_H

#include <string>
#include <unordered_map>


/**
 * 12. Integer to Roman
 *
 * Given an integer, convert it to a roman numeral.

 * Input is guaranteed to be within the range from 1 to 3999.
 */
// The difficulty lies on the special cases 4 and 9
// Time complexity O(N), N is the No. digits.
// space complexity "space required to store the output string"
std::string intToRoman(int num) {
  std::unordered_map<int, char> roman {{1, 'I'},
                                       {5, 'V'},
                                       {10, 'X'},
                                       {50, 'L'},
                                       {100, 'C'},
                                       {500, 'D'},
                                       {1000, 'M'}};
  std::string ans;
  int divider = 1000;
  while (divider > 0 && num > 0) {
    int count = num / divider;
    if (count == 9) {
      ans.push_back(roman.at(divider));
      ans.push_back(roman.at(10*divider));
    } else if (count >= 5) {
      ans.push_back(roman.at(5*divider));
      for (int i = 0; i < count - 5; ++i) ans.push_back(roman.at(divider));
    } else if (count == 4) {
      ans.push_back(roman.at(divider));
      ans.push_back(roman.at(5*divider));
    } else {
      for (int i = 0; i < count; ++i) ans.push_back(roman.at(divider));
    }
    num %= divider;
    divider /= 10;
  }

  return ans;
}

#endif //LEECODE_012_H
