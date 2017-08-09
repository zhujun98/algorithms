//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"

template <class T>
Graph<T>::Graph(int size) {
  for ( int i=0; i<size; ++i ) {
    Node<T>* node = new Node<T>;
    node->value = i + 1;
    node->parent = node->value;
    node->rank = 0;
    nodes_.push_back(node);
  }
};

template <class T>
Graph<T>::~Graph() {
  for ( auto& v : nodes_ ) { delete v; }

  while ( !edges_.empty() ) {
    Edge<T>* edge = edges_.top();
    edges_.pop();
    delete edge;
  }

  while ( !removed_edges_.empty() ) {
    Edge<T>* edge = removed_edges_.top();
    removed_edges_.pop();
    delete edge;
  }
};

template <class T>
void Graph<T>::resetGraph() {
  for ( auto& v : nodes_ ) {
    v->parent = v->value;
    v->rank = 0;
  }

  while ( !removed_edges_.empty() ) {
    edges_.push(removed_edges_.top());
    removed_edges_.pop();
  }
}

template <class T>
void Graph<T>::setEdge(T src, T dst, double weight) {
  Edge<T>* edge = new Edge<T>;
  edge->src = src;
  edge->dst = dst;
  edge->weight = weight;

  edges_.push(edge);
}

template <class T>
Edge<T>* Graph<T>::popEdge() {
  Edge<T>* edge = edges_.top();
  edges_.pop();
  removed_edges_.push(edge); // additional work to avoid memory leak

  return edge;
}

template <class T>
bool Graph<T>::isEdgeEmpty() {
  return edges_.empty();
}

template <class T>
const Node<T>* Graph<T>::getNode(T value) const { return nodes_[value-1]; }

template <class T>
void Graph<T>::increaseRank(T value) { ++nodes_[value-1]->rank; }

template <class T>
void Graph<T>::setParent(T value, T parent) { nodes_[value-1]->parent = parent; }

template <class T>
size_t Graph<T>::size() const { return nodes_.size(); }

