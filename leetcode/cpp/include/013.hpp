//
// Created by jun on 12/6/17.
//

#ifndef LEECODE_013_H
#define LEECODE_013_H

#include <string>
#include <unordered_map>


/**
 * 13. Roman to Integer
 *
 * Given a roman numeral, convert it to an integer.

 * Input is guaranteed to be within the range from 1 to 3999.
 */

// Time complexity O(N), space complexity O(1)
int romanToInt(std::string s) {
  std::unordered_map<char, int> roman {{'I', 1},
                                       {'V', 5},
                                       {'X', 10},
                                       {'L', 50},
                                       {'C', 100},
                                       {'D', 500},
                                       {'M', 1000}};
  if (s.size() == 0) return 0;
  // use 'at' operator to avoid hash new letters
  int sum = roman.at(s.back());
  for (int i=s.size() - 2; i >= 0; --i) {
    int curr = roman.at(s[i]);
    int prev = roman.at(s[i+1]);
    if (curr < prev) {
      sum -= curr;
    } else {
      sum += curr;
    }
  }

  return sum;
}

#endif //LEECODE_013_H
