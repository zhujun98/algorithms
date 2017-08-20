//
// Created by jun on 8/19/17.
//

#ifndef GRAPH_DIJKSTRA_H
#define GRAPH_DIJKSTRA_H

#include <vector>
#include <limits>
#include <iostream>
#include <set>
#include <queue>

#include "../graph.h"


const double kMaxDistance = std::numeric_limits<double>::max();

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
// The time complexity is O(VlogV + V + 2ElogV) = O(ElogV)
//
// The speed is comparable with the implementation using priority queue.
// However, the overhead (memory) of a self-balanced RB-tree is much higher.
//
// @param graph: a directed graph
// @param src: the source vertex value
// @param dst: the destination vertex value. The entire graph
//                     will be searched if dst == src.
//
// @param return: a vector containing a pair of the shortest distance
//                between each vertex to the source as well as the
//                parent vertex of each vertex in the shortest path.
//
template <class G, class T>
std::vector<std::pair<double, T>>
dijkstraTreeBase(const G& graph, T src, T dst) {
  if ( !graph.getVertex(src) ) {
    std::cout << src << " is not a vertex of the graph!" << std::endl;
    return {};
  }
  if ( !graph.getVertex(dst) ) {
    std::cout << dst << " is not a vertex of the graph!" << std::endl;
    return {};
  }

  // A set of vertices <current shortest distance, destination index>
  std::set<std::pair<double, int>> remain;
  // Store the shortest distance and its parent vertex for each vertex
  std::vector<std::pair<double, T>> distances(graph.size());
  // O(VlogV)
  for (int i = 0; i < graph.size(); ++i) {
    if (graph.indexToValue(i) != src) {
      remain.insert(std::make_pair(kMaxDistance, i));
      distances[i].first = kMaxDistance;
      // parent vertex is not initialized
    } else {
      remain.insert(std::make_pair(0, i));
      distances[i].first = 0;
      distances[i].second = src;
    }
  }

  // Run until there is no vertex left in the remain set.
  while ( !remain.empty() ) {
    // Pick the index in the 'remain' set with the shortest distance.
    int selected_index = remain.begin()->second;

    // O(1)*V = O(V), V is the outer loops
    remain.erase(remain.begin());

    if ( src != dst &&
         selected_index == graph.valueToIndex(dst) ) {
      return distances;
    }

    // Loop the neighbors of the "selected_index" which is still in the
    // "remain" set.
    graph::Edge<T> *current_edge = graph.getVertexByIndex(selected_index)->next;
    // Since each edge will only be visited once, so the total time
    // complexity of the two loops is only O(E)
    while (current_edge) {
      int current_index = graph.valueToIndex(current_edge->value);

      if ( current_edge->weight < 0 ) {
        std::cout << "Graph has edge with negative weight!" << std::endl;
        return {};
      }
      // Update shortest distance information.
      // Note: It is not necessary to check whether 'currentIndex' has
      // been visited (here not in 'remain' container) since its
      // shortest distance will (should) not be updated further.
      // Moreover, the find operation is expensive compared to an
      // addition operation and a comparing.
      double new_distance = distances[selected_index].first + current_edge->weight;
      if (distances[current_index].first > new_distance) {
        // O(ElogV)
        remain.erase(std::make_pair(distances[current_index].first, current_index));
        distances[current_index].first = new_distance;
        distances[current_index].second = graph.indexToValue(selected_index);
        // O(ElogV)
        remain.insert(std::make_pair(distances[current_index].first, current_index));
      }

      current_edge = current_edge->next;
    }
  }

  return distances;
}

