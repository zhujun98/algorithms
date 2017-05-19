//
// Created by jun on 5/19/17.
//

#ifndef ALGORITHM_TEST_STRING_ARITHMETIC_H
#define ALGORITHM_TEST_STRING_ARITHMETIC_H

#include <iostream>
#include "../utilities/string_arithmetic.h"


inline void test_string_arithmetic()
{
  std::string a = "24";
  std::string b = "36";
  std::string result1 = "864";
  if (result1.compare(StringArithmetic::karatsuba_mul(a, b)))
  {
    std::cout << "karatsuba_mul Failed!" << std::endl;
    return;
  }

  std::string c = "8450";
  std::string d = "8470";
  std::string result2 = std::to_string(std::stoi(c) * std::stoi(d));
  if (result2.compare(StringArithmetic::karatsuba_mul(c, d)))
  {
    std::cout << "karatsuba_mul Failed!" << "\n";
    std::cout << "output: " << StringArithmetic::karatsuba_mul(c, d);
    std::cout << " correct answer: " << result2 << std::endl;
    return;
  }

  std::cout << "string arithmetic test: passed!" << std::endl;
}

#endif //ALGORITHM_TEST_STRING_ARITHMETIC_H
