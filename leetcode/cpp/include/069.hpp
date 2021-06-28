#ifndef LEECODE_069_H
#define LEECODE_069_H

/**
 * 69. sqrt(x)
 *
 * Implement int sqrt(int x).
 * Compute and return the square root of x.
 */
int mySqrt(int x) {
  if (x == 0) return 0;
  int left = 1;
  int right = x;

  // when we have right == left or right == left + 1, left must be the
  // correct answer since the equal condition goes to left.
  while (right - left > 1 ) {
    // compare to `mid = (left + right)/2`, the following expression
    // is immune to overflow
    int mid = left + (right - left)/2;
    if (mid <= x/mid) {
      left = mid;
    } else {
      right = mid;
    }
  }

  // return the one including the condition equal
  return left;
}

// Newton's method
// f(r) = r^2 - x, f'(r) = 2r;
// Update: r1 = r0 - f(r0)/f'(r0) = 0.5*(r0 + x/r0)
int mySqrtNewton(int x) {
  long long r = x;
  while (r*r > x)
    r = (r + x/r) / 2; // cannot write as r/2 + x/(2r)
  return r;
}

#endif //LEECODE_069_H
