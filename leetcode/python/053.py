"""
53. Maximum Subarray
"""
from typing import List


def maxSubArray(nums: List[int]) -> int:
    max_sum = nums[0]
    max_sum_ends_last = max_sum
    for ele in nums[1:]:
        max_sum_ends_last = max(ele, max_sum_ends_last + ele)
        max_sum = max(max_sum_ends_last, max_sum)
    return max_sum


if __name__ == "__main__":
    assert maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]) == 6
    assert maxSubArray([5, 4, -1, 7, 8]) == 23
    assert maxSubArray([1]) == 1
