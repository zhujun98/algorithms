//
// Created by jun on 7/22/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>


//
// Find the sub-set in a path graph with the maximum sum of weight.
// Any vertices in the sub-set cannot be adjacent to each other.
//
// @param path: a vector representation of a path graph
//
// @return: a vector indicating whether each vertex belongs to the
//          chosen sub-set.
//
template <class T>
std::vector<bool> maxWeightIndependentSet(std::vector<T> path) {

  size_t length = path.size();

  std::vector<long long> result(length, 0);
  // A tracker can facilitate the later reconstruction process.
  // It saves the effort do the addition and compare the result.
  std::vector<bool> tracker(length, true);

  result[0] = path[0];
  result[1] = std::max(path[0], path[1]);
  for ( size_t i = 2; i < length; ++i) {
    long long tmp = result[i-2] + path[i];
    if ( result[i-1] > tmp ) {
      result[i] = result[i-1];
      tracker[i] = false;
    } else {
      result[i] = tmp;
    }
  }

  std::vector<bool> solution(length, false);
  // reconstruct the solution from the tracker
  if ( tracker[length - 1] ) { solution[length - 1] = true; }
  size_t i = length - 1;
  while ( i > 0 ) {
    --i;
    if ( tracker[i] && !solution[i+1] ) {
      solution[i] = true;
    }
  }

  return solution;
}

//
// In this programming problem you'll code up the dynamic programming
// algorithm for computing a maximum-weight independent set of a path
// graph.
//
// This file describes the weights of the vertices in a path graph
// (with the weights listed in the order in which vertices appear in
// the path). It has the following format:
//
// [number_of_vertices]
// [weight of first vertex]
// [weight of second vertex]
// ...
//
// Your task in this problem is to run the dynamic programming
// algorithm (and the reconstruction procedure) on this data set.
// The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997,
// which vertices belong to the maximum-weight independent set? (By
// "vertex 1" we mean the first vertex of the graph---there is no
// vertex 0.)In the box below, enter a 8-bit string, where the ith
// bit should be 1 if the ith of these 8 vertices is in the
// maximum-weight independent set, and 0 otherwise.
// Answer: 10100110
//
void runMaxWeightIndependentSetAssignment() {

  std::cout << "\n" << std::string(80, '-') << "\n"
            << "This is the maximum-weight independent set assignment in the \n"
            << "Stanford's Algorithm course at Coursera"
            << "\n" << std::string(80, '-')
            << std::endl;

  std::vector<long> numbers;

  std::ifstream ifs("../data/mwis.txt", std::ifstream::in);

  long number;
  ifs >> number; // skip the first line
  while ( ifs >> number ) {
    numbers.push_back(number);
  }
  ifs.close();
  std::cout << "Read in " << numbers.size() << " numbers" << std::endl;

  std::vector<bool> solution = maxWeightIndependentSet(numbers);

  std::vector<bool> sub_solution;
  std::vector<int> sub_solution_index = {0, 1, 2, 3, 16, 116, 516, 996};
  for ( auto v : sub_solution_index ) { sub_solution.push_back(solution[v]); }
  std::vector<bool> correct_sub_solution = {1, 0, 1, 0, 0, 1, 1, 0};
  assert(sub_solution == correct_sub_solution);
  std::cout << "Passed!" << std::endl;
}


int main() {
  std::cout << "Hello!\n" << std::endl;

  std::vector<int> test_path1 = {3, 6, 2, 7, 9, 1};
  std::vector<bool> solution1 = maxWeightIndependentSet(test_path1);
  std::vector<bool> correct_solution1 = {0, 1, 0, 0, 1, 0};
  assert(solution1 == correct_solution1);
  std::cout << "Passed: test 1!" << std::endl;

  std::vector<int> test_path2 = {8, 3, 6, 2, 7, 9, 1};
  std::vector<bool> solution2 = maxWeightIndependentSet(test_path2);
  std::vector<bool> correct_solution2 = {1, 0, 1, 0, 0, 1, 0};
  assert(solution2 == correct_solution2);
  std::cout << "Passed: test 2!" << std::endl;

  runMaxWeightIndependentSetAssignment();
}

