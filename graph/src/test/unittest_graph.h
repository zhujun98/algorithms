//
// Created by jun on 6/23/17.
//
// Test graph implementations.
//
#ifndef GRAPH_UNITTEST_GRAPH_H
#define GRAPH_UNITTEST_GRAPH_H

#include <string>

#include "../graph.h"
#include "../ud_graph.h"


namespace graph_test {
  //
  // build a simple undirected graph for testing
  //
  //  a---b---e---f
  //  | x |   | x |
  //  d---c---h---g
  //
  // the minimum cut is 2.
  //
  // @param return: an undirected graph
  //
  UdGraph<std::string> simpleUdGraph() {
    UdGraph<std::string> graph;
    graph.connect("a", "b");
    graph.connect("b", "c");
    graph.connect("c", "d");
    graph.connect("d", "a");
    graph.connect("a", "c");
    graph.connect("b", "d");
    graph.connect("e", "f");
    graph.connect("f", "g");
    graph.connect("g", "h");
    graph.connect("h", "e");
    graph.connect("e", "g");
    graph.connect("f", "h");
    graph.connect("b", "e");
    graph.connect("c", "h");

//    graph.display();
    return graph;
  }

  //
  // build a simple directed graph for testing
  //
  // The annotation "1 *- 4" means from 1 to 4.
  //
  // 1  *-  4 *- 2  *-  5  *-  3  *-  6   10 *- 11
  //  \    *      \    *        \    *     \    *
  //   *  /        *  /          *  /       *  /
  //     7  *----    8             9         12
  // @param return: a directed graph
  //
  Graph<int> simpleGraph() {
    Graph<int> graph;

    graph.connect(1, 4);
    graph.connect(4, 7);
    graph.connect(7, 1);
    graph.connect(4, 2);
    graph.connect(2, 5);
    graph.connect(5, 8);
    graph.connect(8, 2);
    graph.connect(5, 3);
    graph.connect(3, 6);
    graph.connect(6, 9);
    graph.connect(9, 3);
    graph.connect(7, 8);
    graph.connect(10, 11);
    graph.connect(11, 12);
    graph.connect(12, 10);

//    graph.display();
    return graph;
  }

  //
  // build a simple directed graph for testing
  //
  // The annotation "0 *- 1" means from 0 to 1.
  //    (1)    (6)      (5)
  // a  *-  b  *-  d  *-----  g
  //   *    *    /   *       /
  //    \   |(2)/     \ (3) / (2)
  // (4) \  |  / (3)   \   /
  //      \ | *         \ *
  //        c  *-------  f
  //              (2)
  //
  // @param return: a directed graph
  //
  Graph<std::string> distanceGraph() {
    Graph<std::string> graph;

    graph.connect("a", "b", 1);
    graph.connect("b", "d", 6);
    graph.connect("a", "c", 4);
    graph.connect("b", "c", 2);
    graph.connect("c", "d", 3);
    graph.connect("c", "f", 2);
    graph.connect("d", "f", 3);
    graph.connect("d", "g", 5);
    graph.connect("f", "g", 2);

//    graph.display();
    return graph;
  }

  //
  // build a simple directed graph for testing
  //
  // The annotation "0 *- 1" means from 0 to 1.
  //
  //
  //
  //    (1)    (-6)      (5)
  // a ---- b ---- d -------- f
  // | \    |    /   \       /
  // |  \   |(2)/     \(-3) / (2)
  // |(4)\  |  / (3)   \   /
  // |    \ | /         \ /
  // |      c  --------  e
  // |           (-2)    |
  // |------- (-4) ------|
  //
  //
  // @param return: a directed graph
  //
  UdGraph<std::string> distanceUdGraph() {
    UdGraph<std::string> graph;

    graph.connect("a", "b", 1);
    graph.connect("a", "c", 4);
    graph.connect("b", "d", -6);
    graph.connect("b", "c", 2);
    graph.connect("c", "d", 3);
    graph.connect("c", "e", -2);
    graph.connect("d", "e", -3);
    graph.connect("d", "f", 5);
    graph.connect("e", "f", 2);
    graph.connect("a", "e", -4);

//    graph.display();
    return graph;
  }

  //
  // test the copy constructor
  //
  void testGraphCopy() {
    std::cout << "\nTesting graph copy constructor..." << std::endl;

    Graph<int> graph = simpleGraph();
//    graph.display();
    Graph<int> graph_copy(graph);
//    graph_copy.display();

    UdGraph<std::string> ud_graph = simpleUdGraph();
//    ud_graph.display();
    UdGraph<std::string> ud_graph_copy(ud_graph);
//    ud_graph_copy.display();
  }

  //
  // test function reverseGraph()
  //
  void testReverseGraph() {
    std::cout << "\nTesting function reverseGraph()..." << std::endl;

    Graph<int> graph = simpleGraph();
    Graph<int> graph_reversed = graph::reverseGraph(graph);
  }


  //
  // test the implementation of breathFirstSearch algorithm
  //
  void testBreathFirstSearch() {
    std::cout << "\nTesting BFS algorithm..." << std::endl;

    // test on directed graph
    Graph<int> graph = simpleGraph();

    std::vector<int> result = graph::breathFirstSearch(graph, 1);
    std::vector<int> expected_result({1, 4, 2, 7, 5, 8, 3, 6, 9});

    if ( result == expected_result ) {
      ;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_result);
    }

    // test on undirected graph
    UdGraph<std::string> ud_graph = simpleUdGraph();
    std::string source = "a";
    std::vector<std::string> result_ud = graph::breathFirstSearch(ud_graph, source);
    std::vector<std::string> expected_result_ud({"a", "b", "c", "d", "e", "h", "f", "g"});

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

  //
  // test the implementation of depthFirstSearch algorithm
  //
  void testDepthFirstSearch() {
    std::cout << "\nTesting DFS algorithm..." << std::endl;

    // test on directed graph
    Graph<int> graph = simpleGraph();

    std::vector<int> result = graph::depthFirstSearch(graph, 1);
    std::vector<int> expected_result = {9, 6, 3, 8, 5, 2, 7, 4, 1};

    if ( result == expected_result ) {
      ;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_result);
    }

    // test on undirected graph
    UdGraph<std::string> ud_graph = simpleUdGraph();
    std::string source = "a";

    std::vector<std::string> result_ud = graph::depthFirstSearch(ud_graph, source);
    std::vector<std::string> expected_result_ud = {"d", "g", "f", "e", "h", "c", "b", "a"};

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

}

#endif //GRAPH_UNITTEST_GRAPH_H
