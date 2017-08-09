//
// Created by jun on 8/8/17.
//

#ifndef CLUSTERING_GRAPH_H
#define CLUSTERING_GRAPH_H

#include <queue>
#include <vector>


template <class T>
struct Node {
  T value; // value of the node
  T parent; // value of the parent node
  int rank; // rank of the node
};

template <class T>
struct Edge {
  T src; // value of source node
  T dst; // value of destination node
  double weight; // weight of the edge
};

// pointer comparator
template <class T>
struct CompareEdgePtr {
  bool operator()(Edge<T>* a, Edge<T>* b) {return a->weight > b->weight;}
};


template <class T>
class Graph {

private:
  typedef std::vector<Node<T>*> graph_nodes;
  graph_nodes nodes_; // graph nodes

  typedef std::priority_queue<Edge<T>*, std::vector<Edge<T>*>, CompareEdgePtr<T>> graph_edges;
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
  void setEdge(T src, T dst, double weight);

  //
  // Pop an edge from the priority queue
  //
  // @return: pointer to the poped edge
  //
  Edge<T>* popEdge();

  //
  // Set parent node of a node
  //
  // @param value: node value
  // @param parent: parent node value
  //
  void setParent(T value, T parent);

  //
  // Increase the rank of a node by 1
  //
  // @param value: node value
  //
  void increaseRank(T value);

  // Check whether all the edges have been processed
  bool isEdgeEmpty();

  size_t size() const;

  const Node<T>* getNode(T value) const;
};

template class Graph<int>;

#endif //CLUSTERING_GRAPH_H
