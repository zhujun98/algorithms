//
// Created by jun on 9/4/17.
//

#ifndef TSP_TEST_TSP_H
#define TSP_TEST_TSP_H

#include <cassert>
#include "tsp.h"


int testTSPBruteForce() {
  //
  // [ 0.00 7.28 8.77 5.00
  //   7.28 0.00 6.00 2.83
  //   8.77 6.00 0.00 4.47
  //   5.00 2.83 4.47 0.00 ]
  //
  std::vector<std::pair<double, double>>
      xy {{0, 0}, {-2, -7}, {4, -7}, {0, -5}};

  double min_dist = 21.8907;
  std::vector<size_t> tsp_path {0, 2, 1, 3, 0};

  auto result = tspBruteForce(xy);

  assert(std::abs(result.first - min_dist) < 1e-4);
  assert(result.second == tsp_path);

  std::cout << "Passed" << std::endl;
}


int testTSPDP() {
  std::vector<std::pair<double, double>>
      xy {{0, 0}, {-2, -7}, {4, -7}, {0, -5}};

  double min_dist = 21.8907;
  std::vector<unsigned int> tsp_path {0, 2, 1, 3, 0};

  auto result = tspDP(xy);

  assert(std::abs(result.first - min_dist) < 1e-4);
  assert(result.second == tsp_path);

  std::cout << "Passed" << std::endl;
}


int testTSPNN() {
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
