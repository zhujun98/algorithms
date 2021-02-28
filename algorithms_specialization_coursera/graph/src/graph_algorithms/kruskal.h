//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_KRUSKAL_H
#define GRAPH_KRUSKAL_H

#include <algorithm>

#include "breath_first_search.h"
#include "../undirected_graph.h"


// a union-find data structure composed of the head vertex of
// each union and its rank
typedef std::vector<std::pair<size_t, size_t>> union_find;

// Comparator
template <class T>
struct edgeLess {
  // <weight, <src, dst>>
  typedef std::pair<T, std::pair<size_t, size_t>> graph_edge;

  bool operator()(const graph_edge& e1, const graph_edge& e2) {
    return e1.first < e2.first;
  }
};

/**
 * Find the head vertex of a vertex.
 *
 * @param src: source vertex
 * @param union_: union-find data structure
 * @return: head vertex
 */
size_t find(size_t src, const union_find& union_) {
  size_t head(union_[src].first);
  while ( src != head ) {
    src = head;
    head = union_[src].first;
  }
  return head;
}

/**
 * Fuse the two unions by rank
 *
 * @param head1: head vertex 1
 * @param head2: head vertex 2
 * @param union_: union-find data structure
 */
void unionByRank(size_t head1, size_t head2, union_find& union_) {

  if ( union_[head1].second > union_[head2].second ) {
    union_[head2].first = union_[head1].first;
  } else {
    union_[head1].first = union_[head2].first;
    // the rank changes only when two unions have the same rank
    if ( union_[head1].second == union_[head2].second ) {
      ++union_[head2].second;
    }
  }
}


//
// Implementation of the Kruskal's minimum spanning tree algorithm
//
// Union-by-rank is implemented so the time complexity is
// O(2ElogV) = O(ElogV). However, Kruskal's algorithm is bounded by
// edge sorting, which has a time complexity of O(ElogE) = O(ElogV),
// E <= V^2.
//
// @param graph: undirected graph object
//
// @return: a pair in which the first element is the total cost of
//          the minimum spanning tree while the second one is a
//          vector of the leaves (<from vertex, to vertex>) in the
//          tree in sequence.
//
template <class T> std::pair<T, std::vector<std::pair<size_t, size_t>>>
kruskal(const UndirectedGraph<T>& graph) {
  // check the connectivity of the graph
  auto bfs_search = breathFirstSearch(graph, 0);
  if ( bfs_search.size() != graph.size() ) {
    throw std::invalid_argument("Input graph is not connected!");
  }

  // <weight, <src, dst>>
  typedef std::pair<T, std::pair<size_t, size_t>> graph_edge;
  // store all the edges in a vector
  std::vector<graph_edge> edges;
  // read out all the edges
  for ( size_t i=0; i<graph.size(); ++i ) {
    graph::Edge<T>* current_edge = graph.getList(i);
    while ( current_edge ) {
      edges.push_back(std::make_pair(
          current_edge->weight, std::make_pair(i, current_edge->dst)));
      current_edge = current_edge->next;
    }
  }
  // sort the edges in descending order
  std::sort(edges.begin(), edges.end(), edgeLess<T>());

  union_find union_;

  // initialization
  for ( size_t i=0; i<graph.size(); ++i ) {
    union_.push_back(std::make_pair(i, 0));
  }

  // edges (src, dst) in the minimum spanning tree in sequence
  std::vector<std::pair<size_t, size_t>> mst;
  // total cost of the minimum spanning tree
  T cost = 0;
  for ( auto v : edges ) {
    if (mst.size() == graph.size()) { break; }

    // O(ElogV) in worst case for union-by-rank
    size_t head_src = find(v.second.first, union_);
    // O(ElogV) in worst case for union-by-rank
    size_t head_dst = find(v.second.second, union_);

    // if they are in different unions
    if ( head_src != head_dst ) {
      mst.push_back(v.second);
      cost += v.first;
      unionByRank(head_src, head_dst, union_);
    }
  }
  return std::make_pair(cost, mst);
}


#endif //GRAPH_KRUSKAL_H