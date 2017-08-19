//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_PRIM_H
#define GRAPH_PRIM_H


#include "breath_first_search.h"
#include "../graph.h"
#include "../ud_graph.h"


//
// Comparator for edge: greater
//
struct edgeGreater {
  // <weight, <from vertex index, to vertex index>>
  typedef std::pair<double, std::pair<int, int>> graph_edge;

  bool operator()(const graph_edge& e1, const graph_edge& e2) {
    return e1.first > e2.first;
  }
};


//
// Implementation of the Prim's minimum spanning tree algorithm
//
// The time complexity is O(ElogE) = O(ElogV), E <= V^2
// If decrease_key is implemented, the time complexity will become
// O(2ElogV) = O(ElogV), which is almost the same. But
// the decrease_key operation has its overhead.
//
// @param graph: undirected graph object
//
// @return: a pair in which the first element is the total cost of
//          the minimum spanning tree while the second one is a
//          vector of the leaves (<from vertex, to vertex>) in the
//          tree in sequence.
//
template <class T>
inline std::pair<double, std::vector<std::pair<T, T>>>
prim(const UdGraph<T>& graph, int src_index = 0) {

  auto bfs_search = breathFirstSearch(graph, graph.indexToValue(src_index));
  if ( bfs_search.size() != graph.size() ) {
    throw std::invalid_argument("Input graph is not connected!");
  }

  // Minimum spanning tree:
  // Store the <from, to> vertices of edges (leaves) in the minimum
  // spanning tree in sequence, where "from" is the vertex in the
  // processed vertices set while "to" is the vertex in the
  // un-processed (remain) vertices set.
  std::vector<std::pair<T, T>> mst;
  double cost = 0.0;  // total cost of the minimum spanning tree

  // <weight, <tail vertex index, head vertex index>>
  typedef std::pair<double, std::pair<int, int>> graph_edge;
  // A min priority queue store the graph edge information
  std::priority_queue<graph_edge, std::vector<graph_edge>, edgeGreater> remain;

  // An indicator. 0 for unprocessed vertex and 1 for processed vertex.
  std::vector<int> processed(graph.size());
  processed[src_index] = 1;

  // Initialize the priority queue.
  graph::Edge<T>* current_edge = graph.getVertexByIndex(src_index)->next;
  while ( current_edge ) {
    remain.push(std::make_pair(
        current_edge->weight,
        std::make_pair(src_index, graph.valueToIndex(current_edge->value))));
    current_edge = current_edge->next;
  }

  // Run until there is no vertex in the remain set or all the vertices
  // have been processed.
  int n_processed = 1;
  while ( n_processed < graph.size() && !remain.empty() ) {
    graph_edge pick = remain.top();
    remain.pop();

    // Skip if it is an old copy of a processed vertex left in the
    // priority queue. This is a critical step! It ensures that each
    // vertex will only be processed once!
    if ( processed[pick.second.second] == 1 ) {
      continue;
    } else {
      processed[pick.second.second] = 1;
      ++n_processed;
    }

    mst.push_back(std::make_pair(graph.indexToValue(pick.second.first),
                                 graph.indexToValue(pick.second.second)));
    cost += pick.first;

    // New edges due to one vertex is moved from the unprocessed
    // vertices set to the processed vertices set. We do not need
    // to remove the edges which consist of two processed
    // vertices but are still in the remain set, since we can
    // screen it out when it pops out.
    current_edge = graph.getVertexByIndex(pick.second.second)->next;
    // Since each edge will only be visited once, so the total time
    // complexity of the two loops is only O(E)
    while ( current_edge ) {
      // O(ElogE)
      remain.push(std::make_pair(
          current_edge->weight,
          std::make_pair(pick.second.second,
                         graph.valueToIndex(current_edge->value))));
      current_edge = current_edge->next;
    }
  }

  return std::make_pair(cost, mst);
}

//
// Appointing a source vertex in Prim's algorithm
//
// @param graph: undirected graph object
// @param src: source vertex value

template <class T>
inline std::pair<double, std::vector<std::pair<T, T>>>
prim(const UdGraph<T>& graph, T src) {
  return prim(graph, graph.valueToIndex(src));
}


#endif //GRAPH_PRIM_H