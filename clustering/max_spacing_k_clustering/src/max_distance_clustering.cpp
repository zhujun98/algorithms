//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"
#include "max_distance_clustering.h"

MaxDistanceClustering::MaxDistanceClustering() {};

MaxDistanceClustering::~MaxDistanceClustering() {};

int MaxDistanceClustering::find(Graph& graph, int index) {

  if ( use_path_compression_ ) {
    // path compression
    if ( graph.getNode(index)->parent != index ) {
      graph.setParent(index, find(graph, graph.getNode(index)->parent));
    }

    return graph.getNode(index)->parent;
  } else {
    // without path compression
    int parent_index = graph.getNode(index)->parent;
    while ( parent_index != index ) {
      index = graph.getNode(parent_index)->index;
      parent_index = graph.getNode(parent_index)->parent;
    }

    return parent_index;
  }
}

bool MaxDistanceClustering::lazyUnion(Graph& graph, int src, int dst) {
  int leader_src = find(graph, src);
  int leader_dst = find(graph, dst);
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

void MaxDistanceClustering::fit(Graph& graph, int n_clusters) {

  n_sets_ = graph.size();

  Edge* edge;
  while ( n_sets_ > n_clusters ) {
    edge = graph.popEdge();
    lazyUnion(graph, edge->src, edge->dst);
  }

  disjoint_sets_.clear();
  for ( int i=0; i<graph.size(); ++i ) {
    disjoint_sets_.push_back(find(graph, i));
  }

  // The "spacing" is defined as the minimum distance between any of
  // the two clusters
  while ( !graph.isEdgeEmpty() ) {
    edge = graph.popEdge();
    int leader_src = find(graph, edge->src);
    int leader_dst = find(graph, edge->dst);
    if ( leader_src != leader_dst ) {
      min_spacing_ = edge->weight;
      return;
    }
  }
}

void MaxDistanceClustering::print() {
  std::cout<< "The remaining number of clusters is: " << n_sets_ << std::endl;
  for ( const auto& v : disjoint_sets_ ) { std::cout << v << ", "; }
  std::cout << std::endl;
  std::cout << "The minimum spacing is: " << min_spacing_ << std::endl;
}

double MaxDistanceClustering::getMinSpacing() { return min_spacing_; }

std::vector<int> MaxDistanceClustering::getDisjointSets() { return disjoint_sets_; }

void MaxDistanceClustering::setUsePathCompression(bool value) { use_path_compression_ = value; }
