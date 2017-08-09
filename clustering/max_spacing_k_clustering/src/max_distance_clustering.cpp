//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"
#include "max_distance_clustering.h"

template <class T>
MaxDistanceClustering<T>::MaxDistanceClustering() {};

template <class T>
MaxDistanceClustering<T>::~MaxDistanceClustering() {};

template<class T>
T MaxDistanceClustering<T>::find(Graph<T>& graph, T value) {

  if ( use_path_compression_ ) {
    // path compression
    if ( graph.getNode(value)->parent != value ) {
      graph.setParent(value, find(graph, graph.getNode(value)->parent));
    }

    return graph.getNode(value)->parent;
  } else {
    // without path compression
    T parent = graph.getNode(value)->parent;
    while ( parent != value ) {
      value = graph.getNode(parent)->value;
      parent = graph.getNode(parent)->parent;
    }

    return parent;
  }
}

template <class T>
bool MaxDistanceClustering<T>::lazyUnion(Graph<T>& graph, T src, T dst) {
  T leader_src = find(graph, src);
  T leader_dst = find(graph, dst);
  int rank_src = graph.getNode(leader_src)->rank;
  int rank_dst = graph.getNode(leader_dst)->rank;

  if ( leader_src != leader_dst ) {
    if ( rank_src > rank_dst ) {
      graph.setParent(leader_dst, leader_src);
    } else {
      graph.setParent(leader_src, leader_dst);
      // rank changes after union operation only when the original two
      // sets have the same rank.
      if ( rank_dst == rank_src ) { graph.increaseRank(leader_dst); }
    }
    n_sets_ -= 1;
    return true;
  } else {
    return false;
  }
}

template <class T>
void MaxDistanceClustering<T>::fit(Graph<T>& graph, int n_clusters) {

  n_sets_ = graph.size();

  Edge<T>* edge;
  while ( n_sets_ > n_clusters ) {
    edge = graph.popEdge();
    lazyUnion(graph, edge->src, edge->dst);
  }

  disjoint_sets_.clear();
  for ( int i=0; i<graph.size(); ++i ) {
    disjoint_sets_.push_back(find(graph, i+1));
  }

  // The "spacing" is defined as the minimum distance between any of
  // the two clusters
  while ( !graph.isEdgeEmpty() ) {
    edge = graph.popEdge();
    T leader_src = find(graph, edge->src);
    T leader_dst = find(graph, edge->dst);
    if ( leader_src != leader_dst ) {
      min_spacing_ = edge->weight;
      return;
    }
  }
}

template <class T>
void MaxDistanceClustering<T>::print() {
  std::cout<< "The remaining number of clusters is: " << n_sets_ << std::endl;
  for ( const auto& v : disjoint_sets_ ) { std::cout << v << ", "; }
  std::cout << std::endl;
  std::cout << "The minimum spacing is: " << min_spacing_ << std::endl;
}

template <class T>
double MaxDistanceClustering<T>::getMinSpacing() { return min_spacing_; }

template <class T>
std::vector<T> MaxDistanceClustering<T>::getDisjointSets() { return disjoint_sets_; }

template <class T>
void MaxDistanceClustering<T>::setUsePathCompression(bool value) { use_path_compression_ = value; }
