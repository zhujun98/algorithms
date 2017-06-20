//
// Created by jun on 6/19/17.
//

#ifndef GRAPH_GRAPH_UTILITIES_H
#define GRAPH_GRAPH_UTILITIES_H

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>

#include "graph_adj.h"


namespace graph {

  //
  // copy a graph
  //
  // @param graph: original graph (could be directed or undirected)
  //
  // @param return: copied graph
  //
  template <class G>
  inline G copyGraph(const G& graph) {
    std::size_t g_size = graph.size();
    G g_copy(g_size);

    for(std::size_t i=0; i<g_size; ++i) {
      graph::AdjListNode* current = graph.getVertex(i).head;
      while ( current ) {
        g_copy.connect(i, current->value);
        current = current->next;
      }
    }

    return g_copy;
  }

  //
  // contract an undirected graph until only two non-empty linked lists remain
  //
  // @param graph: UnGraphAdj object
  //
  // @return: number of edges in the contracted graph
  //
  inline int graphContract(UdGraphAdj& graph, bool display=false) {

    /* Distribution on which to apply the generator */
    std::vector<int> connected_vertices = graph.getConnectedVertices();

    std::random_device rd;
    std::default_random_engine generator(rd());
    while ( connected_vertices.size() > 2 ) {
      std::uniform_int_distribution<long unsigned> distribution(0, 10000000);

      unsigned long first = distribution(generator) % connected_vertices.size();
      unsigned long second = distribution(generator) % (connected_vertices.size() - 1);
      if (second >= first) { ++second; }

      if ( display ) {
        std::cout << connected_vertices[first] << " " << connected_vertices[second] << std::endl;
      }
      graph.collapse(connected_vertices[first], connected_vertices[second]);

      connected_vertices = graph.getConnectedVertices();
      if ( display) { graph.display(); }
    }

    return graph.countEdge();
  }

  //
  // test the graph and the implementation of the Karger's mini-cut algorithm
  //
  // @param n: number of random contractions.
  //
  inline void karger(const UdGraphAdj& graph, unsigned int n) {

    int min_cut = 100;
    int cut;

    // apply Karger's algorithm to find the minimum cut in the graph
    for (int i=0; i<n; ++i) {
      UdGraphAdj copy = copyGraph(graph);

      cut = graphContract(copy);
      if ( cut < min_cut ) { min_cut = cut; }
    }
    std::cout << "\nthe minimum cut is " << min_cut << std::endl;
  }

  //
  // reverse a directed graph
  //
  // @param graph: original graph
  //
  // @param return: reversed graph
  //
  inline GraphAdj reverseGraph(const GraphAdj& graph) {
    std::size_t g_size = graph.size();
    GraphAdj reversed(g_size);

    for (std::size_t i=0; i<g_size; ++i) {
      graph::AdjListNode* current = graph.getVertex(i).head;
      while ( current ) {
        reversed.connect(current->value, i);
        current = current->next;
      }
    }

    return reversed;
  }


  template <class V>
  inline void printSCC(V scc) {
    std::vector<std::size_t> scc_length;

    std::cout << "\nStrongly connected components with more than one element: " << std::endl;
    for (std::size_t i=0; i<scc.size(); ++i) {
      if ( scc[i].size() > 1 ) {
        scc_length.push_back(scc[i].size());

        for (std::size_t j = 0; j < scc[i].size(); ++j) {
          std::cout << scc[i][j] << " ";
        }
        std::cout << std::endl;
      }
    }

    std::sort(scc_length.begin(), scc_length.end(), std::greater<int>());

    int count = 0;
    std::cout << "\nThe lengths of the five longest SCCs (if any) are: " << std::endl;
    while ( count < 5 && count < scc_length.size() ) {
      std::cout << scc_length[count] << ",";
      ++count;
    }
    std::cout << std::endl;
  }


  //
  // Apply the Kosaraju's algorithm to find the strongly connected components (SCC)
  //
  inline std::vector<std::vector<int>> kosaraju(GraphAdj& graph) {
    // First step, get the reversed graph
    //
    // In order to save space, the original graph is not copied.
    // Therefore, the original graph will be contaminated in the first pass
    GraphAdj graph_reversed = reverseGraph(graph);

    //
    // First pass, recursively run DFS on the original graph.
    // The finish time of each vertex will be store in a stack!!!
    //
    std::stack<int> finish_time;
    for (std::size_t i = 0; i < graph.size(); ++i) {
      if (!graph.getVertex(i).visited) {
        std::vector<int> tmp = graph.DFS(i);
        for (std::size_t j = 0; j < tmp.size(); ++j) {
          finish_time.push(tmp[j]);
        }
      }
    }

    // For debug
//    while ( !finish_time.empty() ) {
//      std::cout << finish_time.top() << " ";
//      finish_time.pop();
//    }
//    std::cout << std::endl;

    //
    // Second pass, recursively run DFS using each vertex stored in
    // the stack. The last finished vertex will be track first!
    //
    std::vector<std::vector<int>> scc;
    while (!finish_time.empty()) {
      if (!graph_reversed.getVertex(finish_time.top()).visited) {
        std::vector<int> tmp = graph_reversed.DFS(finish_time.top());
        scc.push_back(tmp);
      }
      finish_time.pop();
    }

    return scc;
  }

}  // namespace graph

#endif // GRAPH_GRAPH_UTILITIES_H
