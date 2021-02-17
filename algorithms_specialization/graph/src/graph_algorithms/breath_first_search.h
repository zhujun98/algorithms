//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_BREATH_FIRST_SEARCH_H
#define GRAPH_BREATH_FIRST_SEARCH_H

#include <vector>

#include "../graph.h"


/**
 * Breadth-first-search (DFS) starting from a vertex
 *
 * @param graph: graph object
 * @param src: the source vertex
 * @return: a vector of visited vertices, ordered by finding time
 */
template <class T>
std::vector<size_t> breathFirstSearch(const Graph<T>& graph, size_t src) {
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: src");
  }

  // the container for visited vertices in finding sequence
  std::vector<size_t> search;

  std::queue<size_t> track;
  std::vector<bool> visited (graph.size(), false);

  track.push(src);
  search.push_back(src);
  visited[src] = true;
  while (!track.empty()) {
    graph::Edge<T>* current_edge = graph.getList(track.front());
    track.pop();
    // find all children vertices which have not been visited yet
    while (current_edge) {
      if ( !visited[current_edge->dst] ) {
        track.push(current_edge->dst);
        search.push_back(current_edge->dst);
        visited[current_edge->dst] = true;
      }
      current_edge = current_edge->next;
    }
  }

  return search;
}

#endif //GRAPH_BREATH_FIRST_SEARCH_H
