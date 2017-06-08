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

void UdGraphAdj::addNode(int llst, int nd, int weight) {

  assert(llst != nd);

  AdjListNode* new_node = newAdjListNode(nd);
  new_node->weight = weight;

  AdjListNode* current = adj_list_[llst].head;
  AdjListNode* previous = adj_list_[llst].head;

  if ( !adj_list_[llst].head) {
    // the linked list is empty
    adj_list_[llst].head = new_node;
  } else if ( nd == adj_list_[llst].head->value ) {
    adj_list_[llst].head->weight += weight;
    delete new_node;
    return;
  } else if ( nd < adj_list_[llst].head->value ) {
    // insert the new node in the head
    adj_list_[llst].head = new_node;
    adj_list_[llst].head->next = current;
  } else {
    // insert the new node in the middle
    current = current->next;
    while ( current ) {
      if ( current->value == nd ) {
        current->weight += weight;
        delete new_node;
        return;
      } else if ( current->value > nd ) {
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
  addNode(first, second, 1);
  addNode(second, first, 1);

  return true;
}

//
// complexity O(n)
//
int UdGraphAdj::removeNode(int llst, int nd) {

  assert(llst != nd);

  int weight;

  if ( !adj_list_[llst].head ) { return 0; }

  AdjListNode* current = adj_list_[llst].head;
  AdjListNode* previous = adj_list_[llst].head;

  if ( adj_list_[llst].head->value == nd ) {
    // if node is the head node
    adj_list_[llst].head = current->next;
    weight = current->weight;
    delete current;

    return weight;

  } else {
    current = current->next;
    while ( current ) {
      if ( current->value == nd ) {
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

int UdGraphAdj::disconnect(int first, int second) {

  assert(first != second);

  int weight1 = removeNode(first, second);
  int weight2 = removeNode(second, first);

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
    int weight = removeNode(current->value, src);
    addNode(current->value, dst, weight);

    current = current->next;
  }

  // merge two linked list
  AdjListNode* current_dst = adj_list_[dst].head;
  AdjListNode* current_src = adj_list_[src].head;
  AdjListNode* previous_dst = adj_list_[dst].head;
  AdjListNode* tmp;

  if ( !current_src ) { return; }

  if ( !current_dst || current_src->value < current_dst->value ) {
    // insert the head node in linked list a at the head of linked list b
    //
    // This is a move operation, so the weight does not need to be changed
    adj_list_[src].head = current_src->next;

    adj_list_[dst].head = current_src;
    adj_list_[dst].head->next = current_dst;

    current_dst = adj_list_[dst].head->next;
    previous_dst = adj_list_[dst].head;

    current_src = adj_list_[src].head;
  } else if ( current_src->value == current_dst->value ) {

    // if the values of the head nodes are equal
    current_dst->weight += current_src->weight;

    current_src = current_src->next;
    current_dst = current_dst->next;

  } else {

    current_dst = current_dst->next;

  }

  if ( !current_src ) { adj_list_[src].head = NULL; }

  while ( current_src ) {
    if ( !current_dst ) {

      // move all the node in the source to the tail of the destination
      previous_dst->next = current_src;
      adj_list_[src].head = NULL;

      break;

    } else {
      // move one node in the source to the destination
      if ( current_src->value > current_dst->value ) {
        current_dst = current_dst->next;
        previous_dst = previous_dst->next;

      } else {
        if ( current_src->value < current_dst->value ) {
          tmp = current_src->next;
          previous_dst->next = current_src;
          current_src->next = current_dst;
          previous_dst = current_src;
          current_src = tmp;
        } else { // current_src->value == current_dst->value
          current_dst->weight += current_src->weight;
          tmp = current_src;
          current_src = current_src->next;
          delete tmp;
        }
      }
    }
  }

  adj_list_[src].head = NULL;

}

void UdGraphAdj::printGraph() {
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
