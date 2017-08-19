//
// Created by jun on 8/19/17.
//
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H


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
  };

  //
  // vertex of the graph, containing head node of the linked list
  //
  template <class T>
  struct Vertex {
    T value;  // value of the vertex
    Edge<T>* next;  // head node of the linked list
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
  // construct a new Vertex
  //
  // @param value: value of the vertex
  //
  // @return: pointer to the new vertex
  //
  template <class T>
  Vertex<T>* newVertex(T value) {

    Vertex<T>* new_vertex = new Vertex<T>;
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


template <class T>
class Graph {

protected:
  // hash table that converts the vertex value to the vector index
  std::unordered_map<T, int> valueToIndex_;

  // vector of vertices
  std::vector<graph::Vertex<T>*> vertices_;

  //
  // get the pointer to a vertex
  //
  // @param value: the vertex value
  //
  // @return: pointer to the vertex
  //
  graph::Vertex<T>* getVtx(T value);

  //
  // clear (release memory) the linked list belong to a vertex
  //
  // @param vertex: the vertex value
  //
  void clearList(T value);

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
  void addEdge(T tail, T head, double weight);

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
  double delEdge(T tail, T head);

public:
  //
  // constructor
  //
  Graph();

  //
  // copy constructor
  //
  Graph(const Graph<T>& g);

  //
  // destructor
  //
  virtual ~Graph();

  //
  // get No. of vertices in the graph
  //
  std::size_t size() const;

  //
  // get the index of a vertex by value
  //
  // @param value: the vertex value
  //
  // @return: the vertex index
  //
  int const valueToIndex(T value) const;

  //
  // get the value of a vertex by index
  //
  // @param value: the vertex index
  //
  // @return: the vertex value
  //
  T const indexToValue(int idx) const;

  //
  // get the pointer to a const vertex by vertex value
  //
  // @param value: the vertex value
  //
  // @return: pointer to the const vertex
  //
  graph::Vertex<T> const* getVertex(T value) const;

  //
  // get the pointer to a const vertex by index of the vertex vector
  //
  // @param value: the index
  //
  // @return: pointer to the const vertex
  //
  graph::Vertex<T> const* getVertexByIndex(int index) const;

  //
  // get No. of edges in the graph
  //
  virtual int countEdge() const;

  //
  // get the sum of weights of all the edges in the graph
  //
  virtual double countWeightedEdge() const;

  //
  // get a vector of vertices with at least one edge
  //
  std::vector<T> getConnectedVertices() const;

  //
  // check whether two vertices are connected
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  //
  virtual bool isConnected(T tail, T head);

  //
  // connect two vertices
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  // @param weight: the weight of the edge
  //
  // @return: true for success and false for already connected vertices
  //
  virtual bool connect(T tail, T head, double weight=1.0);

  //
  // disconnect two vertices
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: number of edges between the two vertices
  //
  virtual double disconnect(T tail, T head);

  //
  // collapse the vertex src to the vertex dst and empty the linked list for src
  //
  // @param src: the value of the source vertex
  // @param dst: the value of the destination vertex
  //
  virtual void collapse(T src, T dst);

  //
  // display the graph
  //
  void display() const;

};

#endif //GRAPH_GRAPH_H