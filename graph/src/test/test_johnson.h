//
// Created by jun on 9/1/17.
//

#ifndef GRAPH_TEST_JOHNSON_H
#define GRAPH_TEST_JOHNSON_H

#include "unittest_graph.h"
#include "../graph_algorithms/johnson.h"


namespace graph_test {

void testJohnson() {
  std::cout << "\nTesting Johnson's algorithm..." << std::endl;

  auto graph = graph_test::negativeWeightedGraph();
  typedef int weight_t;

  std::pair<std::deque<std::deque<int>>, std::deque<std::deque<size_t>>>
      result = johnson(graph);

//    for (auto& v : result.first) {
//      for (auto& vv : v) {
//        std::cout << vv << ", ";
//      }
//      std::cout << "\n";
//    }
//    std::cout << std::endl;

  assert(result.first[0][3] == -5 &&
         result.first[0][5] == -6 &&
         result.first[1][4] == -9 &&
         result.first[3][5] == -1);

  std::cout << "Passed!" << std::endl;
}

}

#endif //GRAPH_TEST_JOHNSON_H
