//
// Created by jun on 9/1/17.
//

#ifndef GRAPH_ASSIGNMENT_ALL_PAIR_SHORTEST_PATH_H
#define GRAPH_ASSIGNMENT_ALL_PAIR_SHORTEST_PATH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../graph_algorithms/floyd_warshall.h"
#include "../graph_algorithms/johnson.h"


/**
 * In this assignment you will implement one or more algorithms for the
 * all-pairs shortest-path problem. Here are data files describing three
 * graphs:
 *
 *   g1.txt (NULL)
 *   g2.txt (NULL)
 *   g3.txt (-19)
 *
 * The first line indicates the number of vertices and edges, respectively.
 * Each subsequent line describes an edge (the first two numbers are its
 * tail and head, respectively) and its length (the third number). NOTE:
 * some of the edge lengths are negative. NOTE: These graphs may or may
 * not have negative-cost cycles.
 *
 * Your task is to compute the "shortest shortest path". Precisely, you
 * must first identify which, if any, of the three graphs have no negative
 * cycles. For each such graph, you should compute all-pairs shortest
 * paths and remember the smallest one.
 *
 * OPTIONAL: Here is a bigger data set to play with.
 *
 *   large.txt
 */
void runAllPairShortestPathAssignment() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the all-pair-shortest-path assignment in the "
            << "Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/APSP_g3.txt", std::ifstream::in);
  std::string line;
  std::string number;

  // read the first line
  std::getline(ifs, line);
  std::istringstream iss0(line);

  iss0 >> number;
  size_t vertices = std::stoull(number);
  DirectedGraph<long> graph(vertices);
  iss0 >> number;
  size_t edges = std::stoull(number);
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);

    iss >> number;
    size_t src = std::stoull(number) - 1;
    iss >> number;
    size_t dst = std::stoull(number) - 1;
    iss >> number;
    long weight = std::stol(number);

    graph.connect(src, dst, weight);
  }

  ifs.close();
  std::cout << "Finished reading data! \n";
  std::cout << "The graph has " << vertices << " vertices and "
            << edges << " edges." << std::endl;

  clock_t t0;

  // Floyd-Warshall's algorithm takes more than 10 minutes
//  std::cout << "Using Floyd-Warshall's algorithm: \n";
//  t0 = clock();
//  auto result_fw = floydWarshall(graph);
//  long min_length_fw = 100000;
//  for (const auto& v : result_fw.first) {
//    for (const auto&vv : v) {
//      if (vv < min_length_fw) { min_length_fw = vv; }
//    }
//  }
//  std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
//            << " ms" << std::endl;
//  assert(min_length_fw == -19);
//  std::cout << "Passed" << std::endl;

  std::cout << "Using Johnson's algorithm: \n";
  t0 = clock();
  auto result_js = johnson(graph);
  long min_length_js = 100000;
  for (const auto& v : result_js.first) {
    for (const auto&vv : v) {
      if (vv < min_length_js) { min_length_js = vv; }
    }
  }
  std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
            << " ms" << std::endl;
  assert(min_length_js == -19);
  std::cout << "Passed" << std::endl;
}


#endif //GRAPH_ASSIGNMENT_ALL_PAIR_SHORTEST_PATH_H