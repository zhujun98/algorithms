//
// Created by jun on 6/23/17.
//
// Functions:
// - simpleUdGraph()
// - simpleGraph()
// - distanceGraph()
// - testGraphCopy()
// - testReverseGraph()
// - testBreathFirstSearch()
// - testDepthFirstSearch()
//

#ifndef GRAPH_UNITTEST_GRAPH_H
#define GRAPH_UNITTEST_GRAPH_H

#include <string>

#include "graph_adj.h"


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
  UdGraphAdj<std::string> simpleUdGraph() {
    UdGraphAdj<std::string> graph;
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
  // 1  *-  4 *- 2  *-  5  *-  3  *-  6
  //  \    *      \    *        \    *
  //   *  /        *  /          *  /
  //     7           8             9
  // @param return: a directed graph
  //
  GraphAdj<int> simpleGraph() {
    GraphAdj<int> graph;

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
  GraphAdj<std::string> distanceGraph() {
    GraphAdj<std::string> graph;

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
  // test the copy constructor
  //
  void testGraphCopy() {
    std::cout << "\nTesting graph copy constructor..." << std::endl;

    GraphAdj<int> graph = simpleGraph();
    GraphAdj<int> graph_copy(graph);

    UdGraphAdj<std::string> ud_graph = simpleUdGraph();
    UdGraphAdj<std::string> ud_graph_copy(ud_graph);
  }

  //
  // test function reverseGraph()
  //
  void testReverseGraph() {
    std::cout << "\nTesting function reverseGraph()..." << std::endl;

    GraphAdj<int> graph = simpleGraph();
    GraphAdj<int> graph_reversed = graph::reverseGraph(graph);
  }


  //
  // test the implementation of breathFirstSearch algorithm
  //
  void testBreathFirstSearch() {
    std::cout << "\nTesting BFS algorithm..." << std::endl;

    // test on directed graph
    GraphAdj<int> graph = simpleGraph();

    std::vector<int> result = graph.breathFirstSearch(1);
    std::vector<int> expected_result = {1, 4, 2, 7, 5, 3, 8, 6, 9};

    if ( result == expected_result ) {
      ;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printVector(result);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printVector(expected_result);
    }

    // test on undirected graph
    UdGraphAdj<std::string> ud_graph = simpleUdGraph();
    std::vector<std::string> result_ud = ud_graph.breathFirstSearch("a");
    std::vector<std::string> expected_result_ud = {"a", "b", "c", "d", "e", "h", "f", "g"};

    if ( result_ud == expected_result_ud ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printVector(result_ud);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printVector(expected_result_ud);
    }

  }

  //
  // test the implementation of depthFirstSearch algorithm
  //
  void testDepthFirstSearch() {
    std::cout << "\nTesting DFS algorithm..." << std::endl;

    // test on directed graph
    GraphAdj<int> graph = simpleGraph();

    std::vector<int> result = graph.depthFirstSearch(1);
    std::vector<int> expected_result = {9, 6, 3, 8, 5, 2, 7, 4, 1};

    if ( result == expected_result ) {
      ;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printVector(result);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printVector(expected_result);
    }

    // test on undirected graph
    UdGraphAdj<std::string> ud_graph = simpleUdGraph();

    std::vector<std::string> result_ud = ud_graph.depthFirstSearch("a");
    std::vector<std::string> expected_result_ud = {"d", "g", "f", "e", "h", "c", "b", "a"};

    if ( result_ud == expected_result_ud ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printVector(result_ud);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printVector(expected_result_ud);
    }

  }

}

#endif //GRAPH_UNITTEST_GRAPH_H
