//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_DIJKSTRA_H
#define GRAPH_DIJKSTRA_H

#include <vector>
#include <limits>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>

#include "../directed_graph.h"
#include "../undirected_graph.h"


/**
 * Reconstruct the shortest path from the search result
 *
 * @param came_from: a vector that stores the previous vertex of each
 *                   vertex in the shortest path
 * @param src: source vertex
 * @param dst: destination vertex
 * @return: a 1D vector similar to elevation and overrides with the
 *          point in the shortest path marked "true".
 */
std::deque<size_t>
reconstructPath(const std::deque<size_t>& came_from, size_t src, size_t dst) {
  std::deque<size_t> path;

  size_t prev_vertex = dst;
  size_t count = 0;
  while (++count < came_from.size()) {
    path.push_front(prev_vertex);
    prev_vertex = came_from[prev_vertex];
    if (prev_vertex == src) {
      path.push_front(src);
      break;
    }
  }

  return path;
}

/**
 * Implementation of the original Dijkstra's algorithm
 *
 * Time complexity O(V^2). Used for dense graph.
 *
 * @param graph: a directed/undirected graph
 * @param src: source vertex
 * @param dst: destination vertex
 * @return: two deque containers. The first one stores the shortest
 *          distance from each vertex to the source; the second one
 *          stores the previous vertex of each vertex in the shortest
 *          path.
 */
template <class T>
std::pair<std::deque<T>, std::deque<size_t>>
dijkstraOriginal(const Graph<T>& graph, size_t src, size_t dst) {
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: source");
  }
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: destination");
  }

  T kMaxCost = (T)(std::numeric_limits<T>::max()/2.0);

  // actual minimum cost to the source so far
  std::deque<T> costs(graph.size(), kMaxCost);
  // the previous point that allows to achieve the minimum cost so far
  std::deque<size_t> came_from(graph.size());
  // explored vertex will be marked true
  std::deque<bool> explored(graph.size(), false);

  costs[src] = 0;
  came_from[src] = src;
  // Loop over the rest vertices
  for (size_t count = 0; count < graph.size() - 1; ++count) {
    // pick the unexplored vertex with the minimum cost
    auto min_cost = kMaxCost;
    size_t pick = 0;
    for (size_t i = 0; i < costs.size(); ++i) {
      if (!explored[i] && costs[i] < min_cost) {
        min_cost = costs[i];
        pick = i;
      }
    }
    explored[pick] = true;

    // stop search when reaching the destination
    if (src != dst && pick == dst) {
      return std::make_pair(costs, came_from);
    }

    // Loop the neighbors of the picked vertex
    graph::Edge<T> *current_edge = graph.getList(pick);
    while (current_edge) {
      if (current_edge->weight < 0) {
        std::cerr << "Graph has negative weight! Result could be wrong!" << std::endl;
      }

      auto vertex = current_edge->dst;
      T new_cost = costs[pick] + current_edge->weight;
      if (costs[vertex] > new_cost) {
        costs[vertex] = new_cost;
        came_from[vertex] = pick;
      }

      current_edge = current_edge->next;
    }
  }

  if (src != dst) {
    throw std::invalid_argument(
        "Invalid argument: source and destination are not connected!");
  }

  // if no destination is specified
  return std::make_pair(costs, came_from);
}

/**
 * RB-tree implementation of Dijkstra's algorithm
 *
 * Time complexity O(ElogV)
 *
 * @param graph: a directed/undirected graph
 * @param src: source vertex
 * @param dst: destination vertex
 * @return: two deque containers. The first one stores the shortest
 *          distance from each vertex to the source; the second one
 *          stores the previous vertex of each vertex in the shortest
 *          path.
 */
