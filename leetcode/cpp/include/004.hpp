//
// Created by jun on 11/19/17.
//

#ifndef LEECODE_004_H
#define LEECODE_004_H

#include <vector>

/**
 * 4. Median of Two Sorted Arrays
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.

 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

 * Example 1:
 * nums1 = [1, 3]
 * nums2 = [2]

 * The median is 2.0
 * Example 2:
 * nums1 = [1, 2]
 * nums2 = [3, 4]

 * The median is (2 + 3)/2 = 2.5
 */

// time complexity O(log(min(m, n))), space complexity O(1)
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
  int m = nums1.size();
  int n = nums2.size();
  if (m == 0 && n == 0) return 0.0;
  if (m > n) return findMedianSortedArrays(nums2, nums1);
  // binary search on the smaller array
  int left = 0;
  int right = m;  // to data_structures the edge case when only one of the array is empty
  while (left <= right) {
    // We make sure that the No. of elements in the left partition of the two arrays
    // is equal or one more than that in the right partition of the two arrays,
    // i.e. i + j >= (m + n)/2
    int i = (left + right + 1) / 2; // No. of numbers in the left partition of nums1
    int j = (m + n + 1) / 2 - i; // No. of numbers in the left partition of nums2

    if (i > 0 && nums1[i-1] > nums2[j]) {
      right = i - 1;
      // if i == 0, j must be at least 1
    } else if (i < right && nums2[j-1] > nums1[i]) {
      left = i + 1;
    } else {
      // Found the correct partition
      int left_max = 0;
      if (i == 0) left_max = nums2[j - 1];
      else if (j == 0) left_max = nums1[i - 1];
      else left_max = std::max(nums1[i-1], nums2[j-1]);

      if ((m + n) % 2 == 1) return left_max;

      int right_min = 0;
      if (i == m) right_min = nums2[j];
      else if (j == n) right_min = nums1[i];
      else right_min = std::min(nums1[i], nums2[j]);

      return (left_max + right_min) / 2.0;
    }
  }
}

#endif //LEECODE_004_H
