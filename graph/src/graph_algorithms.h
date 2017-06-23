//
// Created by jun on 6/23/17.
//
// Functions:
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
  // implementation of the Karger's mini-cut algorithm on an undirected graph
  //
  // @param n: number of random contractions
  //
  // @return: number of min cut
  //
  inline int karger(const UdGraphAdj &graph, unsigned int n) {

    int min_cut = graph.countEdge();
    int cut;

    // apply Karger's algorithm to find the minimum cut in the graph
    for (int i = 0; i < n; ++i) {
      UdGraphAdj copy = copyGraph(graph);

      cut = graphContract(copy);
      if (cut < min_cut) { min_cut = cut; }
    }

    return min_cut;
  }

  struct Dist {
    int vertex;
    double distance;

    friend bool operator<(Dist a, Dist b) {
      return a.distance > b.distance;
    }
  };


  //
  // Apply the Kosaraju's algorithm to find the strongly connected components (SCC)
  //
  // @param graph: a directed graph
  //
  // @return: strongly connected components
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


  //
  // implementation of the Dijkstra's shorted path algorithm without heap
  //
  // @param graph: GraphAdj object
  // @param source: starting vertex value
  // @param max_distance: maximum distance from the source. If there is no connection
  //                      between two vertices, the distance between them will be
  //                      represented by "max_distance".
  //
  // @param return: a vector containing the shortest distance between each vertex
  //                to the source
  //
  inline std::vector<double> dijkstra(const GraphAdj &graph, int source,
                                      double max_distance=std::numeric_limits<double>::max()) {
    // a set of frontier vertices
    std::vector<int> frontier;
    // a set of vertices waiting to be moved into the frontier set
    std::set<int> remain;
    // storing the shortest distance for each vertices
    std::vector<double> shortest_distance(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      remain.insert(i);
      if (i != source) {
        shortest_distance[i] = max_distance;
      } else {
        shortest_distance[i] = 0;
      }
    }

    remain.erase(source);
    frontier.push_back(source);
    // run until there is no vertex left in the remain set
    while ( remain.size() ) {
      int vertex_to_move;  // the vertex to be moved from remain to frontier
      // the minimum distance from the vertices in the remain set to the source
      double current_min_distance = max_distance;
      // loop the frontier vertices
      for (int i=0; i<frontier.size(); ++i) {
        AdjListNode *current_node = graph.getVertex(frontier[i]).head;
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
