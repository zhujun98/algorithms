//
// Created by jun on 8/8/17.
//
// Max-spacing k-clustering (single-linkage clustering) utilizing
// union-find (disjoint-set) data structure.
//
// Lazy union: union-by-rank and path compression.
// TODO:: implement eager union
//
#ifndef CLUSTERING_UNION_FIND_H
#define CLUSTERING_UNION_FIND_H

#include <queue>
#include <vector>

#include "graph.h"


template<class T>
class MaxDistanceClustering {

private:

  // A vector which stores the leader node value of each node.
  // This is only used for visualization of the final result.
  std::vector<T> disjoint_sets_;
  size_t n_sets_; // No. of remaining sets
  double min_spacing_; // maximum spacing between clusters

  bool use_path_compression_; //

  //
  // Find the leader node of the node with the given value
  //
  // @param graph: Graph object
  // @param value: node value
  // @return: value of the leader node
  //
  T find(Graph<T>& graph, T value);

  //
  // Fuse two nodes belong to an edge (union-by-rank)
  //
  // @param graph: Graph object
  // @param src: source node value
  // @param dst: destination node value
  //
  bool lazyUnion(Graph<T>& graph, T src, T dst);

public:
  //
  // constructor
  //
  MaxDistanceClustering();

  //
  // destructor
  //
  ~MaxDistanceClustering();

  //
  // set whether to use the path compression algorithm
  //
  void setUsePathCompression(bool value);

  //
  // Fit the nodes into disjoint set with minimum total edge weights
  //
  // @param edges: a priority queue of edges
  // @param n_clusters: No. of clusters to make
  //
  void fit(Graph<T>& graph, int n_clusters);

  //
  // Print the result
  //
  void print();

  double getMinSpacing();

  std::vector<T> getDisjointSets();
};

template class MaxDistanceClustering<int>;

#endif //CLUSTERING_UNION_FIND_H
