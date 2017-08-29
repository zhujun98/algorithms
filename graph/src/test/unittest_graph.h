//
// Created by jun on 6/23/17.
//
// Test graph implementations.
//
#ifndef GRAPH_UNITTEST_GRAPH_H
#define GRAPH_UNITTEST_GRAPH_H

#include <cassert>
#include <string>

#include "../directed_graph.h"
#include "../undirected_graph.h"
#include "../graph_utilities.h"
#include "../graph_algorithms/breath_first_search.h"
#include "../graph_algorithms/depth_first_search.h"


namespace graph_test {
  //
  // a simple undirected graph
  //
  //  a---b---e---f
  //  | x |   | x |
  //  d---c---h---g
  //
  // the minimum cut is 2.
  //
  // @param return: an undirected graph
  //
  UndirectedGraph<unsigned int> simpleUdGraph() {
    UndirectedGraph<unsigned int> graph(8);
    enum Vertices {a, b, c, d, e, f, g, h};
    graph.connect(a, b);
    graph.connect(a, c);
    graph.connect(a, d);
    graph.connect(b, c);
    graph.connect(b, d);
    graph.connect(b, e);
    graph.connect(c, d);
    graph.connect(c, h);
    graph.connect(e, f);
    graph.connect(e, g);
    graph.connect(e, h);
    graph.connect(f, g);
    graph.connect(f, h);
    graph.connect(g, h);

    assert(graph.countEdge() == 14);
    assert(graph.countWeight() == 14);

    return graph;
  }

  //
  // a simple directed graph
  //
  // The annotation "1 *- 4" means from 1 to 4.
  //
  // 0  *-  3 *- 1  *-  4  *-  2  *-  5    9 *- 10
  //  \    *      \    *        \    *     \    *
  //   *  /        *  /          *  /       *  /
  //     6  *----    7             8         11
  // @param return: a directed graph
  //
  DirectedGraph<unsigned int> simpleGraph() {
    DirectedGraph<unsigned int> graph(12);

    graph.connect(0, 3);
    graph.connect(1, 4);
    graph.connect(2, 5);
    graph.connect(3, 1);
    graph.connect(3, 6);
    graph.connect(4, 2);
    graph.connect(4, 7);
    graph.connect(5, 8);
    graph.connect(6, 0);
    graph.connect(6, 7);
    graph.connect(7, 1);
    graph.connect(8, 2);
    graph.connect(9, 10);
    graph.connect(10, 11);
    graph.connect(11, 9);

    assert(graph.countEdge() == 15);
    assert(graph.countWeight() == 15);

    return graph;
  }

  //
  // a simple directed graph with negative weight
  //
  // The annotation "0 *- 1" means from 0 to 1.
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
  DirectedGraph<int> negativeWeightedGraph() {
    DirectedGraph<int> graph(6);
    enum Vertices {a, b, c, d, e, f};

    graph.connect(a, b, 1);
    graph.connect(a, c, 4);
    graph.connect(b, d, -6);
    graph.connect(b, c, 2);
    graph.connect(c, d, 3);
    graph.connect(c, e, -2);
    graph.connect(d, e, -3);
    graph.connect(d, f, 5);
    graph.connect(e, f, 2);
    graph.connect(a, e, -4);

    assert(graph.countEdge() == 10);
    assert(graph.countWeight() == 2);

    return graph;
  }

  //
  // a simple weighted undirected graph
  //
  // The annotation "0 *- 1" means from 0 to 1.
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
  UndirectedGraph<int> negativeWeightedUdGraph() {
    UndirectedGraph<int> graph(6);
    enum Vertices {a, b, c, d, e, f};

    graph.connect(a, b, 1);
    graph.connect(a, c, 4);
    graph.connect(b, d, -6);
    graph.connect(b, c, 2);
    graph.connect(c, d, 3);
    graph.connect(c, e, -2);
    graph.connect(d, e, -3);
    graph.connect(d, f, 5);
    graph.connect(e, f, 2);
    graph.connect(a, e, -4);

    assert(graph.countEdge() == 10);
    assert(graph.countWeight() == 2);

    return graph;
  }

  //
  // a simple weighted undirected graph
  //
  // The annotation "0 *- 1" means from 0 to 1.
  //    (1)    (6)      (5)
  // a  --  b  --  d  ------  f       g
  //   \    |    /   \       /
  //    \   |(2)/     \ (3) / (2)
  // (4) \  |  / (3)   \   /
  //      \ | /         \ /
  //        c  --------  e
  //              (2)
  //
  // @param return: an un-directed graph
  //
  UndirectedGraph<unsigned int> distanceUdGraph() {
    UndirectedGraph<unsigned int> graph(7);
    enum Vertices {a, b, c, d, e, f};

    graph.connect(a, b, 1);
    graph.connect(a, c, 4);
    graph.connect(b, c, 2);
    graph.connect(b, d, 6);
    graph.connect(c, d, 3);
    graph.connect(c, e, 2);
    graph.connect(d, e, 3);
    graph.connect(d, f, 5);
    graph.connect(e, f, 2);

    assert(graph.countEdge() == 9);
    assert(graph.countWeight() == 28);

    return graph;
  }

  //
  // a simple weighted directed graph
  //
  // The annotation "0 *- 1" means from 0 to 1.
  //    (1)    (6)      (5)
  // a  *-  b  *-  d  *-----  f       g
  //   *    *    /   *       /
  //    \   |(2)/     \ (3) / (2)
  // (4) \  |  / (3)   \   /
  //      \ | *         \ *
  //        c  *-------  e
  //              (2)
  //
  // @param return: a directed graph
  //
  DirectedGraph<unsigned int> distanceGraph() {
    DirectedGraph<unsigned int> graph(7);
    enum Vertices {a, b, c, d, e, f};

    graph.connect(a, b, 1);
    graph.connect(a, c, 4);
    graph.connect(b, c, 2);
    graph.connect(b, d, 6);
    graph.connect(c, d, 3);
    graph.connect(c, e, 2);
    graph.connect(d, e, 3);
    graph.connect(d, f, 5);
    graph.connect(e, f, 2);

    assert(graph.countEdge() == 9);
    assert(graph.countWeight() == 28);

    return graph;
  }

  //
  // test the copy constructor
  //
  void testGraphCopy() {
    std::cout << "\nTesting graph copy constructor..." << std::endl;

    auto graph = simpleGraph();
    auto graph_copy(graph);
    assert(graph.size() == graph_copy.size());
    assert(graph.countEdge() == graph_copy.countEdge());
    assert(graph.countWeight() == graph_copy.countWeight());

    auto ud_graph = simpleUdGraph();
    auto ud_graph_copy(ud_graph);
    assert(ud_graph.size() == ud_graph_copy.size());
    assert(ud_graph.countEdge() == ud_graph_copy.countEdge());
    assert(ud_graph.countWeight() == ud_graph_copy.countWeight());

    std::cout << "Passed!" << std::endl;
  }

  //
  // test function reverseGraph()
  //
  void testReverseGraph() {
    std::cout << "\nTesting reverse member function of DirectedGraph..." << std::endl;

    auto graph = simpleGraph();

    auto graph_reversed = simpleGraph();
    graph_reversed.reverse();

    assert(graph.countEdge() == graph_reversed.countEdge());
    assert(graph.countWeight() == graph_reversed.countWeight());
    assert(graph_reversed.getList(3)->dst == 0);
    assert(graph_reversed.getList(0)->dst == 6);

    std::cout << "Passed!" << std::endl;
  }

} // namespace graph_test

#endif //GRAPH_UNITTEST_GRAPH_H
