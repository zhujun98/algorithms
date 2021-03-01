//
// Created by jun on 9/28/19.
//

#ifndef LEETCODE_ALGORITHMS_CPP_071_CPP_HPP
#define LEETCODE_ALGORITHMS_CPP_071_CPP_HPP

/**
 * 71. Simplify Path
 *
 * Given an absolute path for a file (Unix-style), simplify it.
 * Or in other words, convert it to the canonical path.

 * In a UNIX-style file system, a period . refers to the current directory.
 * Furthermore, a double period .. moves the directory up a level. For more
 * information, see: Absolute path vs relative path in Linux/Unix

 * Note that the returned canonical path must always begin with a slash /,
 * and there must be only a single slash / between two directory names. The
 * last directory name (if it exists) must not end with a trailing /. Also,
 * the canonical path must be the shortest string representing the absolute path.
 */

#include <queue>

// time complexity O(N), space complexity O(N)
std::string simplifyPath(const std::string& path) {
  std::deque<std::string> dirs;
  
  size_t i = 1;
  size_t j = 1;
  for (; j < path.size(); ++j) {
    if (path[j] == '/') {
      if (j != i) {
        std::string sub = path.substr(i, j-i);
        if (sub == "..") {
          if (not dirs.empty()) dirs.pop_back();
        } else if (sub != ".") {
          dirs.push_back(sub);
        } // else (sub == "."), do nothing
      }
      // move i to the right of the previous '/'
      i = j + 1;
    }
  }
  
  // Note the following block can be removed by append a '/' to the input
  // path at the beginning if it is not a const.
  
  // the last char is not '/'
  if (i != j) {
    std::string sub = path.substr(i, j-i);
    if (sub == "..") {
      if (not dirs.empty()) dirs.pop_back();
    } else if (sub != ".") {
      dirs.push_back(sub);
    } // else (sub == "."), do nothing
  }
  
  std::string simplified("/");
  while (not dirs.empty()) {
    simplified.append(dirs.front() + "/");
    dirs.pop_front();
  }

  // remove the last "/" if simplified != "/
  if (simplified.size() > 1) simplified.pop_back();
  
  return simplified;
}

#endif //LEETCODE_ALGORITHMS_CPP_071_CPP_HPP
