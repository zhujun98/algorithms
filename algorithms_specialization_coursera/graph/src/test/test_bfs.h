//
// Created by jun on 8/27/17.
//

#ifndef GRAPH_TEST_BFS_H
#define GRAPH_TEST_BFS_H

#include "unittest_graph.h"

namespace graph_test {

  void testBreathFirstSearch() {
    std::cout << "\nTesting BFS algorithm..." << std::endl;

    // test on directed graph
    auto graph = simpleGraph();

    std::vector<size_t> result = breathFirstSearch(graph, 0);
    std::vector<size_t> expected_result {0, 3, 6, 1, 7, 4, 2, 5, 8};

    if ( result == expected_result ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_result);
    }

    // test on undirected graph
    auto ud_graph = simpleUdGraph();
    std::vector<size_t> result_ud = breathFirstSearch(ud_graph, 0);
    std::vector<size_t> expected_result_ud {0, 3, 2, 1, 7, 4, 6, 5};

    if ( result_ud == expected_result_ud ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result_ud);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_result_ud);
    }
  }

}  // namespace graph_test

#endif //GRAPH_TEST_BFS_H
