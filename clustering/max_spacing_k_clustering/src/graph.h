//
// Created by jun on 8/8/17.
//

#ifndef CLUSTERING_GRAPH_H
#define CLUSTERING_GRAPH_H

#include <queue>
#include <vector>


typedef int node_value;

struct Node {
  node_value value; // value of the node
  node_value parent; // value of the parent node
  int rank; // rank of the node
};

struct Edge {
  node_value src; // value of source node
  node_value dst; // value of destination node
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
  Graph(int size);

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
  // Set parent node of a node
  //
  // @param value: node value
  // @param parent: parent node value
  //
  void setParent(int value, int parent);

  //
  // Increase the rank of a node by 1
  //
  // @param value: node value
  //
  void increaseRank(int value);

  // Check whether all the edges have been processed
  bool isEdgeEmpty();

  size_t size() const;

  const Node* getNode(int value) const;
};


#endif //CLUSTERING_GRAPH_H
