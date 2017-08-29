//
// Created by jun on 8/19/17.
//
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H


#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>

namespace graph {
  class DirectedGraph;

  // node in a linked list, which represents edges
  template <class T>
  struct Edge {
    size_t dst; // destination vertex
    T weight; // edge weight
    Edge* next; // pointer to the next edge
  };

  /**
   * construct a new Edge
   *
   * @param dst: desintation vertex
   * @param weight: edge weight
   * @return: pointer to the new edge
   */
  template <class T>
  Edge<T>* newEdge(size_t dst, T weight=1) {
    auto* new_edge =new Edge<T>;
    new_edge->dst = dst;
    new_edge->weight = weight;
    new_edge->next = nullptr;

    return new_edge;
  }
}

template <class T>
class Graph {

protected:
  std::vector<graph::Edge<T>*> vertices_;  // a vector of linked lists

  /**
   * clear (release memory) the linked list belong to a vertex
   *
   * @param src: the source vertex
   */
  void clearList(size_t src) {
    graph::Edge<T>* current_edge = vertices_[src];
    while (current_edge != nullptr) {
      graph::Edge<T>* previous_edge = current_edge;
      current_edge = previous_edge->next;

      delete previous_edge;
    }
  }

  /**
   * Add an edge (src->dst) at the head of the linked list
   *
   * @param src: source vertex
   * @param dst: destination vertex
   * @param weight: edge weight
   */
  bool addEdge(size_t src, size_t dst, T weight) {
    if ( src < 0 || src >= vertices_.size() ) {
      throw std::invalid_argument("Out of range: src vertex");
    }

    if ( dst < 0 || dst >= vertices_.size() ) {
      throw std::invalid_argument("Out of range: dst vertex");
    }

    if ( src == dst ) { return false; }

    // check existence of the edge
    graph::Edge<T>* current_edge = vertices_[src];
    while (current_edge != nullptr) {
      if (current_edge->dst == dst) { return false; }
      current_edge = current_edge->next;
    }

    // add new edge to the head of the linked list
    graph::Edge<T>* new_edge = graph::newEdge(dst, weight);
    new_edge->next = vertices_[src];
    vertices_[src] = new_edge;
    return true;
  }

  /**
   * Delete an edge (src->dst)
   *
   * @param src: source vertex
   * @param dst: destination vertex
   * @return: weight of the deleted edge
   */
  T delEdge(size_t src, size_t dst) {
    if ( src < 0 || src >= vertices_.size() ) {
      throw std::invalid_argument("Out of range: src vertex");
    }

    if ( dst < 0 || dst >= vertices_.size() ) {
      throw std::invalid_argument("Out of range: dst vertex");
    }

    graph::Edge<T>* current_edge = vertices_[src];
    while (current_edge != nullptr) {
      if (current_edge->dst == dst) {
        return current_edge->weight;
      }

      current_edge = current_edge->next;
    }

    // src and dst are not connected
    return 0;
  }

public:

  /**
   * constructor
   *
   * @param size
   */
  explicit Graph(size_t size) : vertices_(size) {}

  // copy constructor
  Graph(const Graph& g) : vertices_(g.size()) {
    for (size_t i=0; i < vertices_.size(); ++i) {
      graph::Edge<T>* current_edge_cp = g.vertices_[i];
      graph::Edge<T>* previous_edge = nullptr;
      graph::Edge<T>* current_edge = nullptr;
      while (current_edge_cp != nullptr) {
        current_edge = new graph::Edge<T>(*current_edge_cp);
        if (!vertices_[i]) {
          vertices_[i] = current_edge;
        } else {
          previous_edge->next = current_edge;
        }
        previous_edge = current_edge;
        current_edge_cp = current_edge_cp->next;
      }
    }
  }

  // destructor
  virtual ~Graph() {
    for (size_t i = 0; i < vertices_.size() ; ++i) {
      clearList(i);
    }
  }

  // display the graph
  void display() const {
    std::cout << "------------------------------" << std::endl;

    for (int i = 0; i < vertices_.size(); ++i ) {
      std::cout << "Vertex [" << i << "] ";

      graph::Edge<T>* current_edge = vertices_[i];
      while (current_edge != nullptr) {
        std::cout << " -> " << current_edge->dst
                  << " (" << current_edge->weight << ")";
        current_edge = current_edge->next;
      }

      std::cout << std::endl;
    }
  }
  // get No. of vertices in the graph
  std::size_t size() const { return vertices_.size(); }

  // get No. of edges in the graph
  virtual size_t countEdge() const = 0;

  // get the sum of weights of all the edges in the graph
  virtual T countWeight() const = 0;

  /**
   * connect two vertecies (add one edge for directed graph and two
   * for undirected graph)
   *
   * @param src: source vertex
   * @param dst: destination vertex
   * @param weight: edge weight
   * @return: true for new edge(s) is(are) added.
   */
  virtual bool connect(size_t src, size_t dst) = 0;
  virtual bool connect(size_t src, size_t dst, T weight) = 0;

  /**
   * disconnect two vertices
   *
   * @param src: source vertex
   * @param dst: destination vertex
   * @return: weight of the edge removed
   */
  virtual T disconnect(size_t src, size_t dst) = 0;

  //
  // collapse the vertex src to the vertex dst and empty the linked list for src
  //
  // @param src: the source vertex
  // @param dst: the destination vertex
  //
  virtual void collapse(size_t src, size_t dst) {};

  graph::Edge<T>* getList(size_t src) const {
    if ( src < 0 || src >= vertices_.size() ) {
      throw std::invalid_argument("Out of range: src");
    } else {
      return vertices_[src];
    }
  }};

#endif //GRAPH_GRAPH_H