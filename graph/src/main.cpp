//
// Created by jun on 6/19/17.
//
#include <iostream>

#include "graph_adj.h"
#include "karger.h"
#include "korasaju.h"


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
// @param return: a directed graph
//
GraphAdj simpleGraph() {
  GraphAdj graph(10);

  graph.connect(1, 4);
  graph.connect(4, 7);
  graph.connect(7, 1);
  graph.connect(4, 2);
  graph.connect(2, 5);
  graph.connect(5, 8);
  graph.connect(8, 2);
  graph.connect(5, 3);
  graph.connect(3, 6);
  graph.connect(6, 9);
  graph.connect(9, 3);

  return graph;
}

//
//
// Read the data and build an undirected graph in the quiz in the
// Stanford algorithm course in Coursera:
//
// Find the minimum cut in a graph stored in the file kargerMinCut.txt
// using Karger's random contraction algorithm.
//
// @return: undirected graph build by the read-in data
//
UdGraphAdj readKargerData() {
  UdGraphAdj graph(200);

  std::string line;
  // create an input file stream
  std::ifstream fin("../data/kargerMinCut.txt", std::ios::in);

  // read the file line by line and put the line into a string
  while ( std::getline(fin, line) ) {
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

  return graph;

}


int main() {

  std::cout << "Hello" << std::endl;

  // test undirected graph and related implementations
  UdGraphAdj ud_graph = simpleUdGraph();
  ud_graph.display();

  ud_graph.collapse(0, 1);
  ud_graph.collapse(4, 2);
  ud_graph.display();

  karger(ud_graph, 100);

  // coursera course
  UdGraphAdj graph_course = readKargerData();
  karger(graph_course, 1000);

  // test directed graph and related implementations

  GraphAdj graph = simpleGraph();
  graph.display();

  GraphAdj graph_reversed = reverseGraph(graph);
  graph_reversed.display();

  return 0;
}