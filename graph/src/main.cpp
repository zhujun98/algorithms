//
// Created by jun on 6/5/17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "graph.h"


//
// Step 1: Find the common vertices connected to i, j
// Step 2: Remove j from these vertices's connections
// Step 3: Merge vertices in j to i, and increase the weight of common vertices by 1
// Step 4: Remove vertex j
//
int contractEdge(int i, int j) {

}


int main() {

  std::cout << "Hello" << std::endl;

//  std::string line;
//  // create an input file stream
//  std::ifstream fin("../data/kargerMinCut.txt", std::ios::in);
//
//  // read the file line by line and put the line into a string
//  while ( std::getline(fin, line) ) {
//    std::istringstream iss(line);
//    std::string number;
//
//    while ( iss >> number ) {
//      int value = std::stoi(number);
//      std::cout << value << std::endl;
//
//    }
//
//  }

  Graph graph(5);
  graph.addEdge(0, 1);
  graph.addEdge(0, 4);
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);

  // print the adjacency list representation of the above graph
  graph.printGraph();

//  graph.delEdge(1, 4);
//  graph.delEdge(1, 3);

  graph.delVertexEdge(1);
  graph.delVertexEdge(0);
  graph.delVertexEdge(2);

  graph.printGraph();

  return 0;
}