"""
45. Jump Game II
"""
from typing import List


def jump(nums: List[int]) -> int:
    n_jumps = 0
    # The farthest position the current jump can reach
    current_jump_end = 0
    # The farthest reachable position from the currently virtually
    # visited position
    farthest_reach = 0
    for i in range(len(nums) - 1):
        farthest_reach = max(farthest_reach, i + nums[i])
        if i == current_jump_end:
            # When the search for the current jump finishes, we will anyhow
            # make a jump, but we don't know the step size of the jump.
            n_jumps += 1
            current_jump_end = farthest_reach
    return n_jumps


if __name__ == "__main__":
    assert jump([2, 3, 1, 1, 4]) == 2
    assert jump([2, 3, 0, 1, 4]) == 2
