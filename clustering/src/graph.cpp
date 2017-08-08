//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"


Graph::Graph() {};

Graph::~Graph() {
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
