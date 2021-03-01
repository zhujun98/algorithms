//
// Created by jun on 11/11/17.
//

#ifndef LEECODE_070_H
#define LEECODE_070_H

/**
 * 70. Climbing Stairs
 *
 * You are climbing a stair case. It takes n steps to reach to the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct
 * ways can you climb to the top?
 *
 * Note: Given n will be a positive integer.
 */

// time complexity O(N), space complexity O(1)
inline int climbStairs(int n) {
  int s1 = 1; // distinct ways to reach one steps ahead
  if (n == 1) { return s1; }

  int s2 = 1; // distinct ways to reach two steps ahead
  for (int i = 2; i <= n; ++i) {
    int tmp = s1 + s2;
    s2 = s1;
    s1 = tmp;
  }

  return s1;
}

#endif //LEECODE_070_H
