//
// Created by jun on 9/4/17.
//

#ifndef TSP_TEST_TSP_H
#define TSP_TEST_TSP_H

#include <cassert>
#include "tsp.h"


int testTSP1() {
  std::vector<std::pair<double, double>>
      xy {{0, 0}, {-2, -7}, {4, -7}, {0, -5}};

  double min_dist = 21.8907;
  std::vector<size_t> tsp_path {0, 3, 1, 2, 0};

  auto result = tspNN(xy);

  assert(std::abs(result.first - min_dist) < 1e-4);
  assert(result.second == tsp_path);

  std::cout << "Passed" << std::endl;
}

#endif //TSP_TEST_TSP_H
