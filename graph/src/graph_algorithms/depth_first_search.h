//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_DEPTH_FIRST_SEARCH_H
#define GRAPH_DEPTH_FIRST_SEARCH_H

#include <vector>

#include "../graph.h"


/**
 * Depth-first-search (DFS) starting from a vertex
 *
 * @param graph: graph object
 * @param src: source vertex
 * @param visited: indicator
 * @return: a vector of sink vertices, ordered by finding time
 */
template <class T>
std::vector<size_t> depthFirstSearch(const Graph<T>& graph, size_t src,
                                     std::vector<bool>& visited) {
  if (graph.size() != visited.size()) {
    throw std::invalid_argument("Invalid argument: different sizes of graph and indicator");
  }

  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: src");
  }

  // the container for sink vertices in finding sequence
  std::vector<size_t> sink;

  std::stack<size_t> tracker;
  tracker.push(src);
  visited[src] = true;

  while ( !tracker.empty() ) {
    graph::Edge<T>* current_edge = graph.getList(tracker.top());
    // find the next reachable vertex which has not been visited
    while (current_edge) {
      if (!visited[current_edge->dst]) {
        visited[current_edge->dst] = true;
        tracker.push(current_edge->dst);
        current_edge = graph.getList(current_edge->dst);
      } else {
        current_edge = current_edge->next;
      }
    }
    // if a sink vertex is found
    auto vertex = tracker.top();
    sink.push_back(vertex);
    tracker.pop();
  }

  return sink;
}

//
// Use internal generated indicator for depth-first-search
//
template <class T>
std::vector<size_t> depthFirstSearch(const Graph<T>& graph, size_t src) {
  std::vector<bool> visited (graph.size(), false);
  return depthFirstSearch(graph, src, visited);
}


#endif //GRAPH_DEPTH_FIRST_SEARCH_H