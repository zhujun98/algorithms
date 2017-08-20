//
// Created by jun on 8/20/17.
//

#ifndef GRAPH_BELLMAN_FORD_H
#define GRAPH_BELLMAN_FORD_H

#include <iostream>
#include <vector>
#include <limits>

#include "../graph.h"


//
// implementation of the Bellman-Ford's shorted path algorithm
//
// Time complexity O(EV)
//
// @param graph: a directed graph
// @param src: the starting vertex value
//
// @param return: a vector containing a pair of the shortest distance
//                between each vertex to the source as well as the
//                parent vertex of each vertex in the shortest path.
//
template <class G, class T>
std::vector<std::pair<double, T>> bellmanFord(const G& graph, T src) {
  if ( !graph.getVertex(src) ) {
    std::cout << src << " is not a vertex of the graph!" << std::endl;
    return {};
  }
  int src_index = graph.valueToIndex(src);

  // Store the shortest distance and its parent vertex (index) for each vertex
  std::vector<std::pair<double, T>> distances(graph.size());
  for ( int i=0; i < graph.size(); ++i ) {
    if ( i != src_index ) {
      distances[i].first = kMaxDistance;
      // parent vertex is not initialized
    } else {
      distances[i].first = 0;
      distances[i].second = src;
    }
  }

  for ( int i=0; i < graph.size() - 1; ++i ) {
    for ( int edge_src=0; edge_src < graph.size(); ++edge_src ) {
      graph::Edge<T> *current_edge = graph.getVertexByIndex(edge_src)->next;
      while ( current_edge ) {
        int edge_dst = graph.valueToIndex(current_edge->value);

        if ( std::abs(distances[edge_src].first - kMaxDistance) > 1e-6 &&
             distances[edge_dst].first > distances[edge_src].first + current_edge->weight) {
          distances[edge_dst].first = distances[edge_src].first + current_edge->weight;
          distances[edge_dst].second = graph.indexToValue(edge_src);
        }

        current_edge = current_edge->next;
      }
    }
  }

  return distances;
}


#endif //GRAPH_BELLMAN_FORD_H