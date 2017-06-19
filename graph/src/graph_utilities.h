//
// Created by jun on 6/19/17.
//

#ifndef GRAPH_GRAPH_UTILITIES_H
#define GRAPH_GRAPH_UTILITIES_H

#include <iostream>

#include "graph_adj.h"


//
// copy a graph
//
// @param graph: original graph (could be directed or undirected)
//
// @param return: copied graph
//
template <class G>
inline G copyGraph(const G& graph) {
  int g_size = graph.size();
  G copy(g_size);

  for(int i=0; i<g_size; ++i) {
    graph::AdjListNode* current = graph.getList(i).head;
    while ( current ) {
      copy.connect(i, current->value);
      current = current->next;
    }
  }

  return copy;
}

//
// reverse a directed graph
//
// @param graph: original graph
//
// @param return: reversed graph
//
inline GraphAdj reverseGraph(const GraphAdj& graph) {
  int g_size = graph.size();
  GraphAdj reversed(g_size);

  for (int i=0; i<g_size; ++i) {
    graph::AdjListNode* current = graph.getList(i).head;
    while ( current ) {
      reversed.connect(current->value, i);
      current = current->next;
    }
  }

  return reversed;
}


#endif //GRAPH_GRAPH_UTILITIES_H
