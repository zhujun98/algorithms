//
// Created by jun on 10/1/19.
//

#ifndef LEETCODE_ALGORITHMS_CPP_168_HPP
#define LEETCODE_ALGORITHMS_CPP_168_HPP

/**
 * 168. Excel sheet column title
 *
 * Given a positive integer, return its corresponding column title as appear in an Excel sheet.

 * For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
    ...
 */
 
#include <string>


std::string convertToTitle(int n) {
  std::string ret;
  
  while (n-- > 0) {
    ret = static_cast<char>('A' + n%26) + ret;
    n /= 26;
  }
  
  return ret;
}



#endif //LEETCODE_ALGORITHMS_CPP_168_HPP
