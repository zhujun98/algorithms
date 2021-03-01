//
// Created by jun on 12/21/17.
//

#ifndef LEECODE_121_H
#define LEECODE_121_H

#include <vector>

/**
 * 121. Best Time to Buy and Sell Stock
 *
 * Say you have an array for which the ith element is the price of a
 * given stock on day i.

 * If you were only permitted to complete at most one transaction (ie,
 * buy one and sell one share of the stock), design an algorithm to
 * find the maximum profit.

 * Example 1:
 * Input: [7, 1, 5, 3, 6, 4]
 * Output: 5

 * Example 2:
 * Input: [7, 6, 4, 3, 1]
 * Output: 0

 */

int maxProfit(std::vector<int>& prices) {
  if (prices.size() < 2) return 0;

  int max_profit = 0;
  int buy_price = prices[0];
  for (int i=1; i<prices.size(); ++i) {
    int profit = prices[i] - buy_price;
    if (profit < 0) buy_price = prices[i];
    else if (profit > max_profit) max_profit = profit;
  }

  return max_profit;
}

#endif //LEECODE_121_H
