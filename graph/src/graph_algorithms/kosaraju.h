//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_KOSARAJU_H
#define GRAPH_KOSARAJU_H

#include <vector>

#include "../graph.h"
#include "depth_first_search.h"


//
// Apply the Kosaraju's algorithm to find the strongly connected components (SCC)
//
// @param graph: a directed graph
//
// @return: the strongly connected components
//
template <class T>
inline std::vector<std::vector<T>> kosaraju(Graph<T>& graph) {
  std::vector<std::vector<T>> scc;
  // reverse the directed graph
  Graph<T> graph_reversed = graph::reverseGraph(graph);

  //
  // First pass, recursively run DFS on the original graph.
  // The finish time of each vertex will be store in a stack
  //
  std::vector<bool> visited (graph.size(), false);
  std::stack<T> finish_time;
  for (std::size_t i = 0; i < graph.size(); ++i) {
    if (!visited[i]) {
      std::vector<T> search = depthFirstSearch(graph, graph.indexToValue(i), visited);
      for ( auto j=0; j < search.size(); ++j) {
        finish_time.push(search[j]);
      }
    }
  }

  //
  // Second pass, recursively run DFS using each vertex stored in
  // the stack. The last finished vertex will be tracked first!
  //
  std::vector<bool> reversed_visited (graph_reversed.size(), false);
  while (!finish_time.empty()) {
    if (!reversed_visited[graph_reversed.valueToIndex(finish_time.top())]) {
      std::vector<T> search = depthFirstSearch(
          graph_reversed, finish_time.top(), reversed_visited);
      scc.push_back(search);
    }
    finish_time.pop();
  }

  return scc;
}


#endif //GRAPH_KOSARAJU_H