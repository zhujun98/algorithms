"""
27. Remove Element
"""
from typing import List


def removeElement(nums: List[int], val: int) -> int:
    i = 0
    n = len(nums)
    while i < n:
        if nums[i] == val:
            nums[i] = nums[n - 1]
            n -= 1
        else:
            i += 1
    return i


if __name__ == "__main__":
    assert removeElement([3, 2, 2, 3], 3) == 2
    assert removeElement([], 3) == 0
    assert removeElement([2], 3) == 1
