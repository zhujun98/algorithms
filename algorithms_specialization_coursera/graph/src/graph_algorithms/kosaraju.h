//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_KOSARAJU_H
#define GRAPH_KOSARAJU_H

#include <deque>

#include "../directed_graph.h"
#include "depth_first_search.h"


/**
 * Kosaraju's algorithm to find the strongly connected components (SCC)
 *
 * @param graph: a directed graph
 * @return: the strongly connected components
 */
template <class T>
std::deque<std::deque<size_t>> kosaraju(DirectedGraph<T>& graph) {
  std::deque<std::deque<size_t>> scc;

  // First pass, recursively run DFS on the original graph.
  // The finish time of each vertex will be store in a stack
  graph.reverse();

  std::vector<bool> visited (graph.size(), false);
  std::stack<size_t> finish_time;
  for (std::size_t i = 0; i < graph.size(); ++i) {
    if (!visited[i]) {
      std::vector<size_t> search = depthFirstSearch(graph, i, visited);
      for ( auto j=0; j < search.size(); ++j) {
        finish_time.push(search[j]);
      }
    }
  }

  // Second pass, recursively run DFS using each vertex stored in
  // the stack. The last finished vertex will be tracked first!
  graph.reverse();

  std::vector<bool> reversed_visited (graph.size(), false);
  while (!finish_time.empty()) {
    if (!reversed_visited[finish_time.top()]) {
      std::vector<size_t> search = depthFirstSearch(
          graph, finish_time.top(), reversed_visited);
      std::deque<size_t> sub_scc {search.begin(), search.end()};
      scc.push_back(sub_scc);
    }
    finish_time.pop();
  }

  return scc;
}


#endif //GRAPH_KOSARAJU_H