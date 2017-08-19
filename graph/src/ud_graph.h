//
// Created by jun on 8/19/17.
//
// Implementation of the undirected graph using adjacency list
//
#ifndef GRAPH_UD_GRAPH_H
#define GRAPH_UD_GRAPH_H

#include "graph.h"


template <class T>
class UdGraph: public Graph<T> {

private:
  using Graph<T>::vertices_;
  using Graph<T>::valueToIndex_;
  using Graph<T>::addEdge;
  using Graph<T>::delEdge;
  using Graph<T>::clearList;
  using Graph<T>::getVtx;

public:
  //
  // constructor
  //
  UdGraph();

  //
  // destructor
  //
  ~UdGraph();

  //
  // get No. of edges in the graph
  //
  int countEdge() const;

  //
  // get the sum of weights of all the edges in the graph
  //
  double countWeightedEdge() const;

  //
  // check whether two vertices are connected
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  //
  bool isConnected(T first, T second);

  //
  // connect two vertices
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  // @param weight: the weight of the edge
  //
  // @return: true for success and false for already connected vertices
  //
  bool connect(T first, T second, double weight=1.0);

  //
  // disconnect two vertices
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  //
  // @return: weight of the edge between the two vertices
  //
  double disconnect(T first, T second);

  //
  // Collapse the vertex source to the vertex destination and empty
  // the linked list for source.
  //
  // @param source: the source vertex value
  // @param destination: the destination vertex value
  //
  void collapse(T source, T destination);
};

#endif //GRAPH_UD_GRAPH_H