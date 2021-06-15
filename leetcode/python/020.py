"""
20. Valid Parentheses
"""
from collections import deque


def isValid(s: str) -> bool:
    stack = deque()
    mapping = {')': '(', ']': '[', '}': '{'}

    for c in s:
        if c not in mapping:
            stack.append(c)
        else:
            try:
                if stack.pop() != mapping[c]:
                    return False
            except IndexError:
                return False
    return not stack


if __name__ == "__main__":
    assert isValid("()")
    assert isValid("()[]{}")
    assert not isValid("(]")
    assert not isValid("([)]")
    assert isValid("{[]}")
