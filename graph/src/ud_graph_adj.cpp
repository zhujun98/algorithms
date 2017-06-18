//
// Created by jun on 6/6/17.
//
// implementation of the undirected graph using adjacency list
//
#include <assert.h>

#include "ud_graph_adj.h"

//
// construct a new AdjListNode
//
// @param v: value of the node
// @param weight: weight of the node
//
// @return: pointer of the new node
//
AdjListNode* newAdjListNode(int v, int weight=1) {

  AdjListNode* new_node = new AdjListNode;
  new_node->value = v;
  new_node->weight = weight;
  new_node->next = NULL;

  return new_node;
}


UdGraphAdj::UdGraphAdj(int n) {
  n_vertex_ = n;

  // initialize a adjacency list with n elements (head nodes)
  adj_list_ = new struct AdjList[n];
  for (int i=0; i<n; ++i) {
    adj_list_[i].head = NULL;
  }
}

UdGraphAdj::~UdGraphAdj() {}

int UdGraphAdj::nVertex() { return n_vertex_; }

int UdGraphAdj::nEdge() {
  int count = 0;
  for (int i=0; i<n_vertex_; ++i) {
    AdjListNode* current = adj_list_[i].head;
    while ( current ) {
      count += current->weight;
      current = current->next;
    }
  }

  assert( count % 2 == 0 );

  return count/2;
}

std::vector<int> UdGraphAdj::nonEmptyVertex() {

  std::vector<int> nonEmptyVertex;

  for (int i=0; i<n_vertex_; ++i) {
    if ( adj_list_[i].head ) {
      nonEmptyVertex.push_back(i);
    }
  }

  return nonEmptyVertex;
}

void UdGraphAdj::clearList(int vertex) {

  AdjListNode* current = adj_list_[vertex].head;

  if ( !adj_list_[vertex].head ) { return; }

  while ( current ) {
    adj_list_[vertex].head = current->next;
    delete current;
    current = adj_list_[vertex].head;
  }
}

void UdGraphAdj::addEdge(int first, int second, int weight) {

  assert(first != second);

  AdjListNode* new_node = newAdjListNode(second);
  new_node->weight = weight;

  AdjListNode* current = adj_list_[first].head;
  AdjListNode* previous = adj_list_[first].head;

  if ( !adj_list_[first].head) {
    // the linked list is empty
    adj_list_[first].head = new_node;
  } else if ( second == adj_list_[first].head->value ) {
    adj_list_[first].head->weight += weight;
    delete new_node;
    return;
  } else if ( second < adj_list_[first].head->value ) {
    // insert the new node in the head
    adj_list_[first].head = new_node;
    adj_list_[first].head->next = current;
  } else {
    // insert the new node in the middle
    current = current->next;
    while ( current ) {
      if ( current->value == second ) {
        current->weight += weight;
        delete new_node;

        return;
      } else if ( current->value > second ) {
        new_node->next = current;
        previous->next = new_node;

        return;
      } else {
        current = current->next;
        previous = previous->next;
      }
    }

    // insert the new node in the tail
    previous->next = new_node;
  }
}

//
// complexity O(n)
//
int UdGraphAdj::delEdge(int first, int second) {

  assert(first != second);

  int weight;

  if ( !adj_list_[first].head ) { return 0; }

  AdjListNode* current = adj_list_[first].head;
  AdjListNode* previous = adj_list_[first].head;

  if ( adj_list_[first].head->value == second ) {
    // if node is the head node
    adj_list_[first].head = current->next;
    weight = current->weight;
    delete current;

    return weight;

  } else {
    current = current->next;
    while ( current ) {
      if ( current->value == second ) {
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

bool UdGraphAdj::isConnected(int first, int second) {

  bool connected1 = false;
  bool connected2 = false;

  AdjListNode* current = adj_list_[first].head;

  while ( current ) {
    if ( current->value == second ) {
      connected1 = true;
    }
    current = current->next;
  }

  current = adj_list_[second].head;

  while ( current ) {
    if ( current->value == first ) {
      connected2 = true;
    }
    current = current->next;
  }

  if ( connected1 && connected2 ) {
    return true;
  } else if ( connected1 || connected2 ) {
    throw std::invalid_argument("two vertices are only partially connected");
  } else {
    return false;
  }
}

bool UdGraphAdj::connect(int first, int second) {

  assert(first != second);

  if ( isConnected(first, second) ) { return false; }

  // we need to add a node for the lists a and b respectively
  addEdge(first, second, 1);
  addEdge(second, first, 1);

  return true;
}

int UdGraphAdj::disconnect(int first, int second) {

  assert(first != second);

  int weight1 = delEdge(first, second);
  int weight2 = delEdge(second, first);

  assert(weight1 == weight2);

  return weight1;
}

//
// Nodes will be moved around and no new node will be generated.
// complexity O(n) + O(n^2) + O(n) = O(n^2)
//
void UdGraphAdj::collapse(int src, int dst) {

  assert(src != dst);

  // first remove loops
  disconnect(src, dst);

  // In each collapse, the No. of edges will be reduced only by the No. of edges
  // between the source and destination vertices!

  // change the value of nodes with value src to dst
  AdjListNode* current = adj_list_[src].head;
  while ( current ) {
    // change the node with value 'src' in other linked lists to 'dst'
    // TODO:: this could be fast since the linked list is traversed twice here for code simplicity
    int weight = delEdge(current->value, src);
    addEdge(current->value, dst, weight);

    // add node in the linked list 'src' to the linked list 'dst'
    addEdge(dst, current->value, current->weight);

    current = current->next;
  }

  // delete linked list and release memory
  clearList(src);

}

void UdGraphAdj::display() {
  std::cout << "------------------------------" << std::endl;

  for (int i=0; i<n_vertex_; ++i) {
    AdjListNode* pprint = adj_list_[i].head;

    std::cout << "adjacency list of vertex [" << i << "] head";
    while (pprint) {
      std::cout << " -> " << pprint->value << " (" << pprint->weight << ")";
      pprint = pprint->next;
    }

    std::cout << std::endl;
  }
}
