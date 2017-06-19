//
// Created by jun on 6/5/17.
//
// Test the Karger's random contraction algorithm on a graph represented
// by adjacency list.
//
#ifndef GRAPH_KARGER_H
#define GRAPH_KARGER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>

#include "graph_adj.h"

//
// contract an undirected graph until only two non-empty linked lists remain
//
// @param graph: UnGraphAdj object
//
// @return: number of edges in the contracted graph
//
inline int graphContract(UdGraphAdj& graph, bool display=false) {

  /* Distribution on which to apply the generator */
  std::vector<int> nonEmptyVertex = graph.getNonEmptyList();

  std::random_device rd;
  std::default_random_engine generator(rd());
  while ( nonEmptyVertex.size() > 2 ) {
    std::uniform_int_distribution<long unsigned> distribution(0, 10000000);
    unsigned long first = distribution(generator) % graph.getNonEmptyList().size();
    unsigned long second = distribution(generator) % (graph.getNonEmptyList().size() - 1);
    if (second >= first) { ++second; }

    if ( display ) {
      std::cout << nonEmptyVertex[first] << " " << nonEmptyVertex[second] << std::endl;
    }
    graph.collapse(nonEmptyVertex[first], nonEmptyVertex[second]);

    nonEmptyVertex = graph.getNonEmptyList();
    if ( display) { graph.display(); }
  }

  return graph.countEdge();
}

//
// test the graph and the implementation of the Karger's mini-cut algorithm
//
// @param n: number of random contractions.
//
inline void karger(const UdGraphAdj& graph, int n) {

  int min_cut = 100;
  int cut;

  // apply Karger's algorithm to find the minimum cut in the graph
  for (int i=0; i<n; ++i) {
    UdGraphAdj copy = copyGraph(graph);

    cut = graphContract(copy);
    if ( cut < min_cut ) { min_cut = cut; }
  }
  std::cout << "\nthe minimum cut is " << min_cut << std::endl;
}

#endif //GRAPH_KARGER_H