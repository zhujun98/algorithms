//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_TEST_KARGER_H
#define GRAPH_TEST_KARGER_H

#include "unittest_graph.h"
#include "../graph_algorithms/karger.h"


namespace graph_test {

  void testKarger() {

    std::cout << "\nTesting Karger's algorithm..." << std::endl;

    auto graph = graph_test::simpleUdGraph();

    size_t min_cut = karger(graph, 1000);

    if (min_cut == 2) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is " << min_cut << std::endl;
      std::cout << "The correct result is 2" << std::endl;
    }
  }

} // namespace graph_test

#endif //GRAPH_TEST_KARGER_H
