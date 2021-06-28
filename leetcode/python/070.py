"""
70. Climbing Stairs
"""


def climbStairs(n: int) -> int:
    if n == 1:
        return 1
    prev = 1
    ret = 2
    for i in range(2, n):
        tmp = ret
        ret += prev
        prev = tmp
    return ret


if __name__ == "__main__":
    assert climbStairs(1) == 1
    assert climbStairs(2) == 2
    assert climbStairs(6) == 13
