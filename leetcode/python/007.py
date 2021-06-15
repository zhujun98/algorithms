"""
7. Reverse Integer
"""


# Caveat: the modulo operator % in Python is different from that in C++
def reverse(x: int) -> int:
    sign = -1 if x < 0 else 1
    x = abs(x)
    rev = 0
    while x != 0:
        rev = rev * 10 + x % 10
        x //= 10
    if rev >= 2 ** 31:
        return 0
    return rev * sign


if __name__ == "__main__":
    assert reverse(1534236469) == 0
    assert reverse(123) == 321
    assert reverse(-123) == -321
