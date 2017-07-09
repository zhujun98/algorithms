//
// Created by jun on 6/23/17.
//
// Functions:
// - graphContract()
// - karger()
// - kosaraju()
// - dijkstra()
//

#ifndef GRAPH_GRAPH_ALGORITHMS_H
#define GRAPH_GRAPH_ALGORITHMS_H

#include <limits>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>

#include "graph_adj.h"
#include "graph_utilities.h"


namespace graph {
  //
  // contract an undirected graph until only two non-empty linked lists remain
  //
  // @param graph: an undirected graph
  //
  // @return: the number of edges in the contracted graph
  //
  template <class T>
  inline int graphContract(UdGraphAdj<T>& graph, bool display=false) {

    // Distribution on which to apply the generator
    std::vector<T> connected_vertices = graph.getConnectedVertices();

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
  // implementation of the Karger's mini-cut algorithm on an undirected graph
  //
  // @param n: the number of random contractions
  //
  // @return: the number of min cut
  //
  template <class T>
  inline int karger(const UdGraphAdj<T>& graph, unsigned int n) {

    int min_cut = graph.countEdge();
    int cut;

    // apply Karger's algorithm to find the minimum cut in the graph
    for (int i = 0; i < n; ++i) {
      UdGraphAdj<T> graph_copy(graph);

      cut = graphContract(graph_copy);
      if (cut < min_cut) { min_cut = cut; }
    }

    return min_cut;
  }

  //
  // Apply the Kosaraju's algorithm to find the strongly connected components (SCC)
  //
  // @param graph: a directed graph
  //
  // @return: the strongly connected components
  //
  template <class T>
  inline std::vector<std::vector<T>> kosaraju(GraphAdj<T>& graph) {
    // First step, get the reversed graph
    //
    // In order to save space, the original graph is not copied.
    // Therefore, the original graph will be contaminated in the first pass
    GraphAdj<T> graph_reversed = graph::reverseGraph(graph);

    //
    // First pass, recursively run DFS on the original graph.
    // The finish time of each vertex will be store in a stack!!!
    //
    std::stack<T> finish_time;
    for (std::size_t i = 0; i < graph.size(); ++i) {
      if (!graph.getVertexByIndex(i)->visited) {
        std::vector<T> tmp = graph.depthFirstSearch(graph.getVertexByIndex(i)->value);
        for (std::size_t j = 0; j < tmp.size(); ++j) {
          finish_time.push(tmp[j]);
        }
      }
    }

    //
    // Second pass, recursively run DFS using each vertex stored in
    // the stack. The last finished vertex will be track first!
    //
    std::vector<std::vector<T>> scc;
    while (!finish_time.empty()) {
      if (!graph_reversed.getVertex(finish_time.top())->visited) {
        std::vector<T> tmp = graph_reversed.depthFirstSearch(finish_time.top());
        scc.push_back(tmp);
      }
      finish_time.pop();
    }

    return scc;
  }

  //
  // implementation of the Dijkstra's shorted path algorithm without heap
  //
  // @param graph: a directed graph
  // @param start: the starting vertex value
  // @param max_distance: maximum distance from the source. If there is no connection
  //                      between two vertices, the distance between them will be
  //                      represented by "max_distance".
  //
  // @param return: a vector containing the shortest distance between each vertex
  //                to the source
  //
  template <class T>
  inline std::vector<double> dijkstra(const GraphAdj<T> &graph, int start,
                                      double max_distance=std::numeric_limits<double>::max()) {
    // a set of frontier vertices
    std::vector<int> frontier;
    // a set of vertices waiting to be moved into the frontier set
    std::set<int> remain;
    // storing the shortest distance for each vertices
    std::vector<double> shortest_distance(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      remain.insert(i);
      if (i != start) {
        shortest_distance[i] = max_distance;
      } else {
        shortest_distance[i] = 0;
      }
    }

    remain.erase(start);
    frontier.push_back(start);
    // run until there is no vertex left in the remain set
    while ( remain.size() ) {
      int vertex_to_move;  // the vertex to be moved from remain to frontier
      // the minimum distance from the vertices in the remain set to the source
      double current_min_distance = max_distance;
      // loop the frontier vertices
      for (int i=0; i<frontier.size(); ++i) {
        Edge<T> *current_node = graph.getVertex(frontier[i])->next;
        bool remove_from_frontier = true;
        while (current_node) {
          // try to find the vertex in the remain set
          if ( remain.find(current_node->value) != remain.end() ) {
            remove_from_frontier = false;
            double tmp = shortest_distance[frontier[i]] + current_node->distance;
            if (shortest_distance[current_node->value] > tmp) {
              shortest_distance[current_node->value] = tmp;
            }
            if ( tmp < current_min_distance ) {
              vertex_to_move = current_node->value;
              current_min_distance = tmp;
            }
          }
          current_node = current_node->next;
        }
        // if the vertex and all its connected vertices are in the frontier set,
        // remove this vertex from the frontier
        if ( remove_from_frontier ) { frontier.erase(frontier.begin() + i); }

      }

    remain.erase(vertex_to_move);
    frontier.push_back(vertex_to_move);
    }

    return shortest_distance;
  }

}

#endif //GRAPH_GRAPH_ALGORITHMS_H
