//
// Created by jun on 6/23/17.
//
// Implementations of different graph algorithms/operations:
// - breathFirstSearch
// - depthFirstSearch
// - graphContract
// - Karger's algorithm
// - Kosaraju's algorithm
// - Dijkstra's algorithm
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
  // Breath-first-search (BFS) starting from a vertex
  //
  // @param graph: graph object
  // @param vertex: the starting vertex value
  //
  // @return: a vector of visited vertices, ordered by finding time
  //
  template <class G, class T>
  std::vector<T> breathFirstSearch(const G& graph, T value) {
    graph::GraphAdjVertex<T> const* v = graph.getVertex(value);
    if ( !v ) { return {}; }

    // the container for visited vertices in finding sequence
    std::vector<T> search;
    std::queue<T> track;
    std::vector<bool> visited (graph.size(), false);

    track.push(value);
    search.push_back(value);
    visited[graph.vertexToIndex(value)] = true;
    while (!track.empty()) {
      graph::GraphAdjVertex<T> const* current_head = graph.getVertex(track.front());
      track.pop();

      graph::Edge<T>* current_node = current_head->next;
      // find all children vertices which have not been visited yet
      while (current_node) {
        if ( !visited[graph.vertexToIndex(current_node->value)] ) {
          track.push(current_node->value);
          search.push_back(current_node->value);
          visited[graph.vertexToIndex(current_node->value)] = true;
        }
        current_node = current_node->next;
      }
    }

    return search;
  }

  //
  // Depth-first-search (DFS) starting from a vertex
  //
  // @param graph: graph object
  // @param value: starting vertex value
  // @param visited: An indicator which indicates whether a vertex has
  //                 been visited.
  //
  // @return: a vector of sink vertices, ordered by finding time
  //
  template <class G, class T>
  std::vector<T> depthFirstSearch(const G& graph, T value, std::vector<bool>& visited) {
    assert( graph.size() == visited.size() );

    graph::GraphAdjVertex<T> const* v = graph.getVertex(value);
    if ( !v ) { return {}; }

    // the container for sink vertices in finding sequence
    std::vector<T> sink;
    std::stack<T> tracker;

    tracker.push(value);
    T current_vertex_value;
    // search the vertex reachable from the current vertex
    while ( !tracker.empty() ) {
      current_vertex_value = tracker.top();
      visited[graph.vertexToIndex(current_vertex_value)] = true;

      bool retreat = true;  // a flag indicating whether to retreat to the last vertex
      graph::Edge<T>* current_node = graph.getVertex(current_vertex_value)->next;
      // find the next reachable vertex which has not been visited
      while ( current_node ) {
        if ( !visited[graph.vertexToIndex(current_node->value)] ) {
          tracker.push(current_node->value);
          retreat = false;
          break;
        }
        current_node = current_node->next;
      }
      // if a sink vertex is found
      if ( retreat ) {
        sink.push_back(current_vertex_value);
        tracker.pop();
      }

    }

    return sink;
  }

  template <class G, class T>
  std::vector<T> depthFirstSearch(const G& graph, T value) {
    std::vector<bool> visited (graph.size(), false);
    return depthFirstSearch(graph, value, visited);
  }

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
    std::vector<std::vector<T>> scc;
    // reverse the directed graph
    GraphAdj<T> graph_reversed = graph::reverseGraph(graph);

    //
    // First pass, recursively run DFS on the original graph.
    // The finish time of each vertex will be store in a stack
    //
    std::vector<bool> visited (graph.size(), false);
    std::stack<T> finish_time;
    for (std::size_t i = 0; i < graph.size(); ++i) {
      if (!visited[i]) {
        std::vector<T> search = graph::depthFirstSearch
            (graph, graph.getVertexByIndex(i)->value, visited);
        for ( auto j=0; j < search.size(); ++j) {
          finish_time.push(search[j]);
        }
      }
    }

    //
    // Second pass, recursively run DFS using each vertex stored in
    // the stack. The last finished vertex will be tracked first!
    //
    std::vector<bool> reversed_visited (graph_reversed.size(), false);
    while (!finish_time.empty()) {
      if (!reversed_visited[graph_reversed.vertexToIndex(finish_time.top())]) {
        std::vector<T> search = depthFirstSearch(
            graph_reversed, finish_time.top(), reversed_visited);
        scc.push_back(search);
      }
      finish_time.pop();
    }

    return scc;
  }

  //
  // implementation of the Dijkstra's shorted path algorithm
  // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
  //
  // A self-balanced RB-tree (std::set) is used to store the unfinished
  // vertices and its current shortest distance to the source. It allows
  // us to find, remove and insert any other element in log(n) time
  // (decreasing the priority and re-inserting). In addition, since
  // std::set keeps tracking the smallest element so that the look-up
  // time is only O(1).
  //
  // The speed is comparable with the implementation using priority queue.
  // However, the overhead (memory) of a self-balanced RB-tree is much higher.
  //
  // @param graph: a directed graph
  // @param source: the starting vertex value
  // @param destination: the destination vertex value. The entire graph
  //                     will be searched if destination == source.
  // @param max_distance: maximum distance from the source. If there is
  //                      no connection between two vertices, the distance
  //                      between them will be represented by "max_distance".
  //
  // @param return: a vector containing a pair of the shortest distance
  //                between each vertex to the source as well as the
  //                parent vertex of each vertex.
  //
  template <class G, class T>
  inline std::vector<std::pair<double, T>> dijkstra_base_tree(
      const G& graph, T source, T destination,
      double max_distance=std::numeric_limits<double>::max()) {
    if ( !graph.getVertex(source) ) {
      std::cout << source << " is not a vertex of the graph!" << std::endl;
      return {};
    }
    if ( !graph.getVertex(destination) ) {
      std::cout << destination << " is not a vertex of the graph!" << std::endl;
      return {};
    }

    // A set of vertex <current shortest distance, index>
    std::set<std::pair<double, int>> remain;
    // Store the shortest distance and its parent vertex for each vertex
    std::vector<std::pair<double, T>> distances(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      if (graph.getVertexByIndex(i)->value != source) {
        remain.insert(std::make_pair(max_distance, i));
        distances[i].first = max_distance;
      } else {
        remain.insert(std::make_pair(0, i));
        distances[i].first = 0;
        distances[i].second = source;
      }
    }

    // Run until there is no vertex left in the remain set.
    while ( !remain.empty() ) {
      // Pick the index in the 'remain' set with the shortest distance.
      int selected_index = remain.begin()->second;

      remain.erase(remain.begin());

      if ( source != destination &&
           selected_index == graph.vertexToIndex(destination) ) {
        return distances;
      }

      // Loop the neighbors of the "selected_index" which is still in the
      // "remain" set.
      Edge<T> *current_edge = graph.getVertexByIndex(selected_index)->next;
      while (current_edge) {
        int current_index = graph.vertexToIndex(current_edge->value);

        // Update shortest distance information.
        // Note: It is not necessary to check whether 'currentIndex' has
        // been visited (here not in 'remain' container) since its
        // shortest distance will (should) not be updated further.
        // Moreover, the find operation is expensive compared to an
        // addiction operation and a comparing.
        double new_distance = distances[selected_index].first + current_edge->weight;
        if (distances[current_index].first > new_distance) {
          remain.erase(std::make_pair(distances[current_index].first, current_index));
          distances[current_index].first = new_distance;
          distances[current_index].second = graph.getVertexByIndex(selected_index)->value;
          remain.insert(std::make_pair(distances[current_index].first, current_index));
        }

        current_edge = current_edge->next;
      }
    }

    return distances;
  }

  //
  // This is a similar implementation as dijkstra_base_tree excpet a
  // priority_queue is used to track the un-finished vertex set.
  //
  // The speed is comparable with the implementation using self-balanced
  // RB-tree.
  //
  template <class G, class T>
  inline std::vector<std::pair<double, T>> dijkstra_base_priority_queue(
      const G& graph, T source, T destination,
      double max_distance=std::numeric_limits<double>::max()) {
    if ( !graph.getVertex(source) ) {
      std::cout << source << " is not a vertex of the graph!" << std::endl;
      return {};
    }
    if ( !graph.getVertex(destination) ) {
      std::cout << destination << " is not a vertex of the graph!" << std::endl;
      return {};
    }

    // A set of vertex <current shortest distance, index>.
    typedef std::pair<double, int> distance_index_pair_t ;
    std::priority_queue<distance_index_pair_t,
                        std::vector<distance_index_pair_t>,
                        std::greater<distance_index_pair_t>> remain;
    // Store the shortest distance and its parent vertex for each vertex.
    std::vector<std::pair<double, T>> distances(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      if (graph.getVertexByIndex(i)->value != source) {
        remain.push(std::make_pair(max_distance, i));
        distances[i].first = max_distance;
      } else {
        remain.push(std::make_pair(0, i));
        distances[i].first = 0;
        distances[i].second = source;
      }
    }

    // Run until there is no vertex left in the remain set.
    while ( !remain.empty() ) {
      double selected_distance = remain.top().first;
      int selected_index = remain.top().second;

      remain.pop();

      if ( source != destination &&
           selected_index == graph.vertexToIndex(destination) ) {
        return distances;
      }

      // Since we leave old copies of the vertex in the priority queue
      // (with outdated higher distances), we should ignore it when we
      // come across it again in order to speed up. Otherwise, it still
      // works. However, the speed will be much slower since it will
      // traverse its children vertices again.
      if (selected_distance > distances[selected_index].first) { continue; }

      // Loop the neighbors of the "selected_index" which is still in the
      // "remain" set.
      Edge<T> *current_edge = graph.getVertexByIndex(selected_index)->next;
      while (current_edge) {
        int current_index = graph.vertexToIndex(current_edge->value);

        // Update shortest distance information
        // Note: It is not necessary to check whether 'currentIndex' has
        // been visited (here not in 'remain' container) since its
        // shortest distance will (should) not be updated further.
        // Moreover, the find operation is expensive compared to an
        // addiction operation and a comparing.
        //
        // Also, it is not necessary to find and remove the old
        // (distance, vertex) pair here since it will pop up later.
        double new_distance = distances[selected_index].first + current_edge->weight;
        if (distances[current_index].first > new_distance) {
          distances[current_index].first = new_distance;
          distances[current_index].second = graph.getVertexByIndex(selected_index)->value;
          remain.push(std::make_pair(distances[current_index].first, current_index));
        }

        current_edge = current_edge->next;
      }
    }

    return distances;
  }

  //
  // Explore the entire graph using dijkstra's algorithm
  //
  template <class G, class T>
  inline std::vector<std::pair<double, T>> dijkstra(
      const G& graph, T source,
      double max_distance=std::numeric_limits<double>::max()) {

    return dijkstra_base_priority_queue(graph, source, source, max_distance);
  }

  //
  // Explore the graph until reaching the destination vertex
  //
  template <class G, class T>
  inline std::vector<std::pair<double, T>> dijkstra(
      const G& graph, T source, T destination,
      double max_distance=std::numeric_limits<double>::max()) {

    return dijkstra_base_priority_queue(graph, source, destination, max_distance);
  }

  //
  // Visualize the shortest path between source and destination vertices
  //
  // @param graph: directed graph object
  // @param distances: search result from function Dijkstra()
  // @param source: value of source vertex
  // @param destination: value of destination vertex
  //
  template <class G, class T>
  inline void showDijkstraPath(const G& graph,
                               const std::vector<std::pair<double, T>>& distances,
                               T source, T destination) {
    std::stack<T> path;
    T current_vertex = destination;
    while ( true ) {
      current_vertex = distances[graph.vertexToIndex(current_vertex)].second;
      path.push(current_vertex);
      if ( current_vertex == source ) { break; }
    }

    while ( !path.empty() ) {
      std::cout << path.top() << " -> ";
      path.pop();
    }
    std::cout << destination << std::endl;

  };
}

#endif //GRAPH_GRAPH_ALGORITHMS_H
