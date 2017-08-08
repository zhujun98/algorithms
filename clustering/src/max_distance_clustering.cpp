//
// Created by jun on 8/8/17.
//
#include <iostream>

#include "graph.h"
#include "max_distance_clustering.h"


#define INVALID_NODE_VALUE -1111111

MaxDistanceClustering::MaxDistanceClustering(int size) {
  n_sets_ = size;
  makeNewSet(size);

  use_path_compression_ = true;
};

MaxDistanceClustering::~MaxDistanceClustering() {
  for ( auto &v : tracker_ ) { delete v; }
};

void MaxDistanceClustering::makeNewSet(int n_pts) {
  for ( int i=0; i<n_pts; ++i ) {
    Node* node = new Node;
    node->value = i + 1;
    node->parent = node->value;
    node->rank = 0;
    tracker_.push_back(node);
  }
}

node_value MaxDistanceClustering::find(int value) {
  if ( value > tracker_.size() ) {
    std::cout << "Invalid node value!" << std::endl;
    return INVALID_NODE_VALUE;
  } else {
    // path compression
    if ( use_path_compression_ ) {
      if ( tracker_[value - 1]->parent != value ) {
        tracker_[value - 1]->parent = find(tracker_[value - 1]->parent);
      }

      return tracker_[value - 1]->parent;
    } else {
      node_value parent = tracker_[value - 1]->parent;
      while ( parent != value ) {
        value = tracker_[parent - 1]->value;
        parent = tracker_[parent - 1]->parent;
      }

      return parent;
    }
  }
}

bool MaxDistanceClustering::union_(const Edge& edge) {
  node_value leader_src = find(edge.src);
  node_value leader_dst = find(edge.dst);
  int rank_a = tracker_[leader_src - 1]->rank;
  int rank_b = tracker_[leader_dst - 1]->rank;

  if ( leader_src != INVALID_NODE_VALUE && leader_dst != INVALID_NODE_VALUE
       && leader_src != leader_dst ) {
    if ( rank_a > rank_b ) {
      tracker_[leader_dst - 1]->parent = leader_src;
    } else {
      tracker_[leader_src - 1]->parent = leader_dst;
      // rank changes after union operation only when the original two
      // sets have the same rank.
      if (rank_a == rank_b ) {
        ++tracker_[leader_dst - 1]->rank;
      }
    }
    n_sets_ -= 1;
    return true;
  } else {
    return false;
  }
}

void MaxDistanceClustering::fit(Graph& graph, int n_clusters) {
  Edge* edge;
  while ( n_sets_ > n_clusters ) {
    edge = graph.popEdge();
    union_(*edge);
  }

  for ( const auto& v : tracker_ ) {
    disjoint_sets_.push_back(find(v->value));
  }

  // The "spacing" is defined as the minimum distance between any of
  // the two clusters
  while ( !graph.isEdgeEmpty() ) {
    edge = graph.popEdge();
    node_value leader_src = find(edge->src);
    node_value leader_dst = find(edge->dst);
    if ( leader_src != INVALID_NODE_VALUE && leader_dst != INVALID_NODE_VALUE
         && leader_src != leader_dst ) {
      min_spacing_ = edge->weight;
      return;
    }
  }
}

void MaxDistanceClustering::print() {
  std::cout<< "The remaining number of clusters is: " << n_sets_ << std::endl;
  for ( const auto& v : disjoint_sets_ ) {
    std::cout << v << ", ";
  }
  std::cout << std::endl;

  std::cout << "The maximum spacing is: " << min_spacing_ << std::endl;
}

double MaxDistanceClustering::getMinSpacing() { return min_spacing_; }

std::vector<node_value> MaxDistanceClustering::getDisjointSets() { return disjoint_sets_; }

void MaxDistanceClustering::setUsePathCompression(bool value) { use_path_compression_ = value; }
