#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>

#include "tsp.h"
#include "test_tsp.h"


/**
 * In this assignment, you will implement the dynamic programming
 * algorithm for the traveling salesman problem. Here is a data
 * file describing a TSP instance.
 *
 *   TSP.txt
 *
 * The first line indicates the number of cities. Each city is a point
 * in the plane, and each subsequent line indicates the x- and
 * y-coordinates of a single city. The distance between two cities is
 * defined as their Euclidean distance.
 *
 * Correct answer: 26642
 */
void runTspAssignment() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the TSP assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/TSP.txt", std::ios::in);
  std::string line;
  std::string number;

  std::getline(ifs, line);
  std::istringstream iss0(line);
  iss0 >> number;

  size_t n_cities = std::stoull(number);
  std::vector<std::pair<double, double>> city_coordinates;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);

    iss >> number;
    double x = std::stod(number);
    iss >> number;
    double y = std::stod(number);

    city_coordinates.emplace_back(std::make_pair(x, y));
  }

  std::cout << "Read in " << city_coordinates.size() << " data!\n";
  ifs.close();

  std::cout << "Using DP implementation: \n";
  clock_t t0 = clock();
  auto result = tspDP(city_coordinates);
  std::cout << "Time consumption: "
            << 1000.0 * (clock() - t0) / CLOCKS_PER_SEC << " ms" << std::endl;
  std::cout << std::fixed << std::setprecision(4) << result << std::endl;
//  assert((long)result.first == 1203406);

//  std::cout << "Passed" << std::endl;
}


/**
 * In this assignment we will revisit an old friend, the traveling
 * salesman problem (TSP). This week you will implement a heuristic
 * for the TSP, rather than an exact algorithm, and as a result will
 * be able to handle much larger problem sizes.
 *
 * Here is a data file describing a TSP instance:
 *
 *   TSP_nn.txt
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
            << "This is the TSP NN assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/TSP_nn.txt", std::ios::in);
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
  testTSPBruteForce();
  testTSPDP();
  testTSPNN();

  runTspAssignment();

//  runTspNNAssignment();

  return 0;
}