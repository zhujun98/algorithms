//
// Created by jun on 10/24/17.
//

#ifndef LEECODE_056_H
#define LEECODE_056_H

#include <vector>
#include <algorithm>

/**
 * 56. Merge Intervals
 *
 * Given a collection of intervals, merge all overlapping intervals.

 * For example,
 * Given [1,3],[2,6],[8,10],[15,18],
 * return [1,6],[8,10],[15,18].
 */

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

// time complexity O(NlogN) because of the sorting
// space complexity O(N)
std::vector<Interval> merge(std::vector<Interval>& intervals) {
  std::vector<Interval> ans;
  if (intervals.empty()) return ans;

  std::sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b)
  {
    return a.start < b.start;
  });

  ans.push_back(intervals[0]);
  for (const auto &v : intervals) {
    if (v.start <= ans.back().end) {
      ans.back().end = std::max(ans.back().end, v.end);
    } else {
      ans.push_back(v);
    }
  }
  return ans;
}

#endif //LEECODE_056_H
