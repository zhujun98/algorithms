//
// Created by jun on 8/31/17.
//

#ifndef GRAPH_FLOYD_WARSHALL_H
#define GRAPH_FLOYD_WARSHALL_H

#include <iostream>
#include <deque>
#include <limits>

#include "../directed_graph.h"

/**
 * Floyd-Warshall's all-pair shorted path algorithm
 *
 * Time complexity O(V^3)
 *
 * @param graph: a directed graph
 * @return: a pair of two 2D deques: the first one stores the smallest
 *          cost between each pair of vertices; the second one stores
 *          the previous vertex of each vertex in the shortest path.
 */
template <class T>
std::pair<std::deque<std::deque<T>> , std::deque<std::deque<size_t>>>
floydWarshall(const DirectedGraph<T>& graph) {
  const auto kINF = (T)(std::numeric_limits<T>::max()/2.0);

  // initialization
  std::deque<std::deque<T>>
      costs(graph.size(), std::deque<T>(graph.size(), kINF));
  for (size_t i=0; i<graph.size(); ++i) {
    costs[i][i] = (T)0;

    graph::Edge<T>* current_edge = graph.getList(i);
    while (current_edge != nullptr) {
      costs[i][current_edge->dst] = current_edge->weight;
      current_edge = current_edge->next;
    }
  }

  // TODO:: implement reconstruction
  std::deque<std::deque<size_t>>
      came_from(graph.size(), std::deque<size_t>(graph.size()));

  // dynamic programming of Floyd-Marshall's algorithm
  for (size_t k = 0; k < graph.size(); ++k) {
    for (size_t i = 0; i < graph.size(); ++i) {
      for (size_t j = 0; j < graph.size(); ++j) {
        // avoid doing math on the defined INF, which may cause bugs
        if (std::abs(kINF - costs[i][k]) > std::numeric_limits<T>::epsilon() &&
            std::abs(kINF - costs[k][j]) > std::numeric_limits<T>::epsilon() ) {
          T new_cost = costs[i][k] + costs[k][j];
          if (new_cost < costs[i][j]) { costs[i][j] = new_cost; }
        }
      }
    }
  }

  // test negative cycle
  for (size_t i = 0; i < graph.size(); ++i) {
    if (costs[i][i] < 0) {
      throw std::invalid_argument("Found negative cycle in the graph!");
    }
  }

  return std::make_pair(costs, came_from);
};


#endif //GRAPH_FLOYD_WARSHALL_H