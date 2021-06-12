"""
55. Jump Game
"""
from typing import List


def canJump(nums: List[int]) -> bool:
    nearest_good_point = len(nums) - 1
    for i in range(len(nums) - 1, -1, -1):
        if i + nums[i] >= nearest_good_point:
            nearest_good_point = i
    return nearest_good_point == 0


if __name__ == "__main__":
    assert canJump([2, 3, 1, 1, 4])
    assert not canJump([2, 2, 1, 0, 4])
