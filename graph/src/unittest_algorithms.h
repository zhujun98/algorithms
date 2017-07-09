//
// Created by jun on 6/23/17.
//
// Functions:
// - testKarger()
// - testKosaraju()
// - testDijkstra()
//

#ifndef GRAPH_UNITTEST_ALGORITHMS_H
#define GRAPH_UNITTEST_ALGORITHMS_H

#include "graph_adj.h"
#include "graph_utilities.h"
#include "unittest_graph.h"
#include "graph_algorithms.h"
#include <string>


namespace graph_test {
  //
  // test the implementation of Kosaraju's algorithm
  //
  void testKosaraju() {

    std::cout << "\nTesting Kosaraju's algorithm..." << std::endl;
    GraphAdj<int> graph = graph_test::simpleGraph();

    std::vector<std::vector<int>> scc = graph::kosaraju(graph);

    std::vector<std::vector<int>> expected_scc = {{4, 7, 1}, {5, 8, 2}, {6, 9, 3}};

    if ( scc == expected_scc ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printSCC(scc);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printSCC(expected_scc);
    }

  }

  //
  // test the implementation of Karger's algorithm
  //
  void testKarger() {

    std::cout << "\nTesting Karger's algorithm..." << std::endl;

    UdGraphAdj<std::string> graph = graph_test::simpleUdGraph();

    int min_cut = graph::karger(graph, 1000);

    if ( min_cut == 2 ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is " << min_cut << std::endl;
      std::cout << "The correct result is 2" << std::endl;
    }
  }

  //
  // test the implementation of Dijkastra's algorithm
  //
  void testDijkstra() {
    std::cout << "\nTesting Dijkstra's algorithm..." << std::endl;

    GraphAdj<std::string> graph = graph_test::distanceGraph();

    std::string source = "a";
    std::vector<std::pair<double, std::string>> shortest_path = graph::dijkstra(graph, source);
    std::vector<std::pair<double, std::string>> expected_result =
        {{0, "a"}, {1, "a"}, {6, "c"}, {3, "b"}};

    if ( shortest_path == expected_result ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printVector(shortest_path);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printVector(expected_result);
    }
  }

}

#endif //GRAPH_UNITTEST_ALGORITHMS_H
