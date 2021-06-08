from typing import List


def twoSum(nums: List[int], target: int) -> List[int]:
    m = dict()
    for i, a in enumerate(nums):
        b = target - a
        if b in m:
            return [m[b], i]
        m[a] = i
    return []


if __name__ == "__main__":
    assert twoSum([3, 3], 6) == [0, 1]
    assert twoSum([2, 7, 11, 15], 9) == [0, 1]
