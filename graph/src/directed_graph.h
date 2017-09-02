//
// Created by jun on 8/21/17.
//

#ifndef GRAPH_DIRECTED_GRAPH_H
#define GRAPH_DIRECTED_GRAPH_H

#include "graph.h"


template <class T>
class DirectedGraph : public Graph<T> {
protected:

  using Graph<T>::vertices_;
  using Graph<T>::clearList;

public:

  using Graph<T>::Graph;

  ~DirectedGraph() override {};

  size_t countEdge() const override {
    size_t count = 0;
    for (const auto& v : vertices_) {
      graph::Edge<T>* current_edge = v;
      while (current_edge != nullptr) {
        ++count;
        current_edge = current_edge->next;
      }
    }

    return count;
  }

  T countWeight() const override {
    T sum = 0;
    for (const auto& v : vertices_) {
      graph::Edge<T>* current_edge = v;
      while (current_edge != nullptr) {
        sum += current_edge->weight;
        current_edge = current_edge->next;
      }
    }
    return sum;
  }

  bool connect(size_t src, size_t dst) override {
    return (this->addEdge(src, dst, 1));
  }

  bool connect(size_t src, size_t dst, T weight) override {
    return (this->addEdge(src, dst, weight));
  }

  T disconnect(size_t src, size_t dst) override {
    return (this->delEdge(src, dst));
  }

  // increase the number of vertices by one
  void increaseVertex() {
    vertices_.push_back(nullptr);
  }

  // decrease the number of vertices by one
  void decreaseVertex() {
    clearList(vertices_.size() - 1);
    vertices_.pop_back();
  }

  // increase the weight of an edge
  bool increaseWeight(size_t src, size_t dst, T weight) {
    auto current_edge = vertices_[src];
    while (current_edge != nullptr) {
      if (current_edge->dst == dst) {
        current_edge->weight += weight;
        return true;
      }
      current_edge = current_edge->next;
    }

    return false;
  }

  // reverse a directed graph
  void reverse() {
    size_t n_vertices = this->size();
    std::vector<graph::Edge<T>*> new_vertices_(n_vertices);
    for (size_t i=0; i < n_vertices; ++i) {
      graph::Edge<T>* current_edge = vertices_[i];
      graph::Edge<T>* next_edge;
      while (current_edge != nullptr) {
        next_edge = current_edge->next;
        // reverse the head and tail of the edge and add the edge
        // to the new list
        auto dst = current_edge->dst;
        current_edge->next = new_vertices_[dst];
        current_edge->dst = i;
        new_vertices_[dst] = current_edge;
        // remove the edge from the original list
        current_edge = next_edge;
      }
    }

    for (size_t i=0; i<n_vertices; ++i ) {vertices_[i] = new_vertices_[i]; }
  }

};


#endif //GRAPH_DIRECTED_GRAPH_H
