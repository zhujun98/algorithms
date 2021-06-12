#ifndef LEETCODE_ALGO_CPP_045_HPP
#define LEETCODE_ALGO_CPP_045_HPP

/**
 * Jump Game II
 *
 * Given an array of non-negative integers nums, you are initially positioned
 * at the first index of the array. Each element in the array represents your
 * maximum jump length at that position. Your goal is to reach the last index
 * in the minimum number of jumps.

 * You can assume that you can always reach the last index.
 */

int jump(std::vector<int>& nums) {
  int n_jumps = 0;
  // The farthest position the current jump can reach
  int current_jump_end = 0;
  // The farthest reachable position from the currently virtually
  // visited position
  int farthest_reach = 0;
  for (int i = 0; i < nums.size() - 1; ++i) {
    farthest_reach = std::max(farthest_reach, i + nums[i]);
    if (i == current_jump_end) {
      // When the search for the current jump finishes, we will anyhow
      // make a jump, but we don't know the step size of the jump.
      n_jumps++;
      current_jump_end = farthest_reach;
    }
  }

  return n_jumps;
}

#endif //LEETCODE_ALGO_CPP_045_HPP
