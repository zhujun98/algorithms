//
// Created by jun on 6/23/17.
//
// Functions:
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
              << "\n" << std::string(80, '-') << "\n"
              << std::endl;

    GraphAdj<int> graph;

    std::ifstream ifs("../data/dijkstraData.txt", std::ifstream::in);
    std::string line;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      std::string number;
      int flag = 0;
      int vertex;
      while ( iss >> number ) {
        if ( flag == 0 ) {
          vertex = std::stoi(number) - 1;
          flag = 1;
        } else {
          std::size_t found = number.find(",");
          int value = std::stoi(number.substr(0, found));
          double distance = std::stod(number.substr(found+1, number.size()));
          graph.connect(vertex, value-1, 1, distance);
        };
      }
    }
    ifs.close();

    std::cout << "Finished reading data!" << std::endl;

    std::vector<double> shortest_distance = graph::dijkstra(graph, 0);

    std::cout << "The shortest distance to vertex" << std::endl;
    std::cout << "7,37,59,82,99,115,133,165,188,197" << std::endl;
    std::cout << "are: " << std::endl;

    std::cout << shortest_distance[6] << "," << shortest_distance[36] << ","
              << shortest_distance[58] << "," << shortest_distance[81] << ","
              << shortest_distance[98] << "," << shortest_distance[114] << ","
              << shortest_distance[132] << "," << shortest_distance[164] << ","
              << shortest_distance[187] << "," << shortest_distance[196];
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
  inline void runKargerAssignment(unsigned int repeated_times=10000) {

    std::cout << "\n" << std::string(80, '-') << "\n"
              << "This is the minimum cut assignment in the Stanford's Algorithm course at Coursera"
              << "\n" << std::string(80, '-') << "\n"
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

      int flag = 0;
      int vertex;
      while ( iss >> number ) {
        int value = std::stoi(number);
        if ( flag == 0 ) {
          vertex = value - 1;
          flag = 1;
        } else {
          graph.connect(vertex, value - 1);
        }
      }
    }
    ifs.close();

    std::cout << "Finished reading data!" << std::endl;

    std::cout << "The minimum cut is: "
              << graph::karger(graph, repeated_times) << std::endl;
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
              << "\n" << std::string(80, '-') << "\n"
              << std::endl;

    GraphAdj<int> graph;

    std::string line;
    std::ifstream ifs("../data/SCC.txt", std::ifstream::in);
    // read the file line by line and put the line into a string
    while ( std::getline(ifs, line) ) {
      std::istringstream iss(line);
      std::string number;

      int count = 0;
      int first = -1;
      int second = -1;
      while ( iss >> number ) {

        if ( count == 0 ) {
          first = std::stoi(number);
        } else if ( count == 1 ) {
          second = std::stoi(number);
        } else {
          continue;
        };

        ++count;
      }

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
    std::vector<std::vector<int>> scc = graph::kosaraju(graph);

    // print the result
    std::vector<std::size_t> scc_length;

    for (std::size_t i=0; i<scc.size(); ++i) {
      scc_length.push_back(scc[i].size());
    }

    std::sort(scc_length.begin(), scc_length.end(), std::greater<int>());

    int count = 0;
    std::cout << "The lengths of the five longest SCCs are: " << std::endl;
    while ( count < 5 && count < scc_length.size() ) {
      std::cout << scc_length[count] << ",";
      ++count;
    }
    std::cout << std::endl;
  }

};


#endif //GRAPH_ASSIGNMENTS_H
