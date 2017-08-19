//
// Created by jun on 8/19/17.
//
#include "ud_graph.h"


template<class T>
UdGraph<T>::UdGraph() {}

template<class T>
UdGraph<T>::~UdGraph() {}

template<class T>
int UdGraph<T>::countEdge() const {
  int count = 0;
  for (int i=0; i<vertices_.size(); ++i) {
    graph::Edge<T>* current = vertices_[i]->next;
    while ( current ) {
      ++count;
      current = current->next;
    }
  }

  assert(count%2 == 0);
  return count/2;
}

template<class T>
double UdGraph<T>::countWeightedEdge() const {
  int count = 0;
  for (int i=0; i<vertices_.size(); ++i) {
    graph::Edge<T>* current = vertices_[i]->next;
    while ( current ) {
      count += current->weight;
      current = current->next;
    }
  }

  assert(count%2 == 0);
  return count/2;
}

template<class T>
bool UdGraph<T>::isConnected(T first, T second) {
  graph::Vertex<T>* v_first = getVtx(first);
  graph::Vertex<T>*  v_second = getVtx(second);
  // if any one of the two vertices is empty
  if ( !v_first || !v_second ) { return false; }

  if ( first == second ) { return true; }

  bool connected1 = false;
  bool connected2 = false;

  graph::Edge<T>* current = v_first->next;

  while ( current ) {
    if ( current->value == second ) {
      connected1 = true;
    }
    current = current->next;
  }

  current = v_second->next;

  while ( current ) {
    if ( current->value == first ) {
      connected2 = true;
    }
    current = current->next;
  }

  assert(connected1 == connected2);

  if ( connected1 && connected2 ) {
    return true;
  } else {
    return false;
  }
}

template<class T>
bool UdGraph<T>::connect(T first, T second, double weight) {
  if ( isConnected(first, second) ) { return false; }

  // we need to add a node for the lists a and b respectively
  addEdge(first, second, weight);
  addEdge(second, first, weight);

  return true;
}

template<class T>
double UdGraph<T>::disconnect(T first, T second) {
  double weight1 = delEdge(first, second);
  double weight2 = delEdge(second, first);

  assert(weight1 == weight2);

  return weight1;
}

template<class T>
void UdGraph<T>::collapse(T source, T destination) {
  if ( source == destination ) { return; }

  // first remove loops
  disconnect(source, destination);

  // In each collapse, the No. of edges will be reduced only by the No. of edges
  // between the source and destination vertices!

  // change the value of nodes with value src to dst
  graph::Edge<T>* current = getVtx(source)->next;
  while ( current ) {
    // change the node with value 'src' in other linked lists to 'dst'
    // TODO:: this could be fast since the linked list is traversed twice here for code simplicity
    double weight = delEdge(current->value, source);
    addEdge(current->value, destination, weight);

    // add node in the linked list 'src' to the linked list 'dst'
    addEdge(destination, current->value, current->weight);

    current = current->next;
  }

  // delete linked list and release memory
  clearList(source);
}

template class UdGraph<int>;
template class UdGraph<double>;
template class UdGraph<std::string>;