//
// Created by jun on 6/23/17.
//

#ifndef HASH_TABLE_ASSIGNMENTS_H
#define HASH_TABLE_ASSIGNMENTS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <time.h>


namespace assignment {

  //
  // The goal of this problem is to implement a variant of the 2-SUM algorithm
  // covered in this week's lectures.
  // The file contains 1 million integers, both positive and negative (there
  // might be some repetitions!).This is your array of integers, with the ith
  // row of the file specifying the ith entry of the array.
  //
  // Your task is to compute the number of target values t in the interval
  // [-10000,10000] (inclusive) such that there are distinct numbers x,y in
  // the input file that satisfy x+y=t.
  //
  // OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing
  // your own hash table for it. For example, you could compare performance
  // under the chaining and open addressing approaches to resolving collisions.
  //
  // The running time on my i7-7500U is about 32 minutes:(
  //
  void run2SumAssignment() {
    std::cout << "\n" << std::string(80, '-') << "\n"
              << "This is the 2-Sum assignment in the Stanford's Algorithm course at Coursera"
              << "\n" << std::string(80, '-') << "\n"
              << std::endl;

    std::vector<long> numbers;

    std::ifstream ifs("../data/2sum.txt", std::fstream::in);
    long number;
    while ( ifs >> number ) {
      numbers.push_back(number);
    }
    ifs.close();
    // there are only hundreds of duplicated numbers, so it is not necessary
    // to remove the duplicate.
    std::cout << "Read in " << numbers.size() << " numbers from file!" << std::endl;

    std::sort(numbers.begin(), numbers.end());  // a sorted array can double the speed
    std::unordered_map<long, bool> hash;
    hash.max_load_factor(0.05);  // critical setup to speed up!!!
    for ( int i=0; i < numbers.size(); ++i ) {
      // avoid collisions in the hash table
      if ( hash.find(numbers[i]) == hash.end() ) {
        hash.insert({numbers[i], true});
      }
    }

    clock_t t0 = clock();
    int min_sum = -10000;
    int max_sum = 10000;
    int count = 0;
    for ( long sum=min_sum; sum<=max_sum; ++sum) {
      if ( sum % 10 == 0 ) { std::cout << sum << std::endl; }
      for ( int i=0; i < numbers.size(); ++i) {
        // x + y = t, where x != y
        if ( numbers[i] != sum - numbers[i] && hash.find(sum - numbers[i]) != hash.end() ) {
          ++count;
          break;
        } else if ( numbers[i] > sum/2 ) {
          // The look-up can be stopped since there is no match for the number
          // which are less than or equal to sum/2. The sum of two numbers which
          // are both larger than sum/2 must be greater than sum.
          break;
        }
      }
    }

    std::cout << "The answer is " << count << std::endl;
    std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;
  }

}

#endif //HASH_TABLE_ASSIGNMENTS_H
