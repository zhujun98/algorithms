//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_TEST_KOSARAJU_H
#define GRAPH_TEST_KOSARAJU_H


#include "unittest_graph.h"
#include "../graph_algorithms/kosaraju.h"


namespace graph_test {

  void testKosaraju() {
    std::cout << "\nTesting Kosaraju's algorithm..." << std::endl;
    auto graph = graph_test::simpleGraph();

    std::deque<std::deque<size_t>> scc = kosaraju(graph);

    std::deque<std::deque<size_t>>
        expected_scc = {{11, 10, 9}, {8, 5, 2}, {7, 4, 1}, {6, 3, 0}};

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

} // namespace graph_test

#endif //GRAPH_TEST_KOSARAJU_H
