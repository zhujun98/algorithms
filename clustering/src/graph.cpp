//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"


Graph::Graph(int size) {
  for ( int i=0; i<size; ++i ) {
    Node* node = new Node;
    node->value = i + 1;
    node->parent = node->value;
    node->rank = 0;
    nodes_.push_back(node);
  }
};

Graph::~Graph() {
  for ( auto& v : nodes_ ) { delete v; }

  while ( !edges_.empty() ) {
    Edge* edge = edges_.top();
    edges_.pop();
    delete edge;
  }

  while ( !removed_edges_.empty() ) {
    Edge* edge = removed_edges_.top();
    removed_edges_.pop();
    delete edge;
  }
};

void Graph::resetGraph() {
  for ( auto& v : nodes_ ) {
    v->parent = v->value;
    v->rank = 0;
  }

  while ( !removed_edges_.empty() ) {
    edges_.push(removed_edges_.top());
    removed_edges_.pop();
  }
}

void Graph::setEdge(node_value src, node_value dst, double weight) {
  Edge* edge = new Edge;
  edge->src = src;
  edge->dst = dst;
  edge->weight = weight;

  edges_.push(edge);
}

Edge* Graph::popEdge() {
  Edge* edge = edges_.top();
  edges_.pop();
  removed_edges_.push(edge); // additional work to avoid memory leak

  return edge;
}

bool Graph::isEdgeEmpty() {
  return edges_.empty();
}

const Node* Graph::getNode(int value) const { return nodes_[value-1]; }

void Graph::increaseRank(int value) { ++nodes_[value-1]->rank; }

void Graph::setParent(int value, int parent) { nodes_[value-1]->parent = parent; }

size_t Graph::size() const { return nodes_.size(); }