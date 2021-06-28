"""
66. Plus One
"""
from typing import List


def plusOne(digits: List[int]) -> List[int]:
    for i in range(len(digits) - 1, -1, -1):
        if digits[i] == 9:
            digits[i] = 0
        else:
            digits[i] += 1
            return digits

    digits[0] = 1
    digits.append(0)
    return digits


if __name__ == "__main__":
    assert plusOne([1, 2, 3]) == [1, 2, 4]
    assert plusOne([9, 9]) == [1, 0, 0]
    assert plusOne([0]) == [1]
