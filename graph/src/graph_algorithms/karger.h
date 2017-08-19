//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_KARGER_H
#define GRAPH_KARGER_H

#include <random>
#include <vector>

#include "../ud_graph.h"


//
// contract an undirected graph until only two non-empty linked lists remain
//
// @param graph: an undirected graph
//
// @return: the number of edges in the contracted graph
//
template <class T>
inline int graphContract(UdGraph<T>& graph, bool display=false) {

  // Distribution on which to apply the generator
  std::vector<T> connected_vertices = graph.getConnectedVertices();

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

  return int(graph.countWeightedEdge());
}


//
// implementation of the Karger's mini-cut algorithm on an undirected graph
//
// @param n: the number of random contractions
//
// @return: the number of min cut
//
template <class T>
inline int karger(const UdGraph<T>& graph, unsigned int n) {

  int min_cut = graph.countWeightedEdge();
  int cut;

  // apply Karger's algorithm to find the minimum cut in the graph
  for (int i = 0; i < n; ++i) {
    UdGraph<T> graph_copy(graph);

    cut = graphContract(graph_copy);
    if (cut < min_cut) { min_cut = cut; }
  }

  return min_cut;
}


#endif //GRAPH_KARGER_H