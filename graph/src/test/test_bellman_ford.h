//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_TEST_BELLMAN_FORD_H_H
#define GRAPH_TEST_BELLMAN_FORD_H_H


#include "unittest_graph.h"
#include "../graph_algorithms/bellman_ford.h"


namespace graph_test {

  void testBellmanFord() {
    std::cout << "\nTesting Bellman-Ford's algorithm..." << std::endl;

    auto graph = graph_test::negativeWeightedGraph();
    typedef int weight_t;

    size_t src = 0;
    std::pair<std::deque<weight_t>, std::deque<size_t>> path = bellmanFord(graph, src);
    std::deque<weight_t> result_cost {path.first.begin(), path.first.end()};
    std::deque<size_t> result_came_from {path.second.begin(), path.second.end()};

    std::deque<weight_t> expected_cost{0, 1, 3, -5, -8, -6};
    std::deque<size_t> expected_came_from{0, 0, 1, 1, 3, 4};

    if (result_cost == expected_cost && result_came_from == expected_came_from) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result_cost);
      graph_utilities::printContainer(result_came_from);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_cost);
      graph_utilities::printContainer(expected_came_from);
    }

    graph.connect(3, 0, 2);
    try
    {
      bellmanFord(graph, src);
      std::cerr << "Failed to detect negative cycle!" << std::endl;
      exit (EXIT_FAILURE);
    }
    catch (const std::exception& ia)
    {
//      std::cout << ia.what() << "\n";
      std::cout << "Passed!" << std::endl;
    }
  }

}


#endif //GRAPH_TEST_BELLMAN_FORD_H_H
