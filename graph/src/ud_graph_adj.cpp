//
// Created by jun on 6/6/17.
//

#include "ud_graph_adj.h"


UdGraphAdj::UdGraphAdj(int n) {
  n_vertex_ = n;
  n_edge_ = 0;

  // initialize a adjacency list with n elements (head nodes)
  adj_list_ = new struct AdjList[n];
  for (int i=0; i<n; ++i) {
    adj_list_[i].head = NULL;
  }

}

UdGraphAdj::~UdGraphAdj() {}

AdjListNode* newAdjListNode(int v) {

  AdjListNode* new_node = new AdjListNode;
  new_node->value = v;
  new_node->next = NULL;

  return new_node;
}

void UdGraphAdj::addEdge(int a, int b) {

  // we need to add a node for the lists a and b respectively

  // in the list a, we first initialize a new node b
  AdjListNode* new_node = newAdjListNode(b);
  // then we insert the new node at the head
  // Note: for a linked list, this is the cheapest way
  new_node->next = adj_list_[a].head;
  // move the head to the new node
  adj_list_[a].head = new_node;

  // do the same thing for list b
  new_node = newAdjListNode(a);
  new_node->next = adj_list_[b].head;
  adj_list_[b].head = new_node;

  // only one edge is actually added
  ++n_edge_;
}

void UdGraphAdj::delEdgeNode(int a, int b) {

  AdjListNode* current = adj_list_[a].head;
  AdjListNode* previous = adj_list_[a].head;

  if ( current->value == b ) {
    adj_list_[a].head = current->next;
    delete current;
  } else {
    current = current->next;
    while ( current ) {
      if ( current->value == b ) {
        previous->next = current->next;
        delete current;
        break;
      } else {
        previous = previous->next;
        current = current->next;
      }
    }
  }
}

void UdGraphAdj::delEdge(int a, int b) {

  // we need to delete a node in lists a and b respectively

  delEdgeNode(a, b);
  delEdgeNode(b, a);

  --n_edge_;
}

void UdGraphAdj::delVertexEdge(int v) {

  AdjListNode* conductor = adj_list_[v].head;
  while ( conductor ) {
    AdjListNode* tmp = adj_list_[conductor->value].head;
    while ( tmp ) {
      if ( tmp->value == v ) {
        delEdge(conductor->value, v);
        break;
      } else {
        tmp = tmp->next;
      }
    }
    conductor = conductor->next;
  }
}

void UdGraphAdj::printGraph() {
  for (int i=0; i<n_vertex_; ++i) {
    AdjListNode* pprint = adj_list_[i].head;

    std::cout << "adjacency list of vertex [" << i << "] head";
    while (pprint) {
      std::cout << " -> " << pprint->value;
      pprint = pprint->next;
    }

    std::cout << std::endl;
  }
}

void UdGraphAdj::contract(int a, int b) {
  delEdge(a, b);
}

void UdGraphAdj::validateVertex(int v) {

  if ( v < 0 || v > n_vertex_ ) {
    throw std::invalid_argument("vertex is out of range");
  }
}