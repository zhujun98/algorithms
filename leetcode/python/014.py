"""
14. Longest common prefix
"""
from typing import List


def longestCommonPrefix(strs: List[str]) -> str:
    if not strs:
        return ""

    sorted_strs = sorted(strs)

    ret = ''
    first, last = sorted_strs[0], sorted_strs[-1]
    for i, c in enumerate(first):
        if last[i] == c:
            ret += c
        else:
            break
    return ret


if __name__ == "__main__":
    assert "" == longestCommonPrefix([])
    assert "ab" == longestCommonPrefix([
        "abc", "abdadfa", "abceere", "abaaaaa"
    ])
