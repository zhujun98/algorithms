//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_PRIM_H
#define GRAPH_PRIM_H

#include <set>

#include "breath_first_search.h"
#include "../graph.h"
#include "../ud_graph.h"


//
// Comparator for edge: greater
//
template <class T>
struct edgeGreater {
  // <weight, <from vertex, to vertex>>
  typedef std::pair<double, std::pair<T, T>> graph_edge;

  bool operator()(const graph_edge& e1, const graph_edge& e2) {
    return e1.first > e2.first;
  }
};


//
// Implementation of the Prim's minimum spanning tree algorithm
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
prim(const UdGraph<T>& graph, int source_index = 0) {

  auto bfs_search = breathFirstSearch(graph, graph.indexToValue(source_index));

  if ( bfs_search.size() != graph.size() ) {
    throw std::invalid_argument("Input graph is not connected!");
  }

  // <weight, <tail vertex, head vertex>>
  typedef std::pair<double, std::pair<T, T>> graph_edge;

  // Minimum spanning tree:
  // Store the <from, to> vertices of edges (leaves) in the minimum
  // spanning tree in sequence, where "from" is the vertex in the
  // processed vertices set while "to" is the vertex in the
  // un-processed (remain) vertices set.
  std::vector<std::pair<T, T>> mst;
  double cost = 0.0;  // total cost of the minimum spanning tree
  // A set which records processed vertices.
  std::set<T> processed;
  // A min priority queue store the graph edge information
  std::priority_queue<graph_edge, std::vector<graph_edge>, edgeGreater<T>> remain;

  T source_vertex_value = graph.indexToValue(source_index);
  processed.insert(source_vertex_value);

  // Initialize the priority queue.
  graph::Edge<T>* current_edge = graph.getVertex(source_vertex_value)->next;
  while ( current_edge ) {
    remain.push(std::make_pair(current_edge->weight,
                               std::make_pair(source_vertex_value,
                                              current_edge->value)));
    current_edge = current_edge->next;
  }

  // Run until there is no vertex in the remain set or all the vertices
  // have been processed.
  while ( (processed.size() < graph.size()) && !remain.empty() ) {
    graph_edge pick = remain.top();
    remain.pop();
    auto insertion = processed.insert(pick.second.second);
    // Skip if it is an old copy of a processed vertex left in the
    // priority queue
    if ( !insertion.second ) { continue; }

    mst.push_back(pick.second);
    cost += pick.first;

    // New edges due to one vertex is moved from the unprocessed
    // vertices set to the processed vertices set. We do not need
    // to remove the edges which are consist of two processed
    // vertices but are still in the remain set, since we can
    // screen it out when it pops out.
    current_edge = graph.getVertex(pick.second.second)->next;
    while ( current_edge ) {
      remain.push(std::make_pair(current_edge->weight,
                                 std::make_pair(pick.second.second,
                                                current_edge->value)));
      current_edge = current_edge->next;
    }
  }

  return std::make_pair(cost, mst);
}

//
// Appointing a source vertex in Prim's algorithm
//
template <class T>
inline std::pair<double, std::vector<std::pair<T, T>>>
prim(const UdGraph<T>& graph, T source) {
  return prim(graph, graph.valueToIndex(source));
}


#endif //GRAPH_PRIM_H