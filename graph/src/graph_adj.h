//
// Created by jun on 6/6/17.
//
// Implementation of the directed and undirected graph using adjacency list
//
// base class:
// - GraphAdj()
//  derived class:
//    - UdGraphAdj()
//
//
#ifndef GRAPH_GRAPH_ADJ_H
#define GRAPH_GRAPH_ADJ_H

#include <iostream>
#include <assert.h>
#include <list>
#include <forward_list>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>


namespace graph {
  //
  // node in a linked list, which represents edges
  //
  template <class T>
  struct Edge {
    T value;  // value of the head vertex of the edge
    double weight;  // weight (length) of the edge
    Edge<T>* next;  // pointer to the next edge in the same linked list
//    ~Edge() { std::cout << "deallocated Edge!" << std::endl; }
  };

  //
  // vertex of the graph, containing head node of the linked list
  //
  template <class T>
  struct GraphAdjVertex {
    T value;  // value of the vertex
    Edge<T>* next;  // head node of the linked list
//    ~GraphAdjVertex() { std::cout << "deallocated GraphAdjVertex!" << std::endl; }
  };

  //
  // construct a new Edge
  //
  // @param value: value of the head vertex of the edge
  // @param weight: weight (length) of the edge
  //
  // @return: pointer to the new edge
  //
  template <class T>
  Edge<T>* newEdge(T value, double weight=1.0){

    Edge<T>* new_edge =new Edge<T>;
    new_edge->value = value;
    new_edge->weight = weight;
    new_edge->next = NULL;

    return new_edge;
  }

  //
  // construct a new GraphAdjVertex
  //
  // @param value: value of the vertex
  //
  // @return: pointer to the new vertex
  //
  template <class T>
  GraphAdjVertex<T>* newGraphAdjVertex(T value) {

    GraphAdjVertex<T>* new_vertex = new GraphAdjVertex<T>;
    new_vertex->value = value;
    new_vertex->next = NULL;

    return new_vertex;
  }

  //
  // reverse the directed graph
  // Note:: the value->index hash table is usually different from the
  //        one in the original graph, which is affected by the sequence
  //        of the edges being added.
  //
  // @param graph: a graph object
  //
  template <class G>
  G reverseGraph(G const &graph) {
    G graph_reversed;

    for (auto i = 0; i < graph.size(); ++i) {
      auto value = graph.getVertexByIndex(i)->value;
      auto current_node = graph.getVertexByIndex(i)->next;
      while ( current_node ) {
        graph_reversed.connect(current_node->value, value);
        current_node = current_node->next;
      }
    }

    return graph_reversed;
  }
}

/*
 * Directed graph
 */

template <class T>
class GraphAdj {

protected:
  // hash table that converts the vertex value to the vector index
  std::unordered_map<T, int> valueToIndex_;

  // vector of vertices
  std::vector<graph::GraphAdjVertex<T>*> vertices_;

  //
  // get the pointer to a vertex
  //
  // @param value: the vertex value
  //
  // @return: pointer to the vertex
  //
  graph::GraphAdjVertex<T>* getVtx(T value) {
    auto search = valueToIndex_.find(value);
    if ( search == valueToIndex_.end() ) {
      return NULL;
    } else {
      return vertices_[search->second];
    }
  }

  //
  // clear (release memory) the linked list belong to a vertex
  //
  // @param vertex: the vertex value
  //
  void clearList(T value) {
    graph::GraphAdjVertex<T>* v = getVtx(value);
    if ( !v->next ) { return; }

    graph::Edge<T>* current = v->next;
    while ( current ) {
      v->next = current->next;
      delete current;
      current = v->next;
    }
  }

