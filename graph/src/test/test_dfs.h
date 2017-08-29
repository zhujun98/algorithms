//
// Created by jun on 8/27/17.
//

#ifndef GRAPH_TEST_DFS_H
#define GRAPH_TEST_DFS_H

#include "unittest_graph.h"

namespace graph_test {

  void testDepthFirstSearch() {
    std::cout << "\nTesting DFS algorithm..." << std::endl;

    // test on undirected graph
    auto ud_graph = simpleUdGraph();

    std::vector<size_t> result_ud = depthFirstSearch(ud_graph, 0);
    std::vector<size_t> expected_result_ud {1, 4, 5, 6, 7, 2, 3, 0};

    if ( result_ud == expected_result_ud ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result_ud);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_result_ud);
    }

    // test on directed graph
    auto graph = simpleGraph();
    std::vector<size_t> result = depthFirstSearch(graph, 0);
    std::vector<size_t> expected_result {8, 5, 2, 4, 1, 7, 6, 3, 0};

    if ( result == expected_result ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_result);
    }
  }

} // namespace graph_test


#endif //GRAPH_TEST_DFS_H
