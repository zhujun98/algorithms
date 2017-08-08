//
// Created by jun on 8/8/17.
//

#ifndef CLUSTERING_GRAPH_H
#define CLUSTERING_GRAPH_H

#include <queue>
#include <vector>


typedef int node_value;

struct Edge {
  node_value src; // value of source node
  node_value dst; // value of destination node
  double weight; // weight of the edge
};

// pointer comparator
struct CompareEdgePtr {
  bool operator()(Edge* a, Edge* b) {return a->weight > b->weight;}
};


//
// The graph serves as a container for the edges, which is stored in the heap.
// The advantage here is to avoid memory leak.
//
class Graph {
private:
  typedef std::priority_queue<Edge*, std::vector<Edge*>, CompareEdgePtr> graph_edges;
  graph_edges edges_; // unprocessed edges
  graph_edges removed_edges_; // processed edges

public:
  //
  // constructor
  //
  Graph();

  //
  // destructor
  //
  ~Graph();

  //
  // Add an edge
  //
  // @param src: value of source node
  // @param dst: value of destination node
  // @param weight: weight of the edge
  //
  void setEdge(node_value src, node_value dst, double weight);

  //
  // Pop an edge from the priority queue
  //
  // @return: pointer to the poped edge
  //
  Edge* popEdge();

  //
  // Check whether all the edges have been processed
  //
  bool isEdgeEmpty();

};


#endif //CLUSTERING_GRAPH_H
