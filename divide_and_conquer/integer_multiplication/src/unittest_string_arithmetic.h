//
// Created by jun on 5/19/17.
//
// Functions:
// - compareResult()
// - testStrAdd()
// - testStrSub()
// - testStrAddZero()
// - testStringMul()
//

#ifndef ALGORITHM_TEST_STRING_ARITHMETIC_H
#define ALGORITHM_TEST_STRING_ARITHMETIC_H

#include <iostream>
#include "string_arithmetic.h"


//
// compare the output and correct result and print some information
//
inline bool compareResult(std::string output, std::string expected) {
  if ( output.compare(expected) != 0 ) {
    std::cout << "Failed!" << std::endl;
    std::cout << "Correct result is: " << expected << std::endl;
    std::cout << "Output is: " << output << std::endl;

    return false;
  } else {
    return true;
  }
}

//
// string_arithmetic::strAdd()
//
inline void testStrAdd() {

  std::cout << "\nTesting function strAdd()..." << std::endl;

  std::string a = "24";
  std::string b = "36";
  std::string expected = "60";
  std::string output = string_arithmetic::strAdd(a, b);
  if ( not compareResult(output, expected) ) { return; };

  a = "12352";
  b = "289";
  expected = "12641";
  output = string_arithmetic::strAdd(a, b);
  if ( not compareResult(output, expected) ) { return; };

  std::cout << "Passed!" << std::endl;
}


//
// test string_arithmetic::strSub()
//
inline void testStrSub() {

  std::cout << "\nTesting function strSub()..." << std::endl;

  std::string a = "84";
  std::string b = "36";
  std::string expected = "48";
  std::string output = string_arithmetic::strSub(a, b);
  if ( not compareResult(output, expected) ) { return; };


  a = "981";
  b = "99";
  expected = "882";
  output = string_arithmetic::strSub(a, b);
  if ( not compareResult(output, expected) ) { return; };

  std::cout << "Passed!" << std::endl;
}


//
// string_arithmetic::strShift()
//
inline void testStrAddZero() {
  std::cout << "\nTesting function strAddZero()..." << std::endl;

  std::string a = "184";
  std::string expected = "1840000";
  std::string output = string_arithmetic::strAddZero(a, 4);
  if ( not compareResult(output, expected) ) { return; };

  std::cout << "Passed!" << std::endl;
}


//
// string_arithmetic::strMul()
//
inline void testStringMul()
{
  std::cout << "\nTesting function strMul()..." << std::endl;

  std::string a = "24";
  std::string b = "36";
  std::string expected = "864";
  std::string output = string_arithmetic::strMul(a, b);
  if ( not compareResult(output, expected) ) { return; };

  a = "845";
  b = "847";
  expected = "715715";
  output = string_arithmetic::strMul(a, b);
  if ( not compareResult(output, expected) ) { return; };

  a = "0";
  b = "847";
  expected = "0";
  output = string_arithmetic::strMul(a, b);
  if ( not compareResult(output, expected) ) { return; };

  std::cout << "Passed!" << std::endl;
}

#endif //ALGORITHM_TEST_STRING_ARITHMETIC_H