template <class T>
std::pair<std::deque<T>, std::deque<size_t>>
dijkstraTreeBase(const Graph<T>& graph, size_t src, size_t dst) {
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: source");
  }
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: destination");
  }

  T kMaxCost = (T)(std::numeric_limits<T>::max()/2.0);

  // A set of vertices <current smallest cost, destination index>
  std::set<std::pair<T, size_t>> open_set;
  // actual minimum cost to the source so far
  std::deque<T> costs(graph.size(), kMaxCost);
  // the previous point that allows to achieve the minimum cost so far
  std::deque<size_t> came_from(graph.size());

  costs[src] = 0;
  came_from[src] = src;

  open_set.insert(std::make_pair(0, src));
  // Run until there is no vertex left in the remain set.
  while (!open_set.empty()) {
    // Pick the one in the open set with the smallest cost.
    auto pick = open_set.begin()->second;
    open_set.erase(open_set.begin());

    // stop search when reaching the destination
    if (src != dst && pick == dst) {
      return std::make_pair(costs, came_from);
    }

    // Loop the neighbors of the picked vertex
    graph::Edge<T> *current_edge = graph.getList(pick);
    while (current_edge) {
      if (current_edge->weight < 0) {
        std::cerr << "Graph has negative weight! Result could be wrong!" << std::endl;
      }

      auto vertex = current_edge->dst;
      T new_cost = costs[pick] + current_edge->weight;
      if (costs[vertex] > new_cost) {
        open_set.erase(std::make_pair(costs[vertex], vertex));
        costs[vertex] = new_cost;
        came_from[vertex] = pick;
        open_set.insert(std::make_pair(costs[vertex], vertex));
      }

      current_edge = current_edge->next;
    }
  }

  if (src != dst) {
    throw std::invalid_argument(
        "Invalid argument: source and destination are not connected!");
  }

  // if no destination is specified
  return std::make_pair(costs, came_from);
}

/**
 * Priority queue implementation of Dijkstra's algorithm
 *
 * Time complexity O(ElogV)
 *
 * @param graph: a directed/undirected graph
 * @param src: source vertex
 * @param dst: destination vertex
 * @return: two deque containers. The first one stores the shortest
 *          distance from each vertex to the source; the second one
 *          stores the previous vertex of each vertex in the shortest
 *          path.
 */
template <class T>
std::pair<std::deque<T>, std::deque<size_t>>
dijkstraPriorityQueueBase(const Graph<T>& graph, size_t src, size_t dst) {
  if ( src < 0 || src >= graph.size() ) {
    throw std::out_of_range("Out of range: source");
  }
  if ( dst < 0 || dst >= graph.size() ) {
    throw std::out_of_range("Out of range: destination");
  }

  T kMaxCost = (T)(std::numeric_limits<T>::max()/2.0);

  // The first element is the cost from source to the current
  // vertex; the second element is the current vertex.
  std::priority_queue<std::pair<T, size_t>,
      std::vector<std::pair<T, size_t>>,
      std::greater<std::pair<T, size_t>>> open_set;

  // actual minimum cost to the source so far
  std::deque<T> costs(graph.size(), kMaxCost);
  // the previous point that allows to achieve the minimum cost so far
  std::deque<size_t> came_from(graph.size());
  // mark the explored point (another way to screen the old copies)
//  std::deque<bool> explored(graph.size(), false);

  // initialization
  costs[src] = 0;
  came_from[src] = src;

  // Run until there is no points left in the open set.
  open_set.push(std::make_pair(0, src));
  while (!open_set.empty()) {
    // Pick the point in the open set with the smallest cost.
    auto pick = open_set.top();
    open_set.pop();

    // stop search when reaching the destination
    if (src != dst && pick.second == dst) {
      return std::make_pair(costs, came_from);
    }

    // skip the old copies in the open set
//    if (explored[pick.second]) { continue; }
//    explored[pick.second] = true;
    if (pick.first > costs[pick.second]) { continue; }

    graph::Edge<T> *current_edge = graph.getList(pick.second);
    // Loop the neighbors of the picked vertex
    while (current_edge) {
      if ( current_edge->weight < 0 ) {
        std::cerr << "Graph has negative weight! Result could be wrong!" << std::endl;
      }

      auto vertex = current_edge->dst;
      // It is unnecessary to find and remove the old copy here since it
      // can be screened out later.
      T new_cost = costs[pick.second] + current_edge->weight;
      if (costs[vertex] > new_cost) {
        costs[vertex] = new_cost;
        came_from[vertex] = pick.second;
        open_set.push(std::make_pair(new_cost, vertex));
      }
      current_edge = current_edge->next;
    }
  }

  if (src != dst) {
    throw std::invalid_argument(
        "Invalid argument: source and destination are not connected!");
  }

  // if no destination is specified
  return std::make_pair(costs, came_from);
}

//
// Explore the entire graph using dijkstra's algorithm
//
template <class T>
std::pair<std::deque<T>, std::deque<size_t>>
dijkstra(const Graph<T>& graph, size_t src) {
  return dijkstraPriorityQueueBase(graph, src, src);
}

//
// Explore the graph until reaching the destination vertex
//
template <class T>
std::pair<std::deque<T>, std::deque<size_t>>
dijkstra(const Graph<T>& graph, size_t src, size_t dst) {
  return dijkstraPriorityQueueBase(graph, src, dst);
}

#endif //GRAPH_DIJKSTRA_H