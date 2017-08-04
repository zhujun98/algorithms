//
// Created by jun on 6/23/17.
//
// Functions:
// - runPrimAssignment()
// - runDijkstraAssignment()
// - runKargerAssignment()
// - runSccAssignment()
//

#ifndef GRAPH_ASSIGNMENTS_H
#define GRAPH_ASSIGNMENTS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "graph_adj.h"
#include "graph_algorithms.h"


namespace assignment {

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
  inline void runPrimAssignment() {
    std::cout << "\n" << std::string(80, '-') << "\n"
              << "This is the Prim assignment in the Stanford's Algorithm course at Coursera"
              << "\n" << std::string(80, '-')
              << std::endl;

    UdGraphAdj<int> graph;

    std::ifstream ifs("../data/edges.txt", std::ifstream::in);
    std::string line;

    // skip the first line
    std::getline(ifs, line);

    while ( std::getline(ifs, line) ) {
      std::istringstream iss(line);
      std::string number;

      int first_node;
      int second_node;
      double weight;
      iss >> number;
      first_node = std::stoi(number);
      iss >> number;
      second_node = std::stoi(number);
      iss >> number;
      weight = std::stoi(number);

      graph.connect(first_node, second_node, weight);

    }

    ifs.close();
    std::cout << "Finished reading data!" << std::endl;

    assert( graph.size() == 500);
    assert( graph.countEdge() == 2184 );

    clock_t t0 = clock();
    std::pair<double, std::vector<std::pair<int, int>>> mst = graph::prim(graph);

    std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
              << " ms" << std::endl;

    assert(int(mst.first) == -3612829);
    std::cout << "Passed!" << std::endl;

    std::cout << "Compare with the Kurlskar's algorithm implementation!" << std::endl;
    t0 = clock();

    mst = graph::kruskal(graph);
    std::cout << "Run time: " << 1000.0*(clock() - t0)/CLOCKS_PER_SEC
              << " ms" << std::endl;
    assert(int(mst.first) == -3612829);

  }

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
  inline void runDijkstraAssignment() {
    std::cout << "\n" << std::string(80, '-') << "\n"
              << "This is the Dijkstra assignment in the Stanford's Algorithm course at Coursera"
              << "\n" << std::string(80, '-')
              << std::endl;

    GraphAdj<int> graph;

    std::ifstream ifs("../data/dijkstraData.txt", std::ifstream::in);
    std::string line;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      std::string number;

      // read the first entry
      iss >> number;
      int vertex = std::stoi(number);

      // read the rest entries
      while ( iss >> number ) {
        std::size_t found = number.find(",");
        int value = std::stoi(number.substr(0, found));
        double length = std::stod(number.substr(found+1, number.size()));
        graph.connect(vertex, value, length);
      }
    }
    ifs.close();
    std::cout << "Finished reading data!" << std::endl;

    std::vector<std::pair<double, int>> shortest_path = graph::dijkstra(graph, 1);

    // compare speeds of different implementations
    clock_t t0;

    t0 = clock();
    graph::dijkstra_base_tree(graph, 1, 1);
    std::cout << "Run time using the tree-based implementation: "
              << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;
    t0 = clock();
    graph::dijkstra_base_priority_queue(graph, 1, 1);
    std::cout << "Run time using the heap-based implementation: "
              << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

    assert(shortest_path[graph.valueToIndex(7)].first == 2599);
    assert(shortest_path[graph.valueToIndex(37)].first == 2610);
    assert(shortest_path[graph.valueToIndex(59)].first == 2947);
    assert(shortest_path[graph.valueToIndex(82)].first == 2052);
    assert(shortest_path[graph.valueToIndex(99)].first == 2367);
    assert(shortest_path[graph.valueToIndex(115)].first == 2399);
    assert(shortest_path[graph.valueToIndex(133)].first == 2029);
    assert(shortest_path[graph.valueToIndex(165)].first == 2442);
    assert(shortest_path[graph.valueToIndex(188)].first == 2505);
    assert(shortest_path[graph.valueToIndex(197)].first == 3068);
    std::cout << "Passed!" << std::endl;
  }

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

    UdGraphAdj<int> graph;

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
      int vertex = std::stoi(number);
      // read the rest entries
      while ( iss >> number ) {
        int value = std::stoi(number);
        graph.connect(vertex, value);
      }
    }
    ifs.close();
    std::cout << "Finished reading data!" << std::endl;

    clock_t t0 = clock();
    assert(graph::karger(graph, repeated_times) == 20);
    std::cout << "Run time: "
              << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;
    std::cout << "Passed!" << std::endl;
  }


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

    GraphAdj<int> graph;

    std::string line;
    std::ifstream ifs("../data/SCC.txt", std::ifstream::in);
    // read the file line by line and put the line into a string
    while ( std::getline(ifs, line) ) {
      std::istringstream iss(line);
      std::string number;

      iss >> number;
      int first = std::stoi(number);
      iss >> number;
      int second = std::stoi(number);

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
    std::vector<std::vector<int>> scc = graph::kosaraju(graph);
    std::cout << "Run time: "
              << 1000.0*(clock() - t0)/CLOCKS_PER_SEC << " ms" << std::endl;

    // print the result
    std::vector<std::size_t> scc_length;

    for (std::size_t i=0; i<scc.size(); ++i) {
      scc_length.push_back(scc[i].size());
    }

    std::sort(scc_length.begin(), scc_length.end(), std::greater<int>());
    assert(scc_length[0] == 434821);
    assert(scc_length[1] == 968);
    assert(scc_length[2] == 459);
    assert(scc_length[3] == 313);
    assert(scc_length[4] == 211);
    std::cout << "Passed!" << std::endl;
  }
};


#endif //GRAPH_ASSIGNMENTS_H
