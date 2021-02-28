//
// Created by jun on 8/27/17.
//

#ifndef GRAPH_TEST_DIJKSTRA_H
#define GRAPH_TEST_DIJKSTRA_H

#include <iostream>
#include <algorithm>

#include "unittest_graph.h"
#include "../graph_algorithms/dijkstra.h"


namespace graph_test {

  void testDijkstraDirectedGraph() {
    auto graph = graph_test::distanceGraph();
    size_t src = 0;
    auto path = dijkstra(graph, src);

    std::deque<unsigned int> expected_cost{0, 1, 3, 6, 5, 7};
    std::deque<size_t> expected_came_from{0, 0, 1, 2, 2, 4};

    std::deque<unsigned int> result_cost {path.first.begin(), path.first.end() - 1};
    std::deque<size_t> result_came_from {path.second.begin(), path.second.end() - 1};
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
  }

  void testDijkstraDirectedGraphWithDestination() {
    auto graph = graph_test::distanceGraph();
    size_t src = 0;
    size_t dst = 5;

    auto path = dijkstra(graph, src, dst);
    auto cost = path.first[dst];
    auto sequence_path = reconstructPath(path.second, src, dst);

    std::deque<size_t> expected_sequence_path{0, 1, 2, 4, 5};
    unsigned int expected_cost = 7;

    if (sequence_path == expected_sequence_path && cost == expected_cost) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      std::cout << cost << std::endl;
      graph_utilities::printContainer(sequence_path);
      std::cout << "The correct result is: " << std::endl;
      std::cout << expected_cost << std::endl;
      graph_utilities::printContainer(expected_sequence_path);
    }
  }

  void testDijkstraUnDirectedGraph() {
    auto graph = graph_test::distanceUdGraph();
    size_t src = 0;
    auto path = dijkstra(graph, src);

    std::deque<unsigned int> expected_cost {0, 1, 3, 6, 5, 7};
    std::deque<size_t> expected_came_from {0, 0, 1, 2, 2, 4};

    std::deque<unsigned int> result_cost {path.first.begin(), path.first.end() - 1};
    std::deque<size_t> result_came_from {path.second.begin(), path.second.end() - 1};
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
  }

  void testDijkstraOriginalDirectedGraph() {
    auto graph = graph_test::distanceGraph();
    size_t src = 0;
    auto path = dijkstraOriginal(graph, src, src);

    std::deque<unsigned int> expected_cost{0, 1, 3, 6, 5, 7};
    std::deque<size_t> expected_came_from{0, 0, 1, 2, 2, 4};

    std::deque<unsigned int> result_cost {path.first.begin(), path.first.end() - 1};
    std::deque<size_t> result_came_from {path.second.begin(), path.second.end() - 1};
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
  }

  void testDijkstraTreeBasedDirectedGraph() {
    auto graph = graph_test::distanceGraph();
    size_t src = 0;
    auto path = dijkstraTreeBase(graph, src, src);

    std::deque<unsigned int> expected_cost{0, 1, 3, 6, 5, 7};
    std::deque<size_t> expected_came_from{0, 0, 1, 2, 2, 4};

    std::deque<unsigned int> result_cost {path.first.begin(), path.first.end() - 1};
    std::deque<size_t> result_came_from {path.second.begin(), path.second.end() - 1};
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
  }

  void testDijkstra() {
    std::cout << "\nTesting Dijkstra's algorithm..." << std::endl;

    testDijkstraDirectedGraph();
    testDijkstraDirectedGraphWithDestination();
    testDijkstraUnDirectedGraph();
    testDijkstraOriginalDirectedGraph();
    testDijkstraTreeBasedDirectedGraph();
  }

} // namespace graph_test

#endif //GRAPH_TEST_DIJKSTRA_H