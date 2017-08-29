//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_TEST_KRUSKAL_H
#define GRAPH_TEST_KRUSKAL_H

#include "unittest_graph.h"
#include "../graph_algorithms/kruskal.h"


namespace graph_test {

  void testKruskal() {
    std::cout << "\nTesting Kruskal's algorithm..." << std::endl;

    auto graph = graph_test::negativeWeightedUdGraph();

    typedef std::pair<int, std::vector<std::pair<size_t, size_t>>> mst_tree;

    // starting from an appointing vertex
    mst_tree mst = kruskal(graph);
    mst_tree expected_mst = {-13, {{1, 3}, {4, 0}, {4, 3}, {2, 4}, {4, 5}}};

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

}

#endif //GRAPH_TEST_KRUSKAL_H