  //
  // Add an edge from tail to head. The nodes in the linked
  // list are sorted in ascending order.
  //
  // Public method connect() is implemented to add an edge for both
  // directed graph and undirected graph
  //
  // Note: the sorting will not increase the complexity since it is
  //       anyhow necessary to traverse the list to check the existence
  //       of the identical node. For the identical node, we only
  //       increase the weight.
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  // @param weight: the weight of edge
  //
  void addEdge(T tail, T head, double weight) {
    if ( tail == head ) { return; }

    graph::GraphAdjVertex<T>* v_tail = getVtx(tail);
    if ( !v_tail ) {
      graph::GraphAdjVertex<T>* new_vertex = graph::newGraphAdjVertex<T>(tail);
      vertices_.push_back(new_vertex);
      valueToIndex_.insert(std::pair<T, int> (tail, vertices_.size() - 1));
    }

    graph::GraphAdjVertex<T>* v_head = getVtx(head);
    if ( !v_head ) {
      graph::GraphAdjVertex<T>* new_vertex = graph::newGraphAdjVertex<T>(head);
      vertices_.push_back(new_vertex);
      valueToIndex_.insert(std::pair<T, int> (head, vertices_.size() - 1));
    }

    // the address may have changed due to the rearrangement of the vector
    v_tail = getVtx(tail);
    graph::Edge<T>* new_edge = graph::newEdge(head, weight);

    graph::Edge<T>* current = v_tail->next;
    graph::Edge<T>* previous = v_tail->next;

    if ( !v_tail->next ) {
      v_tail->next = new_edge;
    } else if ( head == v_tail->next->value ) {
      v_tail->next->weight += weight;
      delete new_edge;
      return;
    } else if ( head < v_tail->next->value ) {
      // insert the new edge in the head
      v_tail->next = new_edge;
      v_tail->next->next = current;
    } else {
      // insert the new edge in the middle
      current = current->next;
      while ( current ) {
        if ( current->value == head ) {
          current->weight += weight;
          delete new_edge;
          return;
        } else if ( current->value > head ) {
          new_edge->next = current;
          previous->next = new_edge;
          return;
        } else {
          current = current->next;
          previous = previous->next;
        }
      }

      // insert the new edge in the tail
      previous->next = new_edge;
    }
  }

  //
  // Delete the edge from tail to head
  //
  // Public method disconnect() is implemented to delete an edge for both
  // directed graph and undirected graph
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: weight of the removed node
  //
  double delEdge(T tail, T head) {
    if ( tail == head ) { return 0; }

    double weight;
    graph::GraphAdjVertex<T>* v_tail = getVtx(tail);
    if ( !v_tail ) { return 0; }
    graph::Edge<T>* current = v_tail->next;
    graph::Edge<T>* previous = v_tail->next;

    if ( v_tail->next->value == head ) {
      // if node is the head node
      v_tail->next = current->next;
      weight = current->weight;
      delete current;

      return weight;
    } else {
      current = current->next;
      while ( current ) {
        if ( current->value == head ) {
          previous->next = current->next;
          weight = current->weight;
          delete current;

          return weight;
        } else {
          previous = previous->next;
          current = current->next;
        }
      }
    }

    return 0;
  }

public:
  //
  // constructor
  //
  GraphAdj() {
    valueToIndex_.max_load_factor(0.5);
  }

  //
  // copy constructor
  //
  GraphAdj(const GraphAdj<T>& g) {
    for (int i=0; i != g.vertices_.size(); ++i) {
      graph::GraphAdjVertex<T>* new_vertex =
          new graph::GraphAdjVertex<T>(*g.vertices_[i]);
      vertices_.push_back(new_vertex);
      vertices_[i]->next = NULL;

      graph::Edge<T>* current_node;
      graph::Edge<T>* current_node_cp = g.vertices_[i]->next;
      while ( current_node_cp ) {
        graph::Edge<T>* new_node = new graph::Edge<T>(*current_node_cp);
        if ( !vertices_[i]->next ) {
          vertices_[i]->next = new_node;
        } else {
          current_node->next = new_node;
        }
        current_node = new_node;
        current_node_cp = current_node_cp->next;
      }
    }

    valueToIndex_ = std::unordered_map<T, int>(g.valueToIndex_);
    assert(valueToIndex_.load_factor() == g.valueToIndex_.load_factor());
  }

  //
  // destructor
  //
  virtual ~GraphAdj() {
    for (auto i = 0; i < vertices_.size() ; ++i) {
      clearList(vertices_[i]->value);
      delete vertices_[i];
    }
  }

  //
  // get No. of vertices in the graph
  //
  std::size_t size() const { return vertices_.size(); }

  //
  // get the index of a vertex by value
  //
  // @param value: the vertex value
  //
  // @return: the vertex index
  //
  int const valueToIndex(T value) const {
    auto search = valueToIndex_.find(value);
    if ( search == valueToIndex_.end() ) {
      return -1;
    } else {
      return search->second;
    }
  }

  //
  // get the value of a vertex by index
  //
  // @param value: the vertex index
  //
  // @return: the vertex value
  //
  T const indexToValue(int idx) const {
    if ( idx > vertices_.size() ) {
      throw std::invalid_argument("Input index is out of range!");
    }

    return vertices_[idx]->value;
  }

  //
  // get the pointer to a const vertex by vertex value
  //
  // @param value: the vertex value
  //
  // @return: pointer to the const vertex
  //
  graph::GraphAdjVertex<T> const* getVertex(T value) const {
    auto search = valueToIndex_.find(value);
    if ( search == valueToIndex_.end() ) {
      return NULL;
    } else {
      return vertices_[search->second];
    }
  }

