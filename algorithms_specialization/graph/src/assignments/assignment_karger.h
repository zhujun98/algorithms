//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_ASSIGNMENT_KARGER_H
#define GRAPH_ASSIGNMENT_KARGER_H

#include <cassert>
#include <sstream>
#include <fstream>

#include "../graph_algorithms/karger.h"


//
// The file contains the adjacency list representation of a simple undirected
// graph. There are 200 vertices labeled 1 to 200. The first column in the file
// represents the vertex label, and the particular row (other entries except
// the first column) tells all the vertices that the vertex is adjacent to.
// So for example, the 6th row looks like : "6	155	56	52	120	......". This
// just means that the vertex with label 6 is adjacent to (i.e., shares an
// edge with) the vertices with labels 155, 56, 52, 120,......,etc
//
// Your task is to code up and run the Karger's randomized contraction algorithm
// for the min cut problem and use it on the above graph to compute the min cut.
//
// @param repeated_times: how many times the random contraction will be performed
//
// TODO:: check the answer
inline void runKargerAssignment(unsigned int repeated_times=1000) {

  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the minimum cut assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  typedef long weight_t;
  UndirectedGraph<weight_t> graph;

  std::string line;
  // create an input file stream
  std::ifstream ifs("../data/kargerMinCut.txt", std::ifstream::in);

  std::cout << "Run the random contract for " << repeated_times
            << " times..." << std::endl;
  // read the file line by line and put the line into a string
  while ( std::getline(ifs, line) ) {
    std::istringstream iss(line);
    std::string number;

    // read the first entry in a line
    iss >> number;
    size_t src = std::stoull(number) - 1;
    std::cout << src << std::endl;
    // read the rest entries
    while ( iss >> number ) {
      size_t dst = std::stoull(number) - 1;
      std::cout << dst << std::endl;
      graph.connect(src, dst);
    }
  }
  ifs.close();
  std::cout << "Finished reading data!" << std::endl;

  clock_t t0 = clock();
  assert(karger(graph, repeated_times) == 20);
  std::cout << "Run time: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;
  std::cout << "Passed!" << std::endl;
}

#endif //GRAPH_ASSIGNMENT_KARGER_H
