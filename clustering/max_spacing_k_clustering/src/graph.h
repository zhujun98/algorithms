//
// Created by jun on 8/8/17.
//
#ifndef CLUSTERING_GRAPH_H
#define CLUSTERING_GRAPH_H

#include <queue>
#include <vector>


struct Node {
  int index; // index of the node
  int parent; // index of the parent node
  int rank; // rank of the node
};


struct Edge {
  int src; // index of source node
  int dst; // index of destination node
  double weight; // weight of the edge
};


// pointer comparator
struct CompareEdgePtr {
  bool operator()(Edge* a, Edge* b) {return a->weight > b->weight;}
};


class Graph {

private:
  typedef std::vector<Node*> graph_nodes;
  graph_nodes nodes_; // graph nodes

  typedef std::priority_queue<Edge*, std::vector<Edge*>, CompareEdgePtr> graph_edges;
  graph_edges edges_; // unprocessed edges
  graph_edges removed_edges_; // processed edges

public:
  //
  // constructor
  //
  // @param size: total No. of nodes
  //
  Graph(size_t size);

  //
  // destructor
  //
  ~Graph();

  //
  // reset the graph to the initial state
  //
  void resetGraph();

  //
  // Add an edge
  //
  // @param src: index of source node
  // @param dst: index of destination node
  // @param weight: weight of the edge
  //
  void setEdge(int src, int dst, double weight);

  //
  // Pop an edge from the priority queue
  //
  // @return: pointer to the popped edge
  //
  Edge* popEdge();

  //
  // Set parent node of a node
  //
  // @param index: index of the node
  // @param parent_index: index of the parent node
  //
  void setParent(int index, int parent_index);

  //
  // Increase the rank of a node by 1
  //
  // @param value: node index
  //
  void increaseRank(int index);

  //
  // Check whether all the edges have been processed
  //
  bool isEdgeEmpty();

  size_t size() const;

  const Node* getNode(int index) const;
};

#endif //CLUSTERING_GRAPH_H
