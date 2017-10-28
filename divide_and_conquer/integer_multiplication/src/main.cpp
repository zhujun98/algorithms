//
// Created by jun on 5/18/17.
//
#include <iostream>
#include <sstream>
#include "string_arithmetic.h"
#include "unittest_string_arithmetic.h"

int main()
{
  testStrAdd();
  testStrSub();
  testStringMul();

  //
  // Assignment: Karatsuba multiplication
  //
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the Karatsuba multiplication assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-') << "\n"
            << std::endl;

  std::string a = "3141592653589793238462643383279502884197169399375105820974944592";
  std::string b = "2718281828459045235360287471352662497757247093699959574966967627";
  std::string answer = "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184";
  std::string output = string_arithmetic::strMul(a, b);

  if ( output.compare(answer) == 0 ) {
    std::cout << "Passed!" << std::endl;
  } else {
    std::cout << "Failed!" << std::endl;
  }

}

