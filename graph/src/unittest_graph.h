//
// Created by jun on 6/23/17.
//
// Functions:
// - simpleUdGraph()
// - simpleGraph()
// - distanceGraph()
// - testBreathFirstSearch
// - testDepthFirstSearch
// - testKarger()
// - testKosaraju()
// - testDijkstra()
//

#ifndef GRAPH_MYUNITTEST_H
#define GRAPH_MYUNITTEST_H

#include "graph_adj.h"
#include "graph_utilities.h"
#include "graph_algorithms.h"


namespace my_test {
  //
  // build a simple undirected graph for testing
  //
  //  0---1---4---5
  //  | x |   | x |
  //  3---2---7---6
  //
  // the minimum cut is 2.
  //
  // @param return: an undirected graph
  //
  UdGraphAdj simpleUdGraph() {
    UdGraphAdj graph(8);

    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    graph.connect(0, 2);
    graph.connect(1, 3);
    graph.connect(4, 5);
    graph.connect(5, 6);
    graph.connect(6, 7);
    graph.connect(7, 4);
    graph.connect(4, 6);
    graph.connect(5, 7);
    graph.connect(1, 4);
    graph.connect(2, 7);

    return graph;
  }

  //
  // build a simple directed graph for testing
  //
  // The annotation "0 *- 3" means from 0 to 3.
  //
  // 0  *-  3 *- 1  *-  4  *-  2  *-  5
  //  \    *      \    *        \    *
  //   *  /        *  /          *  /
  //     6           7             8
  // @param return: a directed graph
  //
  GraphAdj simpleGraph() {
    GraphAdj graph(9);

    graph.connect(0, 3);
    graph.connect(3, 6);
    graph.connect(6, 0);
    graph.connect(3, 1);
    graph.connect(1, 4);
    graph.connect(4, 7);
    graph.connect(7, 1);
    graph.connect(4, 2);
    graph.connect(2, 5);
    graph.connect(5, 8);
    graph.connect(8, 2);

    return graph;
  }

  //
  // build a simple directed graph for testing
  //
  // The annotation "0 *- 1" means from 0 to 1.
  //    (1)    (6)
  // 0  *-  1  *-  3
  //   *    *    /
  //    \   |(2)/
  // (4) \  |  / (3)
  //      \ | *
  //        2
  //
  // @param return: a directed graph
  //
  GraphAdj distanceGraph() {
    GraphAdj graph(4);

    graph.connect(0, 1, 1, 1);
    graph.connect(1, 3, 1, 6);
    graph.connect(0, 2, 1, 4);
    graph.connect(1, 2, 1, 2);
    graph.connect(2, 3, 1, 3);

    return graph;
  }

  //
  // test the implementation of breathFirstSearch algorithm
  //
  void testBreathFirstSearch() {
    std::cout << "\nTesting BFS algorithm..." << std::endl;

    // test on undirected graph
    UdGraphAdj ud_graph = simpleUdGraph();

    std::vector<int> result = ud_graph.breathFirstSearch(0);
    std::vector<int> expected_result = {0, 1, 2, 3, 4, 7, 5, 6};

    if ( result == expected_result ) {
      ;
//      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph::printContainer(expected_result);
    }

    // test on directed graph
    GraphAdj graph = simpleGraph();

    result = graph.breathFirstSearch(0);
    expected_result = {0, 3, 1, 6, 4, 2, 7, 5, 8};

    if ( result == expected_result ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph::printContainer(expected_result);
    }

  }

  //
  // test the implementation of depthFirstSearch algorithm
  //
  void testDepthFirstSearch() {
    std::cout << "\nTesting DFS algorithm..." << std::endl;

    // test on undirected graph
    UdGraphAdj ud_graph = simpleUdGraph();

    std::vector<int> result = ud_graph.depthFirstSearch(0);
    std::vector<int> expected_result = {3, 6, 5, 4, 7, 2, 1, 0};

    if ( result == expected_result ) {
      ;
//      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph::printContainer(expected_result);
    }

    // test on directed graph
    GraphAdj graph = simpleGraph();

    result = graph.depthFirstSearch(0);
    expected_result = {8, 5, 2, 7, 4, 1, 6, 3, 0};

    if ( result == expected_result ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph::printContainer(result);
      std::cout << "The correct result is: " << std::endl;
      graph::printContainer(expected_result);
    }
  }

  //
  // test the implementation of Kosaraju's algorithm
  //
  void testKosaraju() {

    std::cout << "\nTesting Kosaraju's algorithm..." << std::endl;
    GraphAdj graph = simpleGraph();

    std::vector<std::vector<int>> scc = graph::kosaraju(graph);

    std::vector<std::vector<int>> expected_scc = {{3, 6, 0}, {4, 7, 1}, {5, 8, 2}};

    if ( scc == expected_scc ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph::printSCC(scc);
      std::cout << "The correct result is: " << std::endl;
      graph::printSCC(expected_scc);
    }

  }

  //
  // test the implementation of Karger's algorithm
  //
  void testKarger() {

    std::cout << "\nTesting Karger's algorithm..." << std::endl;

    UdGraphAdj graph = simpleUdGraph();

    int min_cut = graph::karger(graph, 1000);

    if ( min_cut == 2 ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is " << min_cut << std::endl;
      std::cout << "The correct result is 2" << std::endl;
    }
  }

  //
  // test the implementation of Dijkastra's algorithm
  //
  void testDijkstra() {

    std::cout << "\nTesting Dijkstra's algorithm..." << std::endl;

    GraphAdj graph = distanceGraph();

    std::vector<double> shortest_distance = graph::dijkstra(graph, 0);
    std::vector<double> expected_result = {0, 1, 3, 6};

    if ( shortest_distance == expected_result ) {
      std::cout << "Passed!" << std::endl;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph::printContainer(shortest_distance);
      std::cout << "The correct result is: " << std::endl;
      graph::printContainer(expected_result);
    }
  }
}

#endif //GRAPH_MYUNITTEST_H
