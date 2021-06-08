#ifndef LEECODE_009_H
#define LEECODE_009_H

/**
 * 9. Palindrome Number
 *
 * Determine whether an integer is a palindrome. Do this without extra
 * space?
 *
 * If you are thinking of converting the integer to string, note the
 * restriction of using extra space.
 *
 * You could also try reversing an integer. However, if you have solved
 * the problem "Reverse Integer", you know that the reversed integer
 * might overflow. How would you handle such case?
 */

// time complexity O(log10(N))
// space complexity O(1)
bool isPalindrome(int x) {
  if (x == 0) return true;
  if (x < 0 || x % 10 == 0) return false;

  int reversed = 0;
  while (reversed < x) {
    reversed = 10 * reversed + x % 10;
    x /= 10;
  }

  return (x == reversed || x == reversed / 10);
}

#endif //LEECODE_009_H
