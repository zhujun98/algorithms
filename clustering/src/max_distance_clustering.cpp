//
// Created by jun on 8/8/17.
//
#include <iostream>
#include <map>

#include "graph.h"
#include "max_distance_clustering.h"


#define INVALID_NODE_VALUE -1111111

MaxDistanceClustering::MaxDistanceClustering(int size) {
  n_sets_ = size;
  makeNewSet(size);
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
    if ( tracker_[value - 1]->parent != value ) {
      tracker_[value - 1]->parent = find(tracker_[value - 1]->parent);
    }

    return tracker_[value - 1]->parent;
  }
}

void MaxDistanceClustering::union_(int a, int b) {
  node_value leader_a = find(a);
  node_value leader_b = find(b);
  int rank_a = tracker_[leader_a - 1]->rank;
  int rank_b = tracker_[leader_b - 1]->rank;

  if ( leader_a != INVALID_NODE_VALUE && leader_b != INVALID_NODE_VALUE
       && leader_a != leader_b ) {
    if ( rank_a > rank_b ) {
      tracker_[leader_b - 1]->parent = leader_a;
    } else {
      tracker_[leader_a - 1]->parent = leader_b;
      // rank changes after union operation only when the original two
      // sets have the same rank.
      if (rank_a == rank_b ) {
        ++tracker_[leader_b - 1]->rank;
      }
    }
    n_sets_ -= 1;
  }
}

void MaxDistanceClustering::fit(Graph& graph, int n_clusters) {
  while ( n_sets_ > n_clusters ) {
    Edge* edge = graph.popEdge();
    union_(edge->src, edge->dst);
  }
}

void MaxDistanceClustering::print() {
  std::map<node_value, std::vector<node_value >> disjoint_sets;
  for ( const auto& v : tracker_ ) {
    node_value leader_value = find(v->value);
    auto found = disjoint_sets.find(leader_value);
    if ( found != disjoint_sets.end() ) {
      found->second.push_back(v->value);
    } else {
      std::vector<node_value> this_set_values = {v->value};
      disjoint_sets.insert(std::make_pair(leader_value, this_set_values));
    }
  }

  for ( const auto& s : disjoint_sets ) {
    for ( const auto& v : s.second ) {
      std::cout << v << ", ";
    }
    std::cout << std::endl;
  }
}