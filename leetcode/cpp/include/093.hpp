//
// Created by jun on 11/8/17.
//

#ifndef LEECODE_093_H
#define LEECODE_093_H

#include <vector>
#include <string>

/**
 * 93. Restore IP Addresses
 *
 * Given a string containing only digits, restore it by returning
 * all possible valid IP address combinations.

 * For example:
 * Given "25525511135",

 * return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
 */

// Since the length of the string cannot exceed 12,
// time complexity and space complexity are both constant
std::vector<std::string> restoreIpAddresses(std::string s) {
  if (s.size() > 12) return {};
  std::vector<std::string> ans;

  for (int i=0; i<3; ++i) {
    for (int j=i+1; j<i+4 && j<s.size(); ++j) {
      for (int k=j+1; k<j+4 && k<s.size(); ++k) {
        int l = s.size() - 1;
        if (k >= s.size() - 1 || l - k > 3) continue;

        if (std::stoi(s.substr(0, i+1)) > 255 || (i > 0 && s[0] == '0') ||
            std::stoi(s.substr(i+1, j-i)) > 255 || (j - i > 1 && s[i+1] == '0') ||
            std::stoi(s.substr(j+1, k-j)) > 255 || (k - j > 1 && s[j+1] == '0') ||
            std::stoi(s.substr(k+1, l-k)) > 255 || (l - k > 1 && s[k+1] == '0')) continue;

        std::string tmp;
        tmp.append(s.substr(0, i+1));
        tmp.push_back('.');
        tmp.append(s.substr(i+1, j-i));
        tmp.push_back('.');
        tmp.append(s.substr(j+1, k-j));
        tmp.push_back('.');
        tmp.append(s.substr(k+1, s.size()-1-k));

        ans.push_back(tmp);
      }
    }
  }

  return ans;
}


#endif //LEECODE_093_H
