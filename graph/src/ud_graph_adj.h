//
// Created by jun on 6/6/17.
//
// implementation of the undirected graph using adjacency list
//

#ifndef GRAPH_UD_GRAPH_ADJ_H
#define GRAPH_UD_GRAPH_ADJ_H


#include <iostream>
#include <list>
#include <vector>

//
// adjacency list node
//
struct AdjListNode {
  int value;  // value of the node
  int weight;  // weight of the node
  AdjListNode* next;  // pointer to the next node
};

//
// adjacency list, only the head node is required here
//
struct AdjList {
  AdjListNode* head;  // an array of heads of linked lists
};

class UdGraphAdj {
private:

  int n_vertex_;  // number of vertices

  AdjList* adj_list_;  // an array of adjacency list

public:

  //
  // constructor
  //
  // @param n: total number of vertices
  //
  UdGraphAdj(int n);

  //
  // destructor
  //
  ~UdGraphAdj();

  //
  // get No. of vertices in the graph
  //
  int nVertex();

  //
  // get No. of edges in the graph
  //
  int nEdge();

  //
  // get a vector of vertices with non-empty linked lists
  //
  std::vector<int> nonEmptyVertex();

  //
  // clear the linked list (release memory) corresponding to vertex "node"
  //
  // @param vertex: vertex value
  //
  void clearList(int vertex);

  //
  // add an edge (first, second)
  // The nodes in the linked list are sorted in ascending order
  // Note: the sorting will not increase the complexity since it is
  //       anyhow necessary to traverse the list to check the existence
  //       of the identical node.
  //
  // @param first: first vertex
  // @param second: second vertex
  // @param weight: weight of source node
  //
  void addEdge(int first, int second, int weight=1);

  //
  // delete the edge (first, second)
  //
  // @param first: the first vertex
  // @param second: the second vertex
  //
  // @return: weight of the removed node
  //
  int delEdge(int first, int second);

  //
  // check whether two vertices are connected
  //
  // @param first: the first vertex
  // @param second: the second vertex
  //
  // @return: true for connected and false for unconnected. Throw an error
  //          if the two vertices are only partially connected.
  bool isConnected(int first, int second);

  //
  // connect two vertices
  //
  // @param first: the first vertex
  // @param second: the second vertex
  //
  // @return: true for success and false for already connected vertices
  //
  bool connect(int first, int second);

  //
  // disconnect two vertices
  //
  // @param first: the first vertex
  // @param second: the second vertex
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

  //
  // display the graph
  //
  void display();

};


#endif //GRAPH_UD_GRAPH_ADJ_H
