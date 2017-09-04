#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>

#include "tsp.h"
#include "test_tsp.h"


/**
 * In this assignment we will revisit an old friend, the traveling
 * salesman problem (TSP). This week you will implement a heuristic
 * for the TSP, rather than an exact algorithm, and as a result will
 * be able to handle much larger problem sizes.
 *
 * Here is a data file describing a TSP instance:
 *
 *   nn.txt
 *
 * The first line indicates the number of cities. Each city is a point
 * in the plane, and each subsequent line indicates the x- and
 * y-coordinates of a single city. The distance between two cities is
 * defined as their Euclidean distance.
 *
 * You should implement the nearest neighbor heuristic:
 * 1. Start the tour at the first city.
 * 2. Repeatedly visit the closest city that the tour hasn't visited yet.
 * 3. Once every city has been visited exactly once, return to the first
 *    city to complete the tour.
 *
 * Correct answer: 1203406
 */
void runTspNNAssignment() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the TSP assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/nn.txt", std::ios::in);
  std::string line;
  std::string number;

  std::getline(ifs, line);
  std::istringstream iss0(line);
  iss0 >> number;

  size_t n_cities = std::stoull(number);
  std::vector<std::pair<double, double>> city_coordinates(n_cities);
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);

    iss >> number;
    size_t idx = std::stoull(number) - 1;
    iss >> number;
    double x = std::stod(number);
    iss >> number;
    double y = std::stod(number);

    city_coordinates[idx] = std::make_pair(x, y);
  }

  std::cout << "Read in " << city_coordinates.size() << " data!\n";
  ifs.close();

  auto result = tspNN(city_coordinates);
//  std::cout << std::fixed << std::setprecision(4) << result.first << std::endl;
  assert((long)result.first == 1203406);

  std::cout << "Passed" << std::endl;
}


int main() {
  testTSP1();

  runTspNNAssignment();

  return 0;
}