//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_ASSIGNMENT_MST_H
#define GRAPH_ASSIGNMENT_MST_H

#include <cassert>
#include <sstream>
#include <fstream>

#include "../graph_algorithms/prim.h"
#include "../graph_algorithms/kruskal.h"
#include "../undirected_graph.h"

//
// In this programming problem you'll code up Prim's minimum spanning
// tree algorithm.
//
// The data file "edges.txt" describes an undirected graph with
// integer edge costs. It has the format
//
// [number_of_nodes] [number_of_edges]
// [one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]
// [one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
// ...
//
// You should NOT assume that edge costs are positive, nor should you
// assume that they are distinct.
// Your task is to run Prim's minimum spanning tree algorithm on this
// graph. You should report the overall cost of a minimum spanning
// tree --- an integer, which may or may not be negative.
//
// Answer: -3612829
//
void runPrimAssignment() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the Prim assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;
  typedef long weight_t;
  UndirectedGraph<weight_t> graph(500);

  std::ifstream ifs("../data/edges.txt", std::ifstream::in);
  std::string line;

  // skip the first line
  std::getline(ifs, line);

  while ( std::getline(ifs, line) ) {
    std::istringstream iss(line);
    std::string number;

    size_t src;
    size_t dst;
    weight_t weight;
    iss >> number;
    src = std::stoull(number) - 1;
    iss >> number;
    dst = std::stoull(number) - 1;
    iss >> number;
    weight = (weight_t)(std::stol(number));

    graph.connect(src, dst, weight);

  }

  ifs.close();
  std::cout << "Finished reading data!" << std::endl;

  assert( graph.size() == 500);
  assert( graph.countEdge() == 2184 );

  clock_t t0 = clock();
  std::pair<weight_t, std::vector<std::pair<size_t, size_t>>> mst = prim(graph, 0);

  std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
            << " ms" << std::endl;

  assert(mst.first == -3612829);
  std::cout << "Passed!" << std::endl;

  std::cout << "Compare with Kurlskar's algorithm!" << std::endl;
  t0 = clock();

  mst = kruskal(graph);
  std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
            << " ms" << std::endl;
  assert(mst.first == -3612829);

}

#endif //GRAPH_ASSIGNMENT_MST_H
