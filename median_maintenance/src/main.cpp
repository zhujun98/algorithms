//
// Created by jun on 6/14/17.
//
// std::priority_queue is implemented as a heap represented by sorted array
//
// Difference between a priority_queue and a heap:
//   A priority queue only need to support find_min and insert operation. It
// means it is only required to guarantee that the root node has the highest
// priority (the maximum by default). However, in a heap, there is also another
// constraint saying that the parent must have higher priority (e.g. bigger
// by default) than the child nodes.
//
//
// The goal of this problem is to implement the "Median Maintenance" algorithm
// (covered in the Week 3 lecture on heap applications). The data file contains
// a list of the integers from 1 to 10000 in unsorted order; you should treat
// this as a stream of numbers, arriving one by one. Letting xi denote the ith
// number of the file, the kth median mk is defined as the median of the numbers
// x1,…,xk. (So, if k is odd, then mk is ((k+1)/2)th smallest number among
// x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)
// In the box below you should type the sum of these 10000 medians, modulo 10000
//
// OPTIONAL EXERCISE: Compare the performance achieved by heap-based and
// binary-search-tree based implementations of the algorithm.
//
// Answer: 1213
//
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>

//
// print all the elements in a queue
//
// @param q: input queue
//
template<typename T> void print_queue(T& q) {
  while(!q.empty()) {
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << '\n';
}


int main() {

  std::cout << "hello" << std::endl;

  // max-heap
  std::priority_queue<int> lower_queue;
  // min-heap
  std::priority_queue<int, std::vector<int>, std::greater<int>> upper_queue;

  std::ifstream ifs("../data/Median.txt", std::fstream::in);

  int number;
  int median = 0;
  int sum_of_median = 0;

  clock_t t0 = clock();
  while ( ifs >> number ) {

    // the first number goes into lower_queue
    if ( lower_queue.size() == 0 ) {
      lower_queue.push(number);

    // insert the new number into one of the two heaps
    } else if ( number <= lower_queue.top() ) {
      lower_queue.push(number);
    } else {
      upper_queue.push(number);
    }

    // deal with unbalanced heaps
    if ( lower_queue.size() > upper_queue.size() + 1 ) {
      upper_queue.push(lower_queue.top());
      lower_queue.pop();
    } else if ( upper_queue.size() > lower_queue.size() + 1 ) {
      lower_queue.push(upper_queue.top());
      upper_queue.pop();
    }

    // extract the median
    if ( lower_queue.size() == upper_queue.size()
         || lower_queue.size() == upper_queue.size() + 1 ) {
      median = lower_queue.top();
    } else if ( lower_queue.size() == upper_queue.size() - 1 ) {
      median = upper_queue.top();
    } else {
      std::cout << "Unbalanced heaps!!!" << std::endl;
      exit(EXIT_FAILURE);
    }

    sum_of_median += median;
  }
  ifs.close();

  std::cout << "Sum of median mode 10000 is: " << sum_of_median % 10000 << std::endl;
  std::cout << "Elapse time: " << 1.0*(clock() - t0)/CLOCKS_PER_SEC << std::endl;

  return 0;
}
