//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_TEST_PRIM_H
#define GRAPH_TEST_PRIM_H


#include "unittest_graph.h"
#include "../graph_algorithms/prim.h"


namespace graph_test {

  void testPrim() {
    std::cout << "\nTesting Prim's algorithm..." << std::endl;

    auto graph = graph_test::negativeWeightedUdGraph();

    typedef std::pair<double, std::vector<std::pair<size_t, size_t>>> mst_tree;

    size_t src = 0;
    mst_tree mst = prim(graph, src);
    mst_tree expected_mst = {-13, {{0, 4}, {4, 3}, {3, 1}, {4, 2}, {4, 5}}};

    if (mst == expected_mst) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: (total cost = "
                << mst.first << ")" << std::endl;
      graph_utilities::printContainer(mst.second);
      std::cout << "The correct result is: (total cost = "
                << expected_mst.first << ")" << std::endl;
      graph_utilities::printContainer(expected_mst.second);
    }
  }

} // namespace graph_test

#endif //GRAPH_TEST_PRIM_H
