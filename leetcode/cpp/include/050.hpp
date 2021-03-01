//
// Created by jun on 2/17/18.
//

#ifndef LEECODE_050_H
#define LEECODE_050_H

/**
 * 50. Pow(x, n)
 *
 * Implement pow(x, n).


 * Example 1:

 * Input: 2.00000, 10
 * Output: 1024.00000
 *
 * Example 2:

 * Input: 2.10000, 3
 * Output: 9.26100
 */

// time complexity O(log(n))
// space complexity O(1)
double myPow(double x, int n) {
  if (n == 0) return 1;
  if (x == 0) return 0;

  long long m = n;  // solve the overflow issue
  if (m < 0) {
    m = -m;
    x = 1/x;
  }

  double ans = 1;
  double product = x;
  for (long long i=m; i>0; i /= 2) {
    if (i%2 == 1) ans *= product;
    if (i == 1) return ans;
    product *= product;
  }
}


// time complexity O(log(n))
// space complexity O(log(n))
double myPowRecursive(double x, int n) {
  if (n == 0) return 1;
  if (x == 0) return 0;

  long long m = n;  // solve the overflow issue
  if (m < 0) {
    m = -m;
    x = 1/x;
  }

  double y = myPowRecursive(x, m/2);

  if (m%2 == 1) return y * y * x;
  return y * y;
}


#endif //LEECODE_050_H
