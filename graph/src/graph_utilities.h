//
// Created by jun on 6/19/17.
//
// Functions:
// - printVector()
// - printSCC()
//

#ifndef GRAPH_GRAPH_UTILITIES_H
#define GRAPH_GRAPH_UTILITIES_H

#include <iostream>
#include <random>
#include <vector>

#include "graph_adj.h"


namespace graph_utilities {

  //
  // print the elements in an iterable 1D container
  //
  // @param v: a 1D container
  //
  template <class T>
  inline void printContainer(const T& v) {
    for (auto i=v.begin(); i != v.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
  }

  //
  // print the std::pair elements in an iterable 1D container
  //
  // @param v: a 1D container with std::pair elements
  //
  template <class T1, class T2>
  inline void printContainer(const std::vector<std::pair<T1, T2>>& v) {
    for (auto i=v.begin(); i != v.end(); ++i) {
      std::cout << i->first << "," << i->second << " ";
    }
    std::cout << std::endl;
  }

  //
  // print the path
  //
  // @param v: pair struct which stores the shortest path information from
  //           one vertex to another.
  //
  template <class T>
  inline void printPathVector(const std::pair<std::list<T>, double>& v) {
    int count = 0;
    for (auto it=v.first.begin(); it != v.first.end(); ++it, ++count) {
      std::cout << *it;
      if ( count < v.first.size() - 1 ) { std::cout << "->"; }
    }
    std::cout << " (" << v.second << ")";
    std::cout << std::endl;
  }

  //
  // print the strongly connected components
  //
  // @param scc: strongly connected components represented by two nested
  //             containers
  //
  template <class VV>
  inline void printSCC(const VV& scc) {
    for (auto i=scc.begin(); i != scc.end(); ++i) {
      for (auto j = (*i).begin(); j != (*i).end(); ++j) {
        std::cout << *j << " ";
      }
      std::cout << std::endl;
    }
  }

}  // namespace graph

#endif // GRAPH_GRAPH_UTILITIES_H
