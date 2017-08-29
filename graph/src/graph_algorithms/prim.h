//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_PRIM_H
#define GRAPH_PRIM_H

#include "breath_first_search.h"
#include "../undirected_graph.h"


/**
 * The original Prim's minimum spanning tree algorithm
 *
 * Time complexity O(V^2)
 *
 * @param graph: undirected graph
 * @param src: source vertex
 * @return: a pair with the first element being the total cost of the
 *          minimum spanning tree and the second one being a vector of
 *          the leaves (<from vertex, to vertex>) in the tree in sequence.
 */
template <class T>
std::pair<T, std::vector<std::pair<size_t, size_t>>>
prim_dense(const UndirectedGraph<T>& graph, size_t src) {

  auto bfs_search = breathFirstSearch(graph, src);
  if ( bfs_search.size() != graph.size() ) {
    throw std::invalid_argument("Input graph is not connected!");
  }

  // Minimum spanning tree:
  // Store the edges (src->dst) in the minimum spanning tree in sequence,
  // where "src" is the vertex in the processed vertices set while "dst"
  // is the vertex in the un-processed vertices set.
  std::vector<std::pair<size_t, size_t>> mst;
  T cost = 0.0;  // total cost of the minimum spanning tree

  // An indicator
  std::vector<bool> processed(graph.size());
  processed[src] = true;

  // Loop over the rest vertices
  for (size_t count = 0; count < graph.size() - 1; ++count) {
    // TODO:: implement
  }

  return {};
}

// comparator
struct edgeGreater {
  // <weight, <from vertex index, to vertex index>>
  typedef std::pair<double, std::pair<int, int>> graph_edge;

  bool operator()(const graph_edge& e1, const graph_edge& e2) {
    return e1.first > e2.first;
  }
};

/**
 * The Prim's minimum spanning tree algorithm implemented with
 * priority queue.
 *
 * Time complexity O(ElogV)
 *
 * @param graph: undirected graph
 * @param src: source vertex
 * @return: a pair with the first element being the total cost of the
 *          minimum spanning tree and the second one being a vector of
 *          the leaves (<from vertex, to vertex>) in the tree in sequence.
 */
template <class T>
std::pair<T, std::vector<std::pair<size_t, size_t>>>
prim(const UndirectedGraph<T>& graph, size_t src) {

  auto bfs_search = breathFirstSearch(graph, src);
  if ( bfs_search.size() != graph.size() ) {
    throw std::invalid_argument("Input graph is not connected!");
  }

  // Minimum spanning tree:
  // Store the edges (src->dst) in the minimum spanning tree in sequence,
  // where "src" is the vertex in the processed vertices set while "dst"
  // is the vertex in the un-processed vertices set.
  std::vector<std::pair<size_t, size_t>> mst;
  T cost = 0.0;  // total cost of the minimum spanning tree

  // <weight, <src, dst>>
  typedef std::pair<T, std::pair<size_t, size_t>> graph_edge;
  // A min priority queue store the graph edge information
  std::priority_queue<graph_edge, std::vector<graph_edge>, edgeGreater> unprocessed;

  // An indicator
  std::vector<bool> processed(graph.size());
  processed[src] = true;

  // Initialize the priority queue.
  graph::Edge<T>* current_edge = graph.getList(src);
  while ( current_edge ) {
    unprocessed.push(std::make_pair(
        current_edge->weight,
        std::make_pair(src, current_edge->dst)));
    current_edge = current_edge->next;
  }

  // Run until there is no vertex in the unprocessed set
  // or all the vertices have been processed (for speed).
  while ( mst.size() < graph.size() && !unprocessed.empty() ) {
    graph_edge pick = unprocessed.top();
    unprocessed.pop();

    // Skip old copies of a processed vertex left in the priority queue.
    // It ensures that each vertex will only be processed once!
    if (processed[pick.second.second]) { continue; }
    processed[pick.second.second] = true;

    mst.push_back(pick.second);
    cost += pick.first;

    current_edge = graph.getList(pick.second.second);
    // Since each edge will only be visited once, so the total time
    // complexity of the two loops is only O(E)
    while ( current_edge ) {
      unprocessed.push(std::make_pair(
          current_edge->weight,
          std::make_pair(pick.second.second, current_edge->dst)));

      current_edge = current_edge->next;
    }
  }

  return std::make_pair(cost, mst);
}


#endif //GRAPH_PRIM_H