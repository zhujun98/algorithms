//
// Created by jun on 9/4/17.
//
// tspBruteForce():
// tspNN():
// tspDP():
//

#ifndef TSP_TSP_H
#define TSP_TSP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>


// Calculate Euclidean distance between p1 and p2
template <class T>
inline T euclideanDist(std::pair<T, T> p1, std::pair<T, T> p2) {
  T dx = p2.first - p1.first;
  T dy = p2.second - p1.second;

  return std::sqrt(dx*dx + dy*dy);
}


/**
 * Calculate the total Euclidean distance in a TSP path that starts and
 * ends at src and passes through each vertex in `sequence` in sequence.
 *
 * @param dists: a 2D vector contains the distance between each pair of
 *               vertices
 * @param sequence: visiting sequence of the intermediate vertices
 * @param src: start and end vertex
 * @return: total distance
 */
template <class T>
inline T totalTspDist(const std::vector<std::vector<T>>& dists,
                            const std::vector<size_t>& sequence,
                            size_t src) {
  T dist = 0;
  size_t prev_vertex = src;
  for (auto i : sequence) {
    dist += dists[prev_vertex][i];
    prev_vertex = i;
  }
  dist += dists[prev_vertex][src];

  return dist;
}


/**
 * Implementation of Travelling sales man problem using brute force.
 *
 * Time complexity O(V!)
 *
 * @param xy: a vector contains the (x, y) coordinates of each vertex
 * @param src: source vertex
 * @return: a pair with first element being the distance of the TSP
 *          path and the second element being a deque of the vertices
 *          along the TSP path in sequence.
 */
template <class T>
std::pair<T, std::vector<size_t>>
tspBruteForce(const std::vector<std::pair<T, T>>& xy, size_t src = 0) {
  if (xy.size() > 25) {
    throw std::invalid_argument("The problem size is too larger!");
  }

  const double kINF = std::numeric_limits<T>::max();

  // calculate distances between each pair of vertices and store the values
  std::vector<std::vector<T>> dists(xy.size(), std::vector<T>(xy.size()));
  for (size_t i = 0; i < xy.size(); ++i) {
    for (size_t j = 0; j < xy.size(); ++j) {
      dists[i][j] = euclideanDist(xy[i], xy[j]);
    }
  }

  std::vector<size_t> sequence(xy.size()-1); // container for indices
  size_t idx = 1;
  std::generate(sequence.begin(), sequence.end(), [&idx]{ return idx++; });
  if (src != 0) {
    for (size_t i = 0; i <src; ++i) { sequence[i] = i; }
  }

  std::vector<size_t> path(xy.size()+1); // visiting sequence of the TSP path

  path[0] = src;
  path[xy.size()] = src;
  T min_dist = kINF;
  // Loop over each combination of V - 1 vertices
  do {
    T total_dist = totalTspDist(dists, sequence, src);

    if ( total_dist < min_dist) {
      min_dist = total_dist;
      std::copy(sequence.begin(), sequence.end(), path.begin()+1);
    }
  } while (std::next_permutation(sequence.begin(), sequence.end()));

  return std::make_pair(min_dist, path);
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
 * @param xy: a vector contains the (x, y) coordinates of each vertex
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
        //TODO:: can be faster without calculating sqrt
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

size_t getBitPosition(size_t num) {
  size_t count = 0;
  size_t mask = 1;
  while ( !(mask & num) ) {
    mask = mask << 1;
    ++count;
  }

  return count;
}


/**
 * Implementation of Travelling sales man problem with dynamic
 * programming. This implementation yields the exact optimal solution.
 *
 * Time complexity O(V^2*2^V)
 *
 * @param xy: a vector contains the (x, y) coordinates of each vertex
 * @param src: source vertex
 * @return: a pair with first element being the distance of the TSP
 *          path and the second element being a deque of the vertices
 *          along the TSP path in sequence.
 */
template <class T>
//std::pair<T, std::vector<size_t>>
T
tspDP(std::vector<std::pair<T, T>> xy, size_t src = 0) {

  if (xy.size() > 25) {
    throw std::invalid_argument("The problem size is too larger!");
  }

  const T kINF = std::numeric_limits<T>::max();

  // calculate distances between each pair of vertices and store the values
  std::vector<std::vector<T>> dists(xy.size(), std::vector<T>(xy.size()));
  for (size_t i = 0; i < xy.size(); ++i) {
    for (size_t j = 0; j < xy.size(); ++j) {
      dists[i][j] = euclideanDist(xy[i], xy[j]);
    }
  }

  // there are 2^V sub-sets in S = {0, 1, 2, ... , V - 1}/
  size_t n_subsets = ((size_t)1 << xy.size());

  std::vector<std::vector<T>> costs(xy.size(), std::vector<T>(n_subsets, kINF));
  // costs[i][s] is the shortest path length from src to i and only
  // pass each vertex in subset s only once, where i belongs to s
  for (size_t i = 0; i < xy.size(); ++i) {
    for (size_t j = 0; j < xy.size(); ++j) {
      if (i == j) {
        costs[i][(size_t)1 << j] = dists[src][j];
      }
    }
  }

  for (size_t s = 1; s < costs[0].size(); ++s) {
    // src must not belong to s
    if (((size_t)1 << src) & s) { continue; }

    // the last vertex is i
    for (size_t i = 0; i < xy.size(); ++i) {
      // i must belong to set s
      if (!(((size_t)1 << i) & s)) { continue; }

      T min_dist = costs[i][s];
      // mask is used to unset one bit in s
      size_t mask = ((size_t)1 << xy.size()) - 1 - ((size_t)1 << i);
      size_t masked = s & mask;
      for (size_t j = 0; j < xy.size(); ++j) {
        // j must belong to set s and j != i and j != src
        if (!(((size_t)1 << j) & masked) || j == i || j == src) { continue; }

        T dist = costs[j][masked] + dists[j][i];
        if (dist < min_dist) { min_dist = dist; }
      }
      costs[i][s] = min_dist;
    }
  }

  // For all V - 1 options of costs[i][s],
  // where i = 0, 1, ..., V - 1 where i != src, and
  // s = {1, 2, ..., V - 1}/src, add the last path i -> src
  // and find the minimum distance using brute force search.
  T min_dist = kINF;
  size_t s = ((size_t)1 << xy.size()) - 1 - ((size_t)1 << src);
  for (size_t i = 0; i < xy.size(); ++i) {
    if (i != src) {
      T dist = dists[i][src] + costs[i][s];
      if (dist < min_dist) { min_dist = dist; }
    }
  }

  return min_dist;
}


#endif //TSP_TSP_H
