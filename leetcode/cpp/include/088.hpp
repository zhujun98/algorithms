//
// Created by jun on 10/18/17.
//

#ifndef LEECODE_088_H
#define LEECODE_088_H

#include <vector>


/**
 * 88. Merge Sorted Array
 *
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into
 * nums1 as one sorted array.

 * Note:
 * You may assume that nums1 has enough space (size that is greater or
 * equal to m + n) to hold additional elements from nums2. The number
 * of elements initialized in nums1 and nums2 are m and n respectively.
 */

// Note: 1. merge in reverse order. The process can be stoppped once
//          reaching the head of the second array.
void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
  while (n > 0) nums1[m + n - 1] = (m == 0 || nums1[m-1] < nums2[n-1]) ? nums2[--n] : nums1[--m];
}

// more verbosely
void merge1(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
  int i = m - 1, j = n - 1;
  while (j >= 0) {
    if (i >=0 && nums1[i] > nums2[j]) {
      nums1[i+j+1] = nums1[i];
      --i;
    } else {
      nums1[i+j+1] = nums2[j];
      --j;
    }
  }
}

#endif //LEECODE_088_H
