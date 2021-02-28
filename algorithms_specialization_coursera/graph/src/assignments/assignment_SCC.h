//
// Created by jun on 8/29/17.
//

#ifndef GRAPH_ASSIGNMENT_SCC_H
#define GRAPH_ASSIGNMENT_SCC_H

#include <cassert>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "../graph_algorithms/kosaraju.h"
#include "../directed_graph.h"


//
// The file contains the edges of a directed graph. Vertices are labeled
// as positive integers from 1 to 875714. Every row indicates an edge, the
// vertex label in first column is the tail and the vertex label in second
// column is the head (the edge points from tail to head).
//
// Output Format: You should output the sizes of the 5 largest strongly
// connected components in the given graph, in decreasing order of sizes,
// separated by commas.
//
// Answer: 434821,968,459,313,211
//
inline void runSccAssignment() {

  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the SCC assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  typedef long weight_t;
  DirectedGraph<weight_t> graph(875714);

  std::string line;
  std::ifstream ifs("../data/SCC.txt", std::ifstream::in);
  // read the file line by line and put the line into a string
  while ( std::getline(ifs, line) ) {
    std::istringstream iss(line);
    std::string number;

    iss >> number;
    size_t first = std::stoull(number) - 1;
    iss >> number;
    size_t second = std::stoull(number) - 1;

    if ( first == second ) {
      std::cout << "Warning: Find a line with two identical numbers: "
                << first << " " << second << std::endl;
    } else {
      graph.connect(first, second);
    }
    graph.connect(1, 2);
  }
  ifs.close();
  std::cout << "Finished reading data!" << std::endl;

  std::cout << "Searching strongly connected components...!" << std::endl;
  clock_t t0 = clock();
  std::deque<std::deque<size_t>> scc = kosaraju(graph);
  std::cout << "Run time: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

  // print the result
  std::vector<std::size_t> scc_length;

  for (const auto& v: scc) { scc_length.push_back(v.size()); }

  std::sort(scc_length.begin(), scc_length.end(), std::greater<int>());
  assert(scc_length[0] == 434821);
  assert(scc_length[1] == 968);
  assert(scc_length[2] == 459);
  assert(scc_length[3] == 313);
  assert(scc_length[4] == 211);
  std::cout << "Passed!" << std::endl;
}

#endif //GRAPH_ASSIGNMENT_SCC_H
