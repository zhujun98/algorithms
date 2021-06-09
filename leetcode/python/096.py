"""
96. Unique Binary Search Trees
"""

def numTrees(n: int) -> int:
    rets = (n + 1) * [0]
    rets[0], rets[1] = 1, 1
    for i in range(2, n + 1):
        for j in range(1, i+1):
            rets[i] += rets[j-1] * rets[i - j]
    return rets[-1]


if __name__ == "__main__":
    assert numTrees(1) == 1
    assert numTrees(3) == 5
