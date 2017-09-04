//
// Created by jun on 9/4/17.
//

#ifndef TSP_TSP_H
#define TSP_TSP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>


template <class T>
inline T euclideanDist(std::pair<T, T> p1, std::pair<T, T> p2) {
  T dx = p2.first - p1.first;
  T dy = p2.second - p1.second;

  return std::sqrt(dx*dx + dy*dy);
}

/**
 * Implementation of Travelling sales man problem using the
 * nearest neighbor heuristic.
 *
 * This algorithm on average yields a path 25% longer than the shortest
 * possible path. However, there exist many specially arranged city
 * distributions which make the NN algorithm give the worst route.
 *
 * Time complexity O(V^2)
 *
 * @param graph: a vector contains the (x, y) coordinates of each vertex
 * @param src: source vertex
 * @return: a pair with first element being the distance of the TSP
 *          path and the second element being a deque of the vertices
 *          along the TSP path in sequence.
 */
template <class T>
std::pair<T, std::vector<size_t>>
tspNN(std::vector<std::pair<T, T>> xy, size_t src = 0) {
  const double kINF = std::numeric_limits<T>::max();

  std::vector<bool> visited(xy.size(), false); // flag for visited vertices
  std::vector<size_t> sequence(xy.size()+1); // visiting sequence of the TSP path
  double total_dist = 0.0; // total distance of the TSP path

  sequence[0] = src;
  size_t current_vertex = src;
  visited[current_vertex] = true;
  for (size_t count = 0; count < xy.size() - 1; ++count) {
    T min_dist = kINF; // distance to the nearest neighbor

    size_t next_vertex = current_vertex;
    for (size_t j = 0; j < xy.size(); ++j) {
      if (!visited[j] && j != current_vertex) {
        T dist = euclideanDist(xy[current_vertex], xy[j]);
        if (dist < min_dist) {
          min_dist = dist;
          next_vertex = j;
        }
      }
    }

    current_vertex = next_vertex;
    visited[current_vertex] = true;
    sequence[count+1] = current_vertex;
    total_dist += min_dist;
  }

  // connect the source vertex as the last point
  total_dist += euclideanDist(xy[current_vertex], xy[src]);
  sequence[xy.size()] = src;

  return std::make_pair(total_dist, sequence);
}

#endif //TSP_TSP_H
