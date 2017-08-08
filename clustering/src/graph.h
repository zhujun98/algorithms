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

struct CompareEdgePtr {
  bool operator()(Edge* a, Edge* b) {return a->weight > b->weight;}
};

class Graph {
private:
  typedef std::priority_queue<Edge*, std::vector<Edge*>, CompareEdgePtr> graph_edges;
  graph_edges edges_;
  graph_edges removed_edges_;

public:
  Graph();

  ~Graph();

  void setEdge(node_value src, node_value dst, double weight);

  Edge* popEdge();

};


#endif //CLUSTERING_GRAPH_H
