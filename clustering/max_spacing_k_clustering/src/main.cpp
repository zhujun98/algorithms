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
  Graph graph(n_pts);

  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    iss >> number;
    int src = std::stoi(number) - 1;
    iss >> number;
    int dst = std::stoi(number) - 1;
    iss >> number;
    double weight = std::stod(number);

    graph.setEdge(src, dst, weight);
  }

  std::cout << "Finish reading data!" << std::endl;
  ifs.close();

  std::cout << "With pass compression algorithm" << std::endl;
  clock_t t0 = clock();
  MaxDistanceClustering cluster;
  cluster.setUsePathCompression(true);
  cluster.fit(graph, 4);
  std::cout << "Run time: " << 1.0e-6*(clock() - t0)*CLOCKS_PER_SEC
            << " ms" << std::endl;
//  cluster.print();
  assert(cluster.getMinSpacing() == 106);

  std::cout << "Without pass compression algorithm" << std::endl;
  t0 = clock();
  graph.resetGraph();
  cluster.setUsePathCompression(false);
  cluster.fit(graph, 4);
  std::cout << "Run time: " << 1.0e-6*(clock() - t0)*CLOCKS_PER_SEC
            << " ms" << std::endl;
  assert(cluster.getMinSpacing() == 106);

  std::cout << "Passed!" << std::endl;
}


void runClusteringAssignmentBig() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the clustring assignment (big data set) \n"
            << "in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::ifstream ifs("../data/clustering_big.txt", std::ifstream::in);

  std::string line;
  std::string number;

  // read the first line
  std::getline(ifs, line);
  std::istringstream iss0(line);
  iss0 >> number;
  int n_pts = std::stoi(number);
  iss0 >> number;
  int n_bits = std::stoi(number);

  typedef std::vector<char> node_value;
  Graph graph(n_pts);

  int index = 0;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    char bit;
    node_value value;
    while ( iss >> bit ) {
      value.push_back(bit);
    }
  }

  std::cout << "Finish reading data!" << std::endl;
  ifs.close();

}


void testMaxDistanceClustering() {
  int size = 4;
  Graph graph(size);

  graph.setEdge(0, 1, 1);
  graph.setEdge(0, 2, 2);
  graph.setEdge(0, 3, 3);
  graph.setEdge(1, 2, 2);
  graph.setEdge(1, 3, 4);
  graph.setEdge(2, 3, 2);

  MaxDistanceClustering cluster;
  cluster.fit(graph, 2);
  cluster.print();
  std::vector<int> correct_disjoint_sets0 = {1, 1, 3, 3};
  assert(cluster.getMinSpacing() == 2);
  assert(cluster.getDisjointSets() == correct_disjoint_sets0);

  graph.resetGraph();
  cluster.setUsePathCompression(false);
  cluster.fit(graph, 2);
  cluster.print();
  std::vector<int> correct_disjoint_sets1 = {1, 1, 1, 3};
  assert(cluster.getMinSpacing() == 2);
  assert(cluster.getDisjointSets() == correct_disjoint_sets1);
  std::cout << "Test passed!" << std::endl;
}

int main() {
  testMaxDistanceClustering();

  runClusteringAssignmentSmall();

  runClusteringAssignmentBig();

  return 0;
}