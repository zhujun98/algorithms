//
// Created by jun on 8/8/17.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

#include "graph.h"
#include "max_distance_clustering.h"


void runClusteringAssignmentSmall() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the clustring assignment (small data set) \n"
            << "in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/clustering_small.txt", std::ifstream::in);

  std::string line;
  std::string number;

  // read the first line
  std::getline(ifs, line);
  std::istringstream iss0(line);
  iss0 >> number;
  int n_pts = std::stoi(number);
  Graph graph;

  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    iss >> number;
    node_value src = std::stoi(number);
    iss >> number;
    node_value dst = std::stoi(number);
    iss >> number;
    double weight = std::stod(number);

    graph.setEdge(src, dst, weight);
  }

  std::cout << "Finish reading data!" << std::endl;
  ifs.close();

  clock_t t0 = clock();
  MaxDistanceClustering cluster(n_pts);
  cluster.fit(graph, 4);
  std::cout << "Run time: " << 1.0e-6*(clock() - t0)*CLOCKS_PER_SEC
            << " ms" << std::endl;

  assert(cluster.getMinSpacing() == 106);
  std::cout << "Passed!" << std::endl;
}

void testMaxDistanceClustering() {
  Graph graph;

  graph.setEdge(1, 2, 1);
  graph.setEdge(1, 3, 2);
  graph.setEdge(1, 4, 3);
  graph.setEdge(2, 3, 2);
  graph.setEdge(2, 4, 4);
  graph.setEdge(3, 4, 2);

  MaxDistanceClustering cluster(4);
  cluster.fit(graph, 2);
  cluster.print();
  std::vector<int> correct_disjoint_sets = {2, 2, 4, 4};
  assert(cluster.getMinSpacing() == 2);
  assert(cluster.getDisjointSets() == correct_disjoint_sets);
  std::cout << "Test passed!" << std::endl;
}

int main() {
  testMaxDistanceClustering();

  runClusteringAssignmentSmall();

  return 0;
}