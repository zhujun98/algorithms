//
// Created by jun on 6/6/17.
//
// implementation of the directed and undirected graph using adjacency list
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
#include <list>
#include <vector>

namespace graph {
  //
  // node in a linked list
  //
  struct AdjListNode {
    int value;  // value of the corresponding vertex
    int weight;  // weight of the connection between the head vertex and this node
    double distance;  // distance from the head vertex to this node
    AdjListNode* next;  // pointer to the next node
  };

  //
  // vertex of the graph, stored in vector
  //
  struct GraphAdjVertex {
    bool visited;  // flag indicate whether a vertex has been visited
    AdjListNode* head;  // head node of the linked list
  };

  //
  // construct a new AdjListNode
  //
  // @param value: value of the corresponding vertex
  // @param weight: weight of the connection between the head vertex and this node
  // @param distance: distance from the head vertex to this node
  //
  // @return: pointer of the new node
  //
  AdjListNode* newAdjListNode(int value, int weight=1, double distance=1.0);

}

/*
 * Directed graph
 */
class GraphAdj {

protected:
  //
  // clear (release memory) the linked list belonged to a vertex
  //
  // @param vertex: the vertex value
  //
  void clearList(int vertex);

  std::vector<graph::GraphAdjVertex> vertices_;

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
  // @param distance: the distance of the edge
  //
  void addEdge(int tail, int head, int weight, double distance);

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
  int delEdge(int tail, int head);

public:
  //
  // constructor
  //
  // @param n: the total number of vertices
  //
  GraphAdj(unsigned int n);

  //
  // destructor
  //
  virtual ~GraphAdj();

  //
  // get No. of vertices in the graph
  //
  std::size_t size() const;

  //
  // get No. of edges in the graph
  //
  virtual int countEdge() const;

  //
  // get a vector of vertices with at least one edge
  //
  std::vector<int> getConnectedVertices() const;

  //
  // get a vertex
  //
  // @param value: the vertex value
  //
  // @return: vertex
  //
  graph::GraphAdjVertex getVertex(int value) const;

  //
  // check whether two vertices are connected
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  //
  virtual bool isConnected(int tail, int head) const;

  //
  // connect two vertices
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  // @param weight: the weight of the edge
  // @param distance: the distance of the edge
  //
  // @return: true for success and false for already connected vertices
  //
  virtual bool connect(int tail, int head, int weight=1, double distance=1.0);

  //
  // disconnect two vertices
  //
  // @param tail: the tail vertex value
  // @param head: the head vertex value
  //
  // @return: number of edges between the two vertices
  //
  virtual int disconnect(int tail, int head);

  //
  // collapse the vertex src to the vertex dst and empty the linked list for src
  //
  // @param src: the value of the source vertex
  // @param dst: the value of the destination vertex
  //
  virtual void collapse(int src, int dst);

  //
  // Apply breath-first-search (BFS) from a vertex
  //
  // @param vertex: starting vertex value
  //
  // @return: a vector of visited vertices, ordered by finding time
  //
  std::vector<int> breathFirstSearch(int value);

  //
  // Apply depth-first-search (DFS) from a vertex
  //
  // @param value: starting vertex value
  //
  // @return: a vector of sink vertices, ordered by finding time
  //
  std::vector<int> depthFirstSearch(int value);

  //
  // display the graph
  //
  void display() const;

};


/*
 * Undirected graph
 */
class UdGraphAdj: public GraphAdj {
public:
  //
  // constructor
  //
  UdGraphAdj(unsigned int);

  //
  // destructor
  //
  ~UdGraphAdj();

  //
  // get No. of edges in the graph
  //
  int countEdge() const;

  //
  // check whether two vertices are connected
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  //
  bool isConnected(int first, int second) const;

  //
  // connect two vertices
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  // @param weight: the weight of the edge
  // @param distance: the distance of the edge
  //
  // @return: true for success and false for already connected vertices
  //
  bool connect(int first, int second, int weight=1, double distance=1);


  // disconnect two vertices
  //
  // @param first: the first vertex value
  // @param second: the second vertex value
  //
  // @return: number of edges between the two vertices
  //
  int disconnect(int first, int second);

  //
  // collapse the vertex src to the vertex dst and empty the linked list for src
  //
  // @param src: value of the source vertex
  // @param dst: value of the destination vertex
  //
  void collapse(int src, int dst);
};

#endif //GRAPH_GRAPH_ADJ_H
