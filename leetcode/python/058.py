"""
58. Length of Last Word
"""


def lengthOfLastWord(s: str) -> int:
    i = len(s) - 1
    while i >= 0 and s[i] == ' ':
        i -= 1

    length = 0
    while i >= 0 and s[i] != ' ':
        i -= 1
        length += 1
    return length


def lengthOfLastWord2(s: str) -> int:
    try:
        return len(s.split()[-1])
    except IndexError:
        return 0


if __name__ == "__main__":
    assert lengthOfLastWord("b   a    ") == 1
    assert lengthOfLastWord2("b   a    ") == 1
    assert lengthOfLastWord("last word") == 4
    assert lengthOfLastWord2("last word") == 4
