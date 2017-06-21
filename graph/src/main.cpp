//
// Created by jun on 6/19/17.
//
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph_adj.h"
#include "graph_utilities.h"


//
// build a simple undirected graph for testing
//
//  0---1---4---5
//  | x |   | x |
//  3---2---7---6
//
// the minimum cut is 2.
//
// @param return: an undirected graph
//
UdGraphAdj simpleUdGraph() {
  UdGraphAdj graph(8);

  graph.connect(0, 1);
  graph.connect(1, 2);
  graph.connect(2, 3);
  graph.connect(3, 0);
  graph.connect(0, 2);
  graph.connect(1, 3);
  graph.connect(4, 5);
  graph.connect(5, 6);
  graph.connect(6, 7);
  graph.connect(7, 4);
  graph.connect(4, 6);
  graph.connect(5, 7);
  graph.connect(1, 4);
  graph.connect(2, 7);

  return graph;
}

//
// build a simple directed graph for testing
//
// The annotation "0 *- 3" means from 0 to 3.
//
// 0  *-  3 *- 1  *-  4  *-  2  *-  5
//  \    *      \    *        \    *
//   *  /        *  /          *  /
//     6           7             8
// @param return: a directed graph
//
GraphAdj simpleGraph() {
  GraphAdj graph(9);

  graph.connect(0, 3);
  graph.connect(3, 6);
  graph.connect(6, 0);
  graph.connect(3, 1);
  graph.connect(1, 4);
  graph.connect(4, 7);
  graph.connect(7, 1);
  graph.connect(4, 2);
  graph.connect(2, 5);
  graph.connect(5, 8);
  graph.connect(8, 2);

  return graph;
}

//
// Read the data and build an undirected graph in the quiz in the
// Stanford algorithm course in Coursera:
//
// Find the minimum cut in a graph stored in the file kargerMinCut.txt
// using Karger's random contraction algorithm.
//
void runKargerAssignment() {
  UdGraphAdj graph(200);

  std::string line;
  // create an input file stream
  std::ifstream ifs("../data/kargerMinCut.txt", std::ifstream::in);

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

  graph::karger(graph, 1000);

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
void runSccAssignment() {
  GraphAdj graph(875714);

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
      std::cout << "Find a line with two identical numbers: "
                << first << " " << second << std::endl;
    } else {
      graph.connect(first - 1, second - 1);
    }
    graph.connect(1, 2);
  }
  ifs.close();

  std::cout << "Finished reading data!" << std::endl;

  std::cout << "Searching strongly connected components...!" << std::endl;
  std::vector<std::vector<int>> scc = graph::kosaraju(graph);

  // print scc
  graph::printSCC(scc);
}


int main() {

  std::cout << "Hello" << std::endl;

  // test undirected graph and related implementations
  UdGraphAdj ud_graph = simpleUdGraph();
  ud_graph.display();

  graph::karger(ud_graph, 100);

  // test directed graph and related implementations

  GraphAdj graph = simpleGraph();
  graph.display();

  std::vector<int> visited;
  visited = graph.BFS(5);
  for (int i=0; i<visited.size(); ++i) {
    std::cout << visited[i] << std::endl;
  }

  std::vector<std::vector<int>> scc = graph::kosaraju(graph);

  // print scc
  graph::printSCC(scc);

  runKargerAssignment();

  runSccAssignment();

  return 0;
}