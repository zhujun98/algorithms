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
  // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
  //
  // @param graph: a directed graph
  // @param source: the starting vertex value
  // @param max_distance: maximum distance from the source. If there is no connection
  //                      between two vertices, the distance between them will be
  //                      represented by "max_distance".
  //
  // @param return: a vector containing the shortest distance between each vertex
  //                to the source
  //
  template <class T>
  inline std::vector<double> dijkstra(const GraphAdj<T> &graph, T source,
                                      double max_distance=std::numeric_limits<double>::max()) {
    if ( !graph.getVertex(source) ) {
      std::cout << source << " is not a vertex of the graph!" << std::endl;
      return {};
    }

    // a set of vertex indices waiting to removed one by one
    std::set<int> remain;  // look up complexity O(log(n))
    // storing the shortest distance for each vertices
    std::vector<double> shortest_distance(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      remain.insert(i);
      if (graph.getVertexByIndex(i)->value != source) {
        shortest_distance[i] = max_distance;
      } else {
        shortest_distance[i] = 0;
      }
    }

    // run until there is no vertex left in the remain set
    while ( !remain.empty() ) {
      // pick the index in the 'remain' set with the shortest distance
      double current_min_distance = max_distance;
      int selected_index = -1;
      for ( auto it = remain.begin(); it != remain.end(); ++it ) {
        if ( shortest_distance[*it] < current_min_distance ) {
          current_min_distance = shortest_distance[*it];
          selected_index = *it;
        }
      }

      remain.erase(selected_index);

      // Loop the neighbors of the "selected_index" which is still in the
      // "remain" set.
      Edge<T> *current_edge = graph.getVertexByIndex(selected_index)->next;
      while (current_edge) {
        int currentIndex = graph.getVertexIndex(current_edge->value);
        // check whether the vertex is in the remain set
        if ( remain.find(currentIndex) != remain.end() ) {
          // update shortest distance information
          double tmp = shortest_distance[selected_index] + current_edge->distance;
          if (shortest_distance[currentIndex] > tmp) {
            shortest_distance[currentIndex] = tmp;
          }
        }
        current_edge = current_edge->next;
      }

    }

    return shortest_distance;
  }

}

#endif //GRAPH_GRAPH_ALGORITHMS_H
