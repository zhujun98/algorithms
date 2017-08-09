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


/*
 * This file describes a distance function (equivalently, a complete
 * graph with edge costs). It has the following format:
 *
 * [number_of_nodes]
 * [edge 1 node 1] [edge 1 node 2] [edge 1 cost]
 * [edge 2 node 1] [edge 2 node 2] [edge 2 cost]
 * ...
 *
 * There is one edge (i,j) for each choice of 1≤i<j≤n, where n is the
 * number of nodes.
 *
 * Your task in this problem is to run the clustering algorithm from
 * lecture on this data set, where the target number k of clusters is
 * set to 4. What is the maximum spacing of a 4-clustering?
 *
 * Answer: 106
 */
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

int hummingDistance(std::vector<char> src, std::vector<char> dst) {
  assert( src.size() == dst.size() );

  int distance = 0;
  for ( size_t i=0; i<src.size(); ++i ) {
    if ( src[i] != dst[i] ) { ++distance; }
  }

  return distance;
}

/*
 * In this question, a MUCH bigger graph. So big, in fact, that the
 * distances (i.e., edge costs) are only defined implicitly, rather
 * than being provided as an explicit list.
 *
 * The format is:
 *
 * [# of nodes] [# of bits for each node's label]
 * [first bit of node 1] ... [last bit of node 1]
 * [first bit of node 2] ... [last bit of node 2]
 * ...
 *
 * For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1
 * 1 1 1 1 0 1 0 1 1 0 1" denotes the 24 bits associated with node #2.
 *
 * The distance between two nodes u and v in this problem is defined
 * as the Hamming distance --- the number of differing bits --- between
 * the two nodes' labels. For example, the Hamming distance between
 * the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0
 * 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd,
 * 7th, and 21st bits).
 *
 * The question is: what is the largest value of k such that there is
 * a k-clustering with spacing at least 3? That is, how many clusters
 * are needed to ensure that no pair of nodes with all but 2 bits in
 * common get split into different clusters?
 *
 * Answer: 6118
 */
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
  size_t n_pts = std::stoul(number);
  iss0 >> number;
  int n_bits = std::stoi(number);

  typedef std::vector<char> node_value;
  std::vector<node_value> node_values(n_pts);
  Graph graph(n_pts);

  int count = 0;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    char bit;
    node_value value;
    while ( iss >> bit ) {
      value.push_back(bit);
    }
    node_values[count] = value;
    ++count;
  }

  std::cout << "Finish reading data!" << std::endl;
  ifs.close();
}


void testMaxDistanceClustering() {
  size_t size = 4;
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