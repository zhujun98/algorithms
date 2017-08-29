//
// Created by jun on 8/28/17.
//

#ifndef GRAPH_ASSIGNMENT_SHORTEST_PATH_H
#define GRAPH_ASSIGNMENT_SHORTEST_PATH_H

#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>

#include "../directed_graph.h"
#include "../undirected_graph.h"
#include "../graph_algorithms/dijkstra.h"
#include "../graph_algorithms/bellman_ford.h"


//
// The file contains an adjacency list representation of an undirected
// weighted graph with 200 vertices labeled 1 to 200. Each row consists
// of the node tuples that are adjacent to that particular vertex along
// with the length of that edge. For example, the 6th row has 6 as the
// first entry indicating that this row corresponds to the vertex labeled
// 6. The next entry of this row "141,8200" indicates that there is an
// edge between vertex 6 and vertex 141 that has length 8200. The rest
// of the pairs of this row indicate the other vertices adjacent to
// vertex 6 and the lengths of the corresponding edges.

// Your task is to run Dijkstra's shortest-path algorithm on this graph,
// using 1 (the first vertex) as the source vertex, and to compute the
// shortest-path distances between 1 and every other vertex of the graph.
// If there is no path between a vertex v and vertex 1, we'll define the
// shortest-path distance between 1 and v to be 1000000.

// You should report the shortest-path distances to the following ten
// vertices, in order: 7,37,59,82,99,115,133,165,188,197. You should
// encode the distances as a comma-separated string of integers. So if
// you find that all ten of these vertices except 115 are at distance
// 1000 away from vertex 1 and 115 is 2000 distance away, then your
// answer should be 1000,1000,1000,1000,1000,2000,1000,1000,1000,1000.
//
// Answer: 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
//
void runShortestPathAssignment() {
  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the Dijkstra assignment in the Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  UndirectedGraph<unsigned long> graph(200);

  std::ifstream ifs("../data/dijkstraData.txt", std::ifstream::in);
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    std::string number;

    // read the first entry
    iss >> number;
    size_t src = std::stoull(number) - 1;

    // read the rest entries
    while ( iss >> number ) {
      std::size_t found = number.find(",");
      size_t dst = std::stoull(number.substr(0, found)) - 1;
      size_t length = std::stoull(number.substr(found+1, number.size()));
      graph.connect(src, dst, length);
    }
  }
  ifs.close();
  std::cout << "Finished reading data!" << std::endl;

  size_t src = 1;
  // the vertex in the graph starts from 0
  auto shortest_path = dijkstra(graph, src - 1);

  std::deque<size_t> destinations {6, 36, 58, 81, 98, 114, 132, 164, 187, 196};
  std::deque<unsigned long> expected_answer
      {2599, 2610, 2947, 2052, 2367, 2399, 2029, 2442, 2505, 3068};

  // compare speeds of different implementations
  std::deque<unsigned long> solutions;

  clock_t t0;

  t0 = clock();
  auto shortest_path1 = dijkstraOriginal(graph, 0, 0);
  solutions.clear();
  for (auto v : destinations) { solutions.push_back(shortest_path1.first[v]); }
  assert(solutions == expected_answer);
  std::cout << "Run time using the original implementation: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

  t0 = clock();
  auto shortest_path2 = dijkstraPriorityQueueBase(graph, 0, 0);
  solutions.clear();
  for (auto v : destinations) { solutions.push_back(shortest_path2.first[v]); }
  assert(solutions == expected_answer);
  std::cout << "Run time using the priority-queue-based implementation: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

  t0 = clock();
  auto shortest_path3 = dijkstraTreeBase(graph, 0, 0);
  solutions.clear();
  for (auto v : destinations) { solutions.push_back(shortest_path3.first[v]); }
  assert(solutions == expected_answer);
  std::cout << "Run time using the tree-based implementation: "
            << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

  std::cout << "Passed!" << std::endl;
}

#endif //GRAPH_ASSIGNMENT_SHORTEST_PATH_H
