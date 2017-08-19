//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_BREATH_FIRST_SEARCH_H
#define GRAPH_BREATH_FIRST_SEARCH_H

#include <vector>

#include "../graph.h"


//
// Breath-first-search (BFS) starting from a vertex
//
// @param graph: graph object
// @param vertex: the starting vertex value
//
// @return: a vector of visited vertices, ordered by finding time
//
template <class G, class T>
std::vector<T> breathFirstSearch(const G& graph, T value) {
  graph::Vertex<T> const* v = graph.getVertex(value);
  if ( !v ) { return {}; }

  // the container for visited vertices in finding sequence
  std::vector<T> search;
  std::queue<T> track;
  std::vector<bool> visited (graph.size(), false);

  track.push(value);
  search.push_back(value);
  visited[graph.valueToIndex(value)] = true;
  while (!track.empty()) {
    graph::Vertex<T> const* current_head = graph.getVertex(track.front());
    track.pop();

    graph::Edge<T>* current_node = current_head->next;
    // find all children vertices which have not been visited yet
    while (current_node) {
      if ( !visited[graph.valueToIndex(current_node->value)] ) {
        track.push(current_node->value);
        search.push_back(current_node->value);
        visited[graph.valueToIndex(current_node->value)] = true;
      }
      current_node = current_node->next;
    }
  }

  return search;
}

#endif //GRAPH_BREATH_FIRST_SEARCH_H
