//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_DEPTH_FIRST_SEARCH_H
#define GRAPH_DEPTH_FIRST_SEARCH_H

#include <vector>

#include "../graph.h"


//
// Depth-first-search (DFS) starting from a vertex
//
// @param graph: graph object
// @param value: starting vertex value
// @param visited: An indicator which indicates whether a vertex has
//                 been visited.
//
// @return: a vector of sink vertices, ordered by finding time
//
template <class G, class T>
std::vector<T> depthFirstSearch(const G& graph, T value, std::vector<bool>& visited) {
  assert( graph.size() == visited.size() );

  graph::Vertex<T> const* v = graph.getVertex(value);
  if ( !v ) { return {}; }

  // the container for sink vertices in finding sequence
  std::vector<T> sink;
  std::stack<T> tracker;

  tracker.push(value);
  T current_vertex_value;
  // search the vertex reachable from the current vertex
  while ( !tracker.empty() ) {
    current_vertex_value = tracker.top();
    visited[graph.valueToIndex(current_vertex_value)] = true;

    bool retreat = true;  // a flag indicating whether to retreat to the last vertex
    graph::Edge<T>* current_node = graph.getVertex(current_vertex_value)->next;
    // find the next reachable vertex which has not been visited
    while ( current_node ) {
      if ( !visited[graph.valueToIndex(current_node->value)] ) {
        tracker.push(current_node->value);
        retreat = false;
        break;
      }
      current_node = current_node->next;
    }
    // if a sink vertex is found
    if ( retreat ) {
      sink.push_back(current_vertex_value);
      tracker.pop();
    }

  }

  return sink;
}


//
// Use internal generated indicator for depth-first-search
//
template <class G, class T>
std::vector<T> depthFirstSearch(const G& graph, T value) {
  std::vector<bool> visited (graph.size(), false);
  return depthFirstSearch(graph, value, visited);
}


#endif //GRAPH_DEPTH_FIRST_SEARCH_H