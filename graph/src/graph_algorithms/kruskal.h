//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_KRUSKAL_H
#define GRAPH_KRUSKAL_H

#include <algorithm>
#include <map>

#include "breath_first_search.h"
#include "../ud_graph.h"


//
// Comparator for edge: less
//
template <class T>
struct edgeLess {
  // <weight, <from vertex, to vertex>>
  typedef std::pair<double, std::pair<T, T>> graph_edge;

  bool operator()(const graph_edge& e1, const graph_edge& e2) {
    return e1.first < e2.first;
  }
};


//
// Implementation of the Kruskal's minimum spanning tree algorithm
//
// A naive union-find data structure is implemented to boost the
// algorithm. The time complexity of finding the head vertex of a
// vertex in a union is O(1). To get the final result, we need to
// merge the unions for n times, where n is the number of vertices.
// Since we always merge the smaller union to the big one, the time
// that a vertex needs to change its head vertex has a time
// complexity of O(logn). That is to say, the total time complexity
// for the union (merge) operation is O(nlogn).
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

  // <weight, <tail vertex, head vertex>>
  typedef std::pair<double, std::pair<T, T>> graph_edge;
  std::vector<graph_edge> edges;

  // store all the edges in a vector
  for ( int i=0; i<graph.size(); ++i ) {
    graph::Edge<T>* current_edge = graph.getVertexByIndex(i)->next;
    while ( current_edge ) {
      edges.push_back(std::make_pair(current_edge->weight,
                                     std::make_pair(graph.indexToValue(i),
                                                    current_edge->value)));
      current_edge = current_edge->next;
    }
  }

  // sort the edges in descending order
  std::sort(edges.begin(), edges.end(), edgeLess<T>());

  // a vector storing the head vertex of each union
  std::vector<T> union_find_head;
  // a vector storing the size of each union with the key being the
  // head vertex of each union
  std::map<T, int> rank;
  // initialization
  for ( int i=0; i<graph.size(); ++i ) {
    T vertex = graph.indexToValue(i);
    union_find_head.push_back(vertex);
    rank.insert(std::make_pair(vertex, 1));
  }

  // (tail, head) vertices in the minimum spanning tree
  std::vector<std::pair<T, T>> mst;
  // total cost of the minimum spanning tree
  double cost = 0;
  for ( auto v : edges ) {
    if ( mst.size() == graph.size() ) { break; }
    T tail_vertex = v.second.first;
    T head_vertex = v.second.second;
    T head_of_tail_vertex = union_find_head[graph.valueToIndex(tail_vertex)];
    T head_of_head_vertex = union_find_head[graph.valueToIndex(head_vertex)];

    // if they are in different unions
    if ( head_of_tail_vertex != head_of_head_vertex ) {
      mst.push_back(v.second);
      cost += v.first;

      // merge two unions
      auto head_of_tail_vertex_search = rank.find(head_of_tail_vertex);
      auto head_of_head_vertex_search = rank.find(head_of_head_vertex);
      if ( head_of_tail_vertex_search->second > head_of_head_vertex_search->second ) {
        head_of_head_vertex_search->second += head_of_head_vertex_search->second;
        rank.erase(head_of_head_vertex_search);
        for ( size_t i=0; i < union_find_head.size(); ++i ) {
          if ( union_find_head[i] == head_of_head_vertex ) {
            union_find_head[i] = head_of_tail_vertex;
          }
        }
      } else {
        head_of_head_vertex_search->second += head_of_tail_vertex_search->second;
        rank.erase(head_of_tail_vertex_search);
        for ( size_t i=0; i < union_find_head.size(); ++i ) {
          if ( union_find_head[i] == head_of_tail_vertex ) {
            union_find_head[i] = head_of_head_vertex;
          }
        }
      }
    }
  }

  return std::make_pair(cost, mst);
}


#endif //GRAPH_KRUSKAL_H