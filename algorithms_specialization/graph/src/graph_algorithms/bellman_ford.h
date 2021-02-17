//
// Created by jun on 8/20/17.
//

#ifndef GRAPH_BELLMAN_FORD_H
#define GRAPH_BELLMAN_FORD_H

#include <iostream>
#include <vector>
#include <limits>

#include "../directed_graph.h"


/**
 * Bellman-Ford's shorted path algorithm
 *
 * Time complexity O(VE)
 *
 * @param graph: a directed graph
 * @param src: the source vertex
 * @return: a pair of two deques: the first one stores the smallest
 *          cost of each vertex; the second one stores the previous
 *          vertex of each vertex in the shortest path.
 */
template <class T>
std::pair<std::deque<T>, std::deque<size_t>>
bellmanFord(const DirectedGraph<T>& graph, size_t src) {
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: source");
  }

  T kMaxCost = (T)(std::numeric_limits<T>::max()/2.0);

  // actual minimum cost to the source so far
  std::deque<T> costs(graph.size(), kMaxCost);
  // the previous point that allows to achieve the minimum cost so far
  std::deque<size_t> came_from(graph.size());

  costs[src] = 0;
  came_from[src] = src;

  // If there is no negative directed cycle, the minimum path from vertex
  // u to v will contain at most [V - 1] edges.
  for (size_t count = 0; count < graph.size() - 1; ++count) {
    for (size_t edge_src=0; edge_src < graph.size(); ++edge_src) {
      graph::Edge<T>* current_edge = graph.getList(edge_src);
      while (current_edge != nullptr) {
        size_t edge_dst = current_edge->dst;

        T new_cost = costs[edge_src] + current_edge->weight;
        if (costs[edge_dst] > new_cost) {
          costs[edge_dst] = new_cost;
          came_from[edge_dst] = edge_src;
        }

        current_edge = current_edge->next;
      }
    }
  }

  // check negative cycles
  for (size_t edge_src=0; edge_src < graph.size(); ++edge_src) {
    graph::Edge<T>* current_edge = graph.getList(edge_src);
    while (current_edge != nullptr) {
      T weight = current_edge->weight;

      if (costs[edge_src] + weight < costs[current_edge->dst]) {
        throw std::invalid_argument("Found negative cycle in the graph!");
      }

      current_edge = current_edge->next;
    }
  }

  return std::make_pair(costs, came_from);
}

#endif //GRAPH_BELLMAN_FORD_H