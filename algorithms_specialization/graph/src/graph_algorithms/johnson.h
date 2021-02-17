//
// Created by jun on 8/30/17.
//

#ifndef GRAPH_JOHNSON_H
#define GRAPH_JOHNSON_H

#include <iostream>
#include <deque>
#include <limits>

#include "../directed_graph.h"
#include "bellman_ford.h"
#include "dijkstra.h"


/**
 * Johnson's all-pair shorted path algorithm
 *
 * Time complexity O(EVlogV)
 *
 * @param graph: a directed graph
 * @return: a pair of two 2D deques: the first one stores the smallest
 *          cost between each pair of vertices; the second one stores
 *          the previous vertex of each vertex in the shortest path.
 */
template <class T>
std::pair<std::deque<std::deque<T>>, std::deque<std::deque<size_t>>>
johnson(DirectedGraph<T>& graph) {
  const auto kINF = (T) (std::numeric_limits<T>::max() / 2.0);

  // Add a new vertex and run Bellman Ford once
  graph.increaseVertex();

  for (size_t i=0; i<graph.size() - 1; ++i) {
    graph.connect(graph.size() - 1, i, (T)0);
  }

  auto result = bellmanFord(graph, graph.size() - 1);

  // re-weight the graph
  for (size_t i=0; i<graph.size() - 1; ++i) {
    for (size_t j=0; j<graph.size() - 1; ++j) {
      graph.increaseWeight(i, j, result.first[i] - result.first[j]);
    }
  }

  // delete the new vertex and run Dijkstra's algorithm for each vertex
  graph.decreaseVertex();

  // TODO:: implement reconstruction
  std::deque<std::deque<size_t>> came_from;
  std::deque<std::deque<T>> costs;
  for (size_t i=0; i<graph.size(); ++i) {
    std::pair<std::deque<T>, std::deque<size_t>> result_i = dijkstra(graph, i);
    costs.push_back(result_i.first);
  }

  // re-weight the graph (recover the original cost)
  for (size_t i=0; i<graph.size(); ++i) {
    for (size_t j=0; j<graph.size(); ++j) {
      costs[i][j] += result.first[j] - result.first[i];
    }
  }

  return std::make_pair(costs, came_from);
}


#endif //GRAPH_JOHNSON_H