//
// This is a similar implementation as dijkstra_base_tree except a
// priority_queue is used to track the un-finished vertex set.
//
// Since there is decrease_key operation, the time complexity is
// O(VlogV + E + ElogE) = O(ElogE) = O(ElogV), E <= V^2
// If decrease_key is implemented, the time complexity will become
// O(VlogV + V + 2ElogV) = O(ElogV), which is almost the same. But
// the decrease_key operation has its overhead.
//
// The speed is comparable with the implementation using self-balanced
// RB-tree.
//
// @param graph: a directed graph
// @param src: the source vertex value
// @param dst: the destination vertex value. The entire graph
//                     will be searched if dst == src.
//
// @param return: a vector containing a pair of the shortest distance
//                between each vertex to the source as well as the
//                parent vertex of each vertex in the shortest path.
//
template <class G, class T>
std::vector<std::pair<double, T>>
dijkstraPriorityQueueBase(const G& graph, T src, T dst) {
  if ( !graph.getVertex(src) ) {
    std::cout << src << " is not a vertex of the graph!" << std::endl;
    return {};
  }
  if ( !graph.getVertex(dst) ) {
    std::cout << dst << " is not a vertex of the graph!" << std::endl;
    return {};
  }

  // A set of vertex <current shortest distance, index>.
  typedef std::pair<double, int> distance_index_pair_t;
  std::priority_queue<distance_index_pair_t,
                      std::vector<distance_index_pair_t>,
                      std::greater<distance_index_pair_t>> remain;
  // Store the shortest distance and its parent vertex for each vertex.
  // The index in the vector is the same as the index of the vertex in
  // the graph.
  std::vector<std::pair<double, T>> distances(graph.size());
  // O(VlogV)
  for (int i = 0; i < graph.size(); ++i) {
    if (graph.indexToValue(i) != src) {
      remain.push(std::make_pair(kMaxDistance, i));
      distances[i].first = kMaxDistance;
    } else {
      remain.push(std::make_pair(0, i));
      distances[i].first = 0;
      distances[i].second = src;
    }
  }

  // Run until there is no vertex left in the remain set.
  while ( !remain.empty() ) {
    double selected_distance = remain.top().first;
    int selected_index = remain.top().second;

    // O(1)*E = O(E), E is the outer loops
    remain.pop();

    if ( src != dst &&
         selected_index == graph.valueToIndex(dst) ) {
      return distances;
    }

    // Critical step!!!
    // Ensure that each vertex will only be visited once!
    //
    // Since we leave old copies of the vertex in the priority queue
    // (with outdated higher distances), we should ignore it when we
    // come across it again in order to speed up. Otherwise, the time
    // complexity will increase to O(EVlogV).
    if (selected_distance > distances[selected_index].first) { continue; }

    // Loop the neighbors of the "selected_index" which is still in the
    // "remain" set.
    graph::Edge<T> *current_edge = graph.getVertexByIndex(selected_index)->next;
    // Since each edge will only be visited once, so the total time
    // complexity of the two loops is only O(E)
    while (current_edge) {
      int current_index = graph.valueToIndex(current_edge->value);

      if ( current_edge->weight < 0 ) {
        throw std::invalid_argument("Graph has edge with negative weight!");
      }
      // Update shortest distance information
      // Note: It is not necessary to check whether 'currentIndex' has
      // been visited (here not in 'remain' container) since its
      // shortest distance will (should) not be updated further.
      // Moreover, the find operation is expensive compared to an
      // addition operation and a comparing.
      //
      // Also, it is not necessary to find and remove the old
      // (distance, vertex) pair here since it will pop up later.
      double new_distance = distances[selected_index].first + current_edge->weight;
      if (distances[current_index].first > new_distance) {
        distances[current_index].first = new_distance;
        distances[current_index].second = graph.indexToValue(selected_index);
        // O(ElogE)
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
inline std::vector<std::pair<double, T>>
dijkstra(const G& graph, T src) {
  return dijkstraPriorityQueueBase(graph, src, src);
}

//
// Explore the graph until reaching the destination vertex
//
template <class G, class T>
inline std::vector<std::pair<double, T>>
dijkstra(const G& graph, T src, T dst) {
  return dijkstraPriorityQueueBase(graph, src, dst);
}

//
// Visualize the shortest path between src and dst vertices
//
// @param graph: directed graph object
// @param distances: search result from function Dijkstra()
// @param src: value of source vertex
// @param dst: value of destination vertex
//
template <class G, class T>
inline void showDijkstraPath(const G& graph,
                             const std::vector<std::pair<double, T>>& distances,
                             T src, T dst) {
  std::stack<T> path;
  T current_vertex = dst;
  while ( true ) {
    current_vertex = distances[graph.valueToIndex(current_vertex)].second;
    path.push(current_vertex);
    if ( current_vertex == src ) { break; }
  }

  while ( !path.empty() ) {
    std::cout << path.top() << " -> ";
    path.pop();
  }
  std::cout << dst << std::endl;
};


#endif //GRAPH_DIJKSTRA_H