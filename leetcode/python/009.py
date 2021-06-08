def isPalindrome1(x: int) -> bool:
    if x == 0:
        return True
    if x < 0 or x % 10 == 0:
        return False
    r = 0
    while r < x:
        r = 10 * r + x % 10
        x //= 10
    return r == x or x == r // 10


def isParlindrome2(x: int) -> bool:
    s = str(x)
    return s == s[::-1]


if __name__ == "__main__":
    for func in [isPalindrome1, isParlindrome2]:
        assert func(0)
        assert not func(-1)
        assert func(121)
        assert not func(123)
        assert func(3223)
