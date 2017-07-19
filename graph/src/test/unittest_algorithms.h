//
// Created by jun on 6/23/17.
//
// Test implementations of graph related algorithms.
//

#ifndef GRAPH_UNITTEST_ALGORITHMS_H
#define GRAPH_UNITTEST_ALGORITHMS_H

#include <string>

#include "../graph_adj.h"
#include "../graph_utilities.h"
#include "unittest_graph.h"
#include "../graph_algorithms.h"


namespace graph_test {
  //
  // test the implementation of Kosaraju's algorithm
  //
  void testKosaraju() {

    std::cout << "\nTesting Kosaraju's algorithm..." << std::endl;
    GraphAdj<int> graph = graph_test::simpleGraph();

    std::vector<std::vector<int>> scc = graph::kosaraju(graph);

    std::vector<std::vector<int>> expected_scc = {{11, 12, 10}, {4, 7, 1}, {5, 8, 2}, {6, 9, 3}};

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

  //
  // test the implementation of Karger's algorithm
  //
  void testKarger() {

    std::cout << "\nTesting Karger's algorithm..." << std::endl;

    UdGraphAdj<std::string> graph = graph_test::simpleUdGraph();

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
  // Check whether a vertex was explored after the search using
  // Dijkstra's algorithm
  //
  bool isEmpty(const std::pair<double, std::string>& vertex) {
    return vertex.second.empty();
  }

  //
  // test the implementation of Dijkastra's algorithm
  //
  void testDijkstra() {
    std::cout << "\nTesting Dijkstra's algorithm..." << std::endl;

    GraphAdj<std::string> graph = graph_test::distanceGraph();

    std::string source = "a";
    std::vector<std::pair<double, std::string>> shortest_path =
        graph::dijkstra(graph, source);
    std::vector<std::pair<double, std::string>> shortest_path_1 =
        graph::dijkstra_base_tree(graph, source, source);
    assert(shortest_path == shortest_path_1);

    std::vector<std::pair<double, std::string>> expected_shortest_path =
        {{0, "a"}, {1, "a"}, {6, "c"}, {3, "b"}, {5, "c"}, {7, "f"}};


    if ( shortest_path == expected_shortest_path ) {
      ;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(shortest_path);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_shortest_path);
    }

    std::string destination = "f";
    std::vector<std::pair<double, std::string>> shortest_path_dst =
        graph::dijkstra(graph, source, destination);
    std::vector<std::pair<double, std::string>> shortest_path_dst_1 =
        graph::dijkstra_base_tree(graph, source, destination);
    assert(shortest_path_dst == shortest_path_dst_1);

    // remove the untouched vertices
    auto pend = std::remove_if(shortest_path_dst.begin(),
                               shortest_path_dst.end(),
                               isEmpty);
    std::vector<std::pair<double, std::string>>
        shortest_path_dst_filtered (shortest_path_dst.begin(), pend);

    std::vector<std::pair<double, std::string>> expected_shortest_path_dst =
        {{0, "a"}, {1, "a"}, {6, "c"}, {3, "b"}, {5, "c"}};

    if ( shortest_path_dst_filtered == expected_shortest_path_dst ) {
      std::cout << "Passed!" << std::endl;
      graph::showDijkstraPath(graph, shortest_path_dst, source, destination);
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: " << std::endl;
      graph_utilities::printContainer(shortest_path_dst_filtered);
      std::cout << "The correct result is: " << std::endl;
      graph_utilities::printContainer(expected_shortest_path_dst);
    }

  }

  //
  // test the implementation of Prim's algorithm
  //
  void testPrim() {
    std::cout << "\nTesting Prim's algorithm..." << std::endl;

    UdGraphAdj<std::string> graph = graph_test::distanceUdGraph();

    typedef std::pair<double, std::vector<std::pair<std::string, std::string>>> mst_tree;

    // starting from the first vertex by default
    mst_tree mst = graph::prim(graph);
    mst_tree expected_mst =
        {-13, {{"a", "e"}, {"e", "d"}, {"d", "b"}, {"e", "c"}, {"e", "f"}}};

    if (mst == expected_mst) {
      ;
    } else {
      std::cout << "Failed!!!" << std::endl;
      std::cout << "The output is: (total cost = "
                << mst.first << ")" << std::endl;
      graph_utilities::printContainer(mst.second);
      std::cout << "The correct result is: (total cost = "
                << expected_mst.first << ")" << std::endl;
      graph_utilities::printContainer(expected_mst.second);
    }

    // starting from an appointing vertex
    mst = graph::prim(graph, std::string("c"));
    expected_mst =
        {-13, {{"c", "e"}, {"e", "a"}, {"e", "d"}, {"d", "b"}, {"e", "f"}}};

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

  //
  // test the implementation of Kurlskar's algorithm
  //
  void testKruskal() {
    std::cout << "\nTesting Kruskal's algorithm..." << std::endl;

    UdGraphAdj<std::string> graph = graph_test::distanceUdGraph();

    typedef std::pair<double, std::vector<std::pair<std::string, std::string>>> mst_tree;

    // starting from an appointing vertex
    mst_tree mst = graph::kruskal(graph);
    mst_tree expected_mst =
        {-13, {{"b", "d"}, {"a", "e"}, {"e", "d"}, {"e", "c"}, {"f", "e"}}};

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

#endif //GRAPH_UNITTEST_ALGORITHMS_H
