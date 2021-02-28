//
// Created by jun on 8/19/17.
//
// Implementation of the undirected graph using adjacency list
//
#ifndef GRAPH_UNDIRECTED_GRAPH_H
#define GRAPH_UNDIRECTED_GRAPH_H

#include "graph.h"


template <class T>
class UndirectedGraph: public Graph<T> {
protected:
  using Graph<T>::vertices_;

public:
  using Graph<T>::Graph;

  ~UndirectedGraph() override {};

  size_t countEdge() const override {
    size_t count = 0;
    for (const auto& v : vertices_) {
      graph::Edge<T>* current_edge = v;
      while (current_edge != nullptr) {
        ++count;
        current_edge = current_edge->next;
      }
    }

    if (count%2 != 0) {
      throw std::invalid_argument("Number of edges is odd in an undirected graph!");
    }
    return count/2;
  }

  T countWeight() const override {
    long long sum = 0;
    for (const auto& v : vertices_) {
      graph::Edge<T>* current_edge = v;
      while (current_edge != nullptr) {
        sum += current_edge->weight;
        current_edge = current_edge->next;
      }
    }

    return (sum/2);
  }

  bool connect(size_t src, size_t dst) override {
    return (this->addEdge(src, dst, 1) && this->addEdge(dst, src, 1));
  }

  bool connect(size_t src, size_t dst, T weight) override {
    return (this->addEdge(src, dst, weight) && this->addEdge(dst, src, weight));
  }

  T disconnect(size_t src, size_t dst) override {
    auto weight1 = this->delEdge(src, dst);
    auto weight2 = this->delEdge(dst, src);

    if (weight1 != weight2) {
      throw std::invalid_argument("Inconsistent edge lengths in undirected graph!");
    }

    return weight1;
  }

  //void UdGraph::collapse(int src, int dst) {
//  if ( src == dst ) { return; }
//
//  // first remove loops
//  disconnect(src, dst);
//
//  // In each collapse, the No. of edges will be reduced only by the No. of edges
//  // between the source and destination vertices!
//
//  // change the value of nodes with value src to dst
//  graph::Edge* current = getVtx(source)->next;
//  while ( current ) {
//    // change the node with value 'src' in other linked lists to 'dst'
//    // TODO:: this could be fast since the linked list is traversed twice here for code simplicity
//    double weight = delEdge(current->value, source);
//    addEdge(current->value, destination, weight);
//
//    // add node in the linked list 'src' to the linked list 'dst'
//    addEdge(destination, current->value, current->weight);
//
//    current = current->next;
//  }
//
//  // delete linked list and release memory
//  clearList(source);
//}

};

#endif //GRAPH_UNDIRECTED_GRAPH_H