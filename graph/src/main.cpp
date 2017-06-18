//
// Created by jun on 6/5/17.
//
// Test the Karger's random contraction algorithm on a graph represented
// by adjacency list.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>

#include "graph_adj.h"


//
// contract the graph until only two non-empty linked lists remain
//
// @param graph: UnGraphAdj object
//
// @return: number of edges in the contracted graph
//
int graphContract(UdGraphAdj graph) {

  /* Distribution on which to apply the generator */
  std::vector<int> nonEmptyVertex = graph.getNonEmptyList();

  std::random_device rd;
  std::default_random_engine generator(rd());
  while ( nonEmptyVertex.size() > 2 ) {
    std::uniform_int_distribution<long unsigned> distribution(0, 10000000);
    unsigned long first = distribution(generator) % graph.getNonEmptyList().size();
    unsigned long second = distribution(generator) % (graph.getNonEmptyList().size() - 1);
    if (second >= first) { ++second; }

//    std::cout << nonEmptyVertex[first] << " " << nonEmptyVertex[second] << std::endl;
    graph.collapse(nonEmptyVertex[first], nonEmptyVertex[second]);

    nonEmptyVertex = graph.getNonEmptyList();
//    graph.display();
  }

  return graph.countEdge();
}


//
// build a simple graph for testing
//
//  0---1---4---5
//  | x |   | x |
//  3---2---7---6
//
// the minimum cut is 2.
UdGraphAdj simpleGraph() {
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
// test the graph and the implementation of the Karger's mini-cut algorithm
//
// @param n: number of random contractions.
//
void testKarger(int n) {

  int min_cut = 100;
  int cut;

  // apply Karger's algorithm to find the minimum cut in the graph
  for (int i=0; i<n; ++i) {
    UdGraphAdj graph = simpleGraph();

    cut = graphContract(graph);
    if ( cut < min_cut ) { min_cut = cut; }
  }
  std::cout << "the minimum cut is " << min_cut << std::endl;
}


//
// Find the minimum cut in a graph stored in the file kargerMinCut.txt
// using Karger's random contraction algorithm.
//
// This is the quiz in the Stanford algorithm course in Coursera
//
// @param n: number of random runs
//
void runCourseraQuiz(int n) {
  int min_cut = 1000;
  int cut;
  for (int i=0; i<n; ++i) {
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

    cut = graphContract(graph);
    if ( cut < min_cut ) { min_cut = cut; }
  }

  std::cout << "the minimum cut is: " << min_cut << std::endl;
}


int main() {

  std::cout << "Hello" << std::endl;

  UdGraphAdj graph = simpleGraph();
  graph.display();

//  graph.collapse(0, 1);
//  graph.collapse(1, 2);
//  graph.collapse(3, 2);
//  graph.collapse(4, 5);
//  graph.collapse(5, 6);
//  graph.collapse(6, 7);
//  graph.display();

  testKarger(100);

  runCourseraQuiz(1000);

  return 0;
}