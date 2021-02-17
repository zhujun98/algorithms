//
// Created by jun on 9/1/17.
//

#ifndef GRAPH_TEST_FLOYD_WARSHALL_H
#define GRAPH_TEST_FLOYD_WARSHALL_H

#include "unittest_graph.h"
#include "../graph_algorithms/floyd_warshall.h"


namespace graph_test {

  void testFloydWarshall() {
    std::cout << "\nTesting Floyd-Warshall's algorithm..." << std::endl;

    auto graph = graph_test::negativeWeightedGraph();
    graph.disconnect(0, 1);
    typedef int weight_t;

    std::pair<std::deque<std::deque<int>>, std::deque<std::deque<size_t>>>
        result = floydWarshall(graph);

//    for (auto& v : result.first) {
//      for (auto& vv : v) {
//        std::cout << vv << ", ";
//      }
//      std::cout << "\n";
//    }
//    std::cout << std::endl;

    assert(result.first[0][3] == 7 &&
           result.first[0][5] == -2 &&
           result.first[1][4] == -9 &&
           result.first[3][5] == -1);

    std::cout << "Passed!" << std::endl;
  }

}

#endif //GRAPH_TEST_FLOYD_WARSHALL_H
