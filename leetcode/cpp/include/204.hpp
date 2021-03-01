//
// Created by jun on 10/14/17.
//

#ifndef LEECODE_ALGORITHMS_204_H
#define LEECODE_ALGORITHMS_204_H

#include <vector>
#include <cmath>

/**
 * 204. Count Primes
 *
 * Count the number of prime numbers less than a non-negative number, n
 */

// time complexity O(N), space complexity O(1)
inline int countPrimes(int n) {
  if (n < 2) return 0;

  std::vector<bool> marker(n, true);
  int count = 0;
  int upper = sqrt(n);
  for (int i=2; i<n; ++i) {
    if (marker[i]) {
      ++count;
      if (i <= upper) {
        for (int num = i*i; num < n; num += i) marker[num] = false;
      }
    }
  }

  return count;
}

#endif //LEECODE_ALGORITHMS_204_H
