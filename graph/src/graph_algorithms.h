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
#include <list>
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
  // @param destination: the destination vertex value. Search for the entire
  //                     graph if destination == source
  // @param max_distance: maximum distance from the source. If there is no
  //                      connection between two vertices, the distance
  //                      between them will be represented by "max_distance".
  //
  // @param return: a vector containing a pair of the shortest distance
  //                between each vertex to the source as well as the previous
  //                vertex of each vertex.
  //
  template <class T>
  inline std::vector<std::pair<double, T>> dijkstra_base(
      const GraphAdj<T> &graph, T source, T destination,
      double max_distance=std::numeric_limits<double>::max()) {
    if ( !graph.getVertex(source) ) {
      std::cout << source << " is not a vertex of the graph!" << std::endl;
      return {};
    }
    if ( !graph.getVertex(destination) ) {
      std::cout << destination << " is not a vertex of the graph!" << std::endl;
      return {};
    }

    // a set of vertex indices waiting to removed one by one
    std::set<int> remain;  // look up complexity O(log(n))
    // storing the shortest distance for each vertices
    std::vector<std::pair<double, T>> shortest_path(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      remain.insert(i);
      if (graph.getVertexByIndex(i)->value != source) {
        shortest_path[i].first = max_distance;
      } else {
        shortest_path[i].first = 0;
        shortest_path[i].second = source;
      }
    }

    // run until there is no vertex left in the remain set
    while ( !remain.empty() ) {
      // pick the index in the 'remain' set with the shortest distance
      double current_min_distance = max_distance;
      int selected_index = -1;
      for ( auto it = remain.begin(); it != remain.end(); ++it ) {
        if ( shortest_path[*it].first < current_min_distance ) {
          current_min_distance = shortest_path[*it].first;
          selected_index = *it;
        }
      }

      if ( source != destination &&
           selected_index == graph.getVertexIndex(destination) ) {
        return shortest_path;
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
          double tmp = shortest_path[selected_index].first + current_edge->distance;
          if (shortest_path[currentIndex].first > tmp) {
            shortest_path[currentIndex].first = tmp;
            shortest_path[currentIndex].second = graph.getVertexByIndex(selected_index)->value;
          }
        }
        current_edge = current_edge->next;
      }
    }

    return shortest_path;
  }

  //
  // Explore the entire graph using dijkstra's algorithm
  //
  template <class T>
  inline std::vector<std::pair<double, T>> dijkstra(
      const GraphAdj<T> &graph, T source,
      double max_distance=std::numeric_limits<double>::max()) {

    return dijkstra_base(graph, source, source, max_distance);
  }

  //
  // Looking for the shortest path between source and destination
  //
  template <class T>
  inline std::pair<std::list<T>, double> dijkstra(
      const GraphAdj<T> &graph, T source, T destination,
      double max_distance=std::numeric_limits<double>::max()) {

    std::vector<std::pair<double, T>> shortest_path =
        dijkstra_base(graph, source, destination, max_distance);

    std::pair<std::list<T>, double> shortest_path_destination;

    int destination_index = graph.getVertexIndex(destination);
    shortest_path_destination.second = shortest_path[destination_index].first;

    T current_vertex = destination;
    shortest_path_destination.first.push_front(current_vertex);
    while ( true ) {
      current_vertex = shortest_path[graph.getVertexIndex(current_vertex)].second;
      shortest_path_destination.first.push_front(current_vertex);
      if ( current_vertex == source ) { break; }
    }

    return shortest_path_destination;
  };

}

#endif //GRAPH_GRAPH_ALGORITHMS_H
