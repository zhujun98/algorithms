//
// Created by jun on 8/8/17.
//
// Union-find (disjoint-set) data structure implemented
// using union-by-rank and path compression.
//
#ifndef CLUSTERING_UNION_FIND_H
#define CLUSTERING_UNION_FIND_H

#include <queue>
#include <vector>

class Graph;
typedef int node_value;


struct Node {
  node_value value; // value of the node
  node_value parent; // value of the parent node
  int rank; // rank of the node
};

class MaxDistanceClustering {
private:

  std::vector<Node*> tracker_;
  std::vector<node_value> disjoint_sets_;
  int n_sets_; // number of remaining sets
  double min_spacing_; // maximum spacing between clusters

  //
  // Initialize the disjoint sets. Each node forms a set.
  //
  // @param size: total No. of nodes
  //
  void makeNewSet(int size);

  //
  // Find the leader node of the node with the given value
  //
  // @param value: node value
  // @return: value of the leader node
  //
  node_value find(node_value value);

  //
  // Fuse two nodes belong to an edge
  //
  // @param edge: Edge object
  //
  bool union_(const Edge& edge);

public:

  //
  // constructor
  //
  // @param: total No. of nodes
  //
  MaxDistanceClustering(int size);

  //
  // destructor
  //
  ~MaxDistanceClustering();

  //
  // Fit the nodes into disjoint set with minimum total edge weights
  //
  // @param edges: a priority queue of edges
  // @param n_clusters: No. of clusters to make
  //
  void fit(Graph& graph, int n_clusters);

  //
  // Print the result
  //
  void print();

  double getMinSpacing();

  std::vector<node_value> getDisjointSets();
};


#endif //CLUSTERING_UNION_FIND_H
