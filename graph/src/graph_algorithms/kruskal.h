//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_KRUSKAL_H
#define GRAPH_KRUSKAL_H

#include <algorithm>

#include "breath_first_search.h"
#include "../ud_graph.h"


// a union-find data structure composed of the head vertex (index) of
// each union and its rank
typedef std::vector<std::pair<int, int>> union_find;

//
// Comparator for edge: less
//
template <class T>
struct edgeLess {
  // <weight, <from vertex index, to vertex index>>
  typedef std::pair<double, std::pair<int, int>> graph_edge;

  bool operator()(const graph_edge& e1, const graph_edge& e2) {
    return e1.first < e2.first;
  }
};


//
// Find the head vertex of a vertex
//
// @param vertex: index of the vertex
// @param union_: union-find data structure
//
// @return: index of the head vertex
//
int find(int vertex, const union_find& union_) {
  int head(union_[vertex].first);
  while ( vertex != head ) {
    vertex = head;
    head = union_[vertex].first;
  }
  return head;
}


//
// Fuse the two unions by rank
//
// @param head1: index of the head vertex 1
// @param head2: index of the head vertex 2
// @param union_: union-find data structure
//
void unionByRank(int head1, int head2, union_find& union_) {

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
template <class T>
inline std::pair<double, std::vector<std::pair<T, T>>>
kruskal(const UdGraph<T>& graph) {
  // check the connectivity of the graph
  auto bfs_search = breathFirstSearch(graph, graph.indexToValue(0));

  if ( bfs_search.size() != graph.size() ) {
    throw std::invalid_argument("Input graph is not connected!");
  }

  // <weight, <tail vertex index, head vertex index>>
  typedef std::pair<double, std::pair<int, int>> graph_edge;
  // store all the edges in a vector
  std::vector<graph_edge> edges;
  // read out all the edges
  for ( int i=0; i<graph.size(); ++i ) {
    graph::Edge<T>* current_edge = graph.getVertexByIndex(i)->next;
    while ( current_edge ) {
      edges.push_back(std::make_pair(
          current_edge->weight,
          std::make_pair(i, graph.valueToIndex(current_edge->value))));
      current_edge = current_edge->next;
    }
  }
  // sort the edges in descending order, O(ElogE)
  std::sort(edges.begin(), edges.end(), edgeLess<T>());

  union_find union_;

  // initialization
  for ( int i=0; i<graph.size(); ++i ) {
    union_.push_back(std::make_pair(i, 0));
  }

  // (tail, head) vertices in the minimum spanning tree
  std::vector<std::pair<T, T>> mst;
  // total cost of the minimum spanning tree
  double cost = 0;
  for ( auto v : edges ) {
    if ( mst.size() == graph.size() ) { break; }

    // O(ElogV) in worst case for union-by-rank
    int head_of_tail_vertex = find(v.second.first, union_);
    // O(ElogV) in worst case for union-by-rank
    int head_of_head_vertex = find(v.second.second, union_);

    // if they are in different unions
    if ( head_of_tail_vertex != head_of_head_vertex ) {
      mst.push_back(std::make_pair(graph.indexToValue(v.second.first),
                                   graph.indexToValue(v.second.second)));
      cost += v.first;

      unionByRank(head_of_tail_vertex, head_of_head_vertex, union_);
    }
  }
  return std::make_pair(cost, mst);
}


#endif //GRAPH_KRUSKAL_H