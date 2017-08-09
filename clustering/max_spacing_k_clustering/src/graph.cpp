//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"


Graph::Graph(int size) {
  for ( int i=0; i<size; ++i ) {
    Node* node = new Node;
    node->index = i;
    node->parent = i;
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
    v->parent = v->index;
    v->rank = 0;
  }

  while ( !removed_edges_.empty() ) {
    edges_.push(removed_edges_.top());
    removed_edges_.pop();
  }
}

void Graph::setEdge(int src, int dst, double weight) {
  if ( src >= nodes_.size() ) {
    throw std::invalid_argument("index out of range");
  }
  if ( dst >= nodes_.size() ) {
    throw std::invalid_argument("index out of range");
  }

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

const Node* Graph::getNode(int index) const { return nodes_[index]; }

void Graph::increaseRank(int index) { ++nodes_[index]->rank; }

void Graph::setParent(int index, int parent_index) { nodes_[index]->parent = parent_index; }

size_t Graph::size() const { return nodes_.size(); }
