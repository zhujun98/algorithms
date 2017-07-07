//
// Created by jun on 6/19/17.
//
// Functions:
// - copyGraph()
// - graphContract()
// - reverseGraph()
// - printSCC()
// - printContainer()
//

#ifndef GRAPH_GRAPH_UTILITIES_H
#define GRAPH_GRAPH_UTILITIES_H

#include <iostream>
#include <random>
#include <vector>

#include "graph_adj.h"


namespace graph {

  //
  // copy a graph
  //
  // @param graph: the original graph (can be directed or undirected)
  //
  // @param return: the copied graph
  //
  template <class G>
  inline G copyGraph(const G& graph) {
    std::size_t g_size = graph.size();
    G g_copy(g_size);

    for(std::size_t i=0; i<g_size; ++i) {
      graph::AdjListNode* current = graph.getVertex(i).head;
      while ( current ) {
        g_copy.connect(i, current->value);
        current = current->next;
      }
    }

    return g_copy;
  }

  //
  // reverse a directed graph
  //
  // @param graph: the original graph
  //
  // @param return: the reversed graph
  //
  inline GraphAdj reverseGraph(const GraphAdj& graph) {
    std::size_t g_size = graph.size();
    GraphAdj reversed(g_size);

    for (std::size_t i=0; i<g_size; ++i) {
      graph::AdjListNode* current = graph.getVertex(i).head;
      while ( current ) {
        reversed.connect(current->value, i);
        current = current->next;
      }
    }

    return reversed;
  }

  //
  // contract an undirected graph until only two non-empty linked lists remain
  //
  // @param graph: an undirected graph
  //
  // @return: the number of edges in the contracted graph
  //
  inline int graphContract(UdGraphAdj& graph, bool display=false) {

    // Distribution on which to apply the generator
    std::vector<int> connected_vertices = graph.getConnectedVertices();

    std::random_device rd;
    std::default_random_engine generator(rd());
    while ( connected_vertices.size() > 2 ) {
      std::uniform_int_distribution<long unsigned> distribution(0, 10000000);

      unsigned long first = distribution(generator) % connected_vertices.size();
      unsigned long second = distribution(generator) % (connected_vertices.size() - 1);
      if (second >= first) { ++second; }

      if ( display ) {
        std::cout << connected_vertices[first] << " " << connected_vertices[second] << std::endl;
      }
      graph.collapse(connected_vertices[first], connected_vertices[second]);

      connected_vertices = graph.getConnectedVertices();
      if ( display) { graph.display(); }
    }

    return graph.countEdge();
  }

  //
  // print the strongly connected components
  //
  // @param scc: strongly connected components represented by two nested containers
  //
  template <class VV>
  inline void printSCC(const VV& scc) {
    for (auto i=scc.begin(); i != scc.end(); ++i) {
      for (auto j = (*i).begin(); j != (*i).end(); ++j) {
        std::cout << *j << " ";
      }
      std::cout << std::endl;
    }
  }

  //
  // print the elements in a 1D container
  //
  // @param container: a 1D container
  //
  template <class VV>
  inline void printContainer(const VV& container) {
    for (auto i=container.begin(); i != container.end(); ++i) {
        std::cout << *i << " ";
    }

    std::cout << std::endl;
  }

}  // namespace graph

#endif // GRAPH_GRAPH_UTILITIES_H