  //
  // get the pointer to a const vertex by index of the vertex vector
  //
  // @param value: the index
  //
  // @return: pointer to the const vertex
  //
  graph::GraphAdjVertex<T> const* getVertexByIndex(int index) const {
    if ( index < 0 || index >= vertices_.size() ) {
      return NULL;
    } else {
      return vertices_[index];
    }
  }

  //
  // get No. of edges in the graph
  //
  virtual int countEdge() const {
    int count = 0;
    for (int i = 0; i < vertices_.size(); ++i ) {
      graph::Edge<T>* current = vertices_[i]->next;
      while ( current ) {
        ++count;
        current = current->next;
      }
    }

    return count;
  }

  //
  // get a vector of vertices with at least one edge
  //
  std::vector<T> getConnectedVertices() const {
    std::vector<T> connectedVertices;
    for (int i = 0; i < vertices_.size(); ++i) {
      if ( vertices_[i]->next ) {
        connectedVertices.push_back(vertices_[i]->value);
      }
    }

    return connectedVertices;
  }

  //
  // check whether two vertices are connected
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  //
  virtual bool isConnected(T tail, T head) {
    graph::GraphAdjVertex<T>* v_tail = getVtx(tail);
    if ( !v_tail) { return false; }

    if ( tail == head ) { return true; }

    bool connected = false;

    graph::Edge<T>* current = v_tail->next;

    while ( current ) {
      if ( current->value == head ) {
        connected = true;
      }
      current = current->next;
    }

    return connected;
  }

  //
  // connect two vertices
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  // @param weight: the weight of the edge
  //
  // @return: true for success and false for already connected vertices
  //
  virtual bool connect(T tail, T head, double weight=1.0) {
    if ( isConnected(tail, head) ) { return false; }

    addEdge(tail, head, weight);

    return true;
  }

  //
  // disconnect two vertices
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: number of edges between the two vertices
  //
  virtual double disconnect(T tail, T head) {
    double weight = delEdge(tail, head);

    return weight;
  }

  //
  // collapse the vertex src to the vertex dst and empty the linked list for src
  //
  // @param src: the value of the source vertex
  // @param dst: the value of the destination vertex
  //
  virtual void collapse(T src, T dst) {};

  //
  // display the graph
  //
  void display() const {
    std::cout << "------------------------------" << std::endl;

    for (int i = 0; i < vertices_.size(); ++i ) {
      graph::Edge<T>* pprint = vertices_[i]->next;

      std::cout << "Vertex [" << vertices_[i]->value << "] ";
      while (pprint) {
        std::cout << " -> " << pprint->value
                  << " (" << pprint->weight << ")";
        pprint = pprint->next;
      }

      std::cout << std::endl;
    }
  }

};


/*
 * Undirected graph
 */

template <class T>
class UdGraphAdj: public GraphAdj<T> {
private:
  using GraphAdj<T>::vertices_;
  using GraphAdj<T>::valueToIndex_;
  using GraphAdj<T>::addEdge;
  using GraphAdj<T>::delEdge;
  using GraphAdj<T>::clearList;
  using GraphAdj<T>::getVtx;

public:
  //
  // constructor - call default constructor of GraphAdj()
  //
  UdGraphAdj() {}

  //
  // destructor - call default destructor
  //
  ~UdGraphAdj() {}

  //
  // get No. of edges in the graph
  //
  int countEdge() const {
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

  //
  // check whether two vertices are connected
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  //
  bool isConnected(T first, T second) {
    graph::GraphAdjVertex<T>* v_first = getVtx(first);
    graph::GraphAdjVertex<T>*  v_second = getVtx(second);
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

  //
  // connect two vertices
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  // @param weight: the weight of the edge
  //
  // @return: true for success and false for already connected vertices
  //
  bool connect(T first, T second, double weight=1.0) {
    if ( isConnected(first, second) ) { return false; }

    // we need to add a node for the lists a and b respectively
    addEdge(first, second, weight);
    addEdge(second, first, weight);

    return true;
  }

  //
  // disconnect two vertices
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  //
  // @return: weight of the edge between the two vertices
  //
  double disconnect(T first, T second) {
    double weight1 = delEdge(first, second);
    double weight2 = delEdge(second, first);

    assert(weight1 == weight2);

    return weight1;
  }
  //
  // Collapse the vertex source to the vertex destination and empty
  // the linked list for source.
  //
  // @param source: the source vertex value
  // @param destination: the destination vertex value
  //
  void collapse(T source, T destination) {
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
};

#endif //GRAPH_GRAPH_ADJ_H
