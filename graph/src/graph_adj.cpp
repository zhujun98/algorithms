//
// Created by jun on 6/6/17.
//
// implementation of the directed and undirected graph using adjacency list
//
#include <iostream>
#include <assert.h>
#include <stack>
#include <queue>

#include "graph_adj.h"
#include "graph_utilities.h"


namespace graph {

  AdjListNode* newAdjListNode(int v, int weight) {

    AdjListNode* new_node =new graph::AdjListNode;
    new_node->value = v;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
  }

}


GraphAdj::GraphAdj(unsigned int n) {
  graph::GraphAdjVertex adj_list;
  // initialize a adjacency list with n elements (head nodes)
  for (int i = 0; i < n; ++i) {
    adj_list.value = 0;
    adj_list.visited = false;
    adj_list.head = NULL;

    vertices_.push_back(adj_list);
  }
}

GraphAdj::~GraphAdj() {
  for (int i=0; i<vertices_.size();++i) {
    clearList(i);
  }
}

std::size_t GraphAdj::size() const { return vertices_.size(); }

int GraphAdj::countEdge() const {
  int count = 0;
  for (int i=0; i<vertices_.size(); ++i) {
    graph::AdjListNode* current = vertices_[i].head;
    while ( current ) {
      count += current->weight;
      current = current->next;
    }
  }

  return count;
}

std::vector<int> GraphAdj::getConnectedVertices() const {

  std::vector<int> connectedVertices;

  for (int i=0; i<vertices_.size(); ++i) {
    if ( vertices_[i].head ) {
      connectedVertices.push_back(i);
    }
  }

  return connectedVertices;
}

graph::GraphAdjVertex GraphAdj::getVertex(int value) const {
  return vertices_[value];
}


void GraphAdj::clearList(int vertex) {

  graph::AdjListNode* current = vertices_[vertex].head;

  if ( !vertices_[vertex].head ) { return; }

  while ( current ) {
    vertices_[vertex].head = current->next;
    delete current;
    current = vertices_[vertex].head;
  }
}

void GraphAdj::addEdge(int first, int second, int weight) {

  assert(first != second);

  graph::AdjListNode* new_node = graph::newAdjListNode(second);
  new_node->weight = weight;

  graph::AdjListNode* current = vertices_[first].head;
  graph::AdjListNode* previous = vertices_[first].head;

  if ( !vertices_[first].head) {
    // the linked list is empty
    vertices_[first].head = new_node;
  } else if ( second == vertices_[first].head->value ) {
    vertices_[first].head->weight += weight;
    delete new_node;
    return;
  } else if ( second < vertices_[first].head->value ) {
    // insert the new node in the head
    vertices_[first].head = new_node;
    vertices_[first].head->next = current;
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
int GraphAdj::delEdge(int first, int second) {

  assert(first != second);

  int weight;

  if ( !vertices_[first].head ) { return 0; }

  graph::AdjListNode* current = vertices_[first].head;
  graph::AdjListNode* previous = vertices_[first].head;

  if ( vertices_[first].head->value == second ) {
    // if node is the head node
    vertices_[first].head = current->next;
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

bool GraphAdj::connect(int first, int second) {

  assert(first != second);

  if ( isConnected(first, second) ) { return false; }

  addEdge(first, second, 1);

  return true;
}

int GraphAdj::disconnect(int first, int second) {

  assert(first != second);

  int weight = delEdge(first, second);

  return weight;
}

bool GraphAdj::isConnected(int first, int second) const {

  bool connected = false;

  graph::AdjListNode* current = vertices_[first].head;

  while ( current ) {
    if ( current->value == second ) {
      connected = true;
    }
    current = current->next;
  }

  return connected;
}

void GraphAdj::collapse(int src, int dst) {}

void GraphAdj::display() const {
  std::cout << "------------------------------" << std::endl;

  for (int i=0; i<vertices_.size(); ++i) {
    graph::AdjListNode* pprint = vertices_[i].head;

    std::cout << "Vertex [" << i << "] (visited = "
              << vertices_[i].visited << " )";
    while (pprint) {
      std::cout << " -> " << pprint->value << " (" << pprint->weight << ")";
      pprint = pprint->next;
    }

    std::cout << std::endl;
  }
}

std::vector<int> GraphAdj::BFS(int vertex) {

  std::vector<int> visited;
  std::queue<int> tracker;

  tracker.push(vertex);
  visited.push_back(vertex);
  vertices_[vertex].visited = true;
  while (!tracker.empty()) {
    int current_vertex = tracker.front();
    tracker.pop();

    graph::GraphAdjVertex *current_head = &vertices_[current_vertex];

    graph::AdjListNode* current_node = current_head->head;
    // find all children vertices which have not been visited yet
    while (current_node) {
      if ( !vertices_[current_node->value].visited ) {
        // move to the next node
        tracker.push(current_node->value);
        visited.push_back(current_node->value);
        vertices_[current_node->value].visited = true;
      }
      current_node = current_node->next;
    }
  }

  return visited;
}

std::vector<int> GraphAdj::DFS(int vertex) {

  std::vector<int> sink;
  std::stack<int> tracker;

  tracker.push(vertex);
  // search the vertex reachable from the current vertex
  while ( !tracker.empty() ) {
    // retreat to the last vertex
    int current_vertex = tracker.top();
    graph::GraphAdjVertex* current_head = &vertices_[current_vertex];
    current_head->visited = true;

    bool retreat = true;  // a flag indicating whether to retreat to the last vertex
    graph::AdjListNode* current_node = current_head->head;
    // find the next reachable vertex which has not been visited
    while ( current_node ) {
      graph::GraphAdjVertex* next_head = &vertices_[current_node->value];
      if ( !next_head->visited ) {
        // move to the next vertex
        current_head = next_head;
        // mark the vertex visited
        current_head->visited = true;
        // store the vertex in the stack
        tracker.push(current_node->value);

        retreat = false;
        break;
      }
      current_node = current_node->next;
    }
    // find a sink vertex
    if ( retreat ) {
      // store the sink vertex
      sink.push_back(current_vertex);
      // remove the sink vertex from stack
      tracker.pop();
    }
  }

  return sink;
}


UdGraphAdj::UdGraphAdj(unsigned int n) : GraphAdj(n) {}

UdGraphAdj::~UdGraphAdj() {}

int UdGraphAdj::countEdge() const {
  int count = 0;
  for (int i=0; i<vertices_.size(); ++i) {
    graph::AdjListNode* current = vertices_[i].head;
    while ( current ) {
      count += current->weight;
      current = current->next;
    }
  }

  assert( count % 2 == 0 );

  return count/2;
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
  graph::AdjListNode* current = vertices_[src].head;
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

bool UdGraphAdj::isConnected(int first, int second) const {

  bool connected1 = false;
  bool connected2 = false;

  graph::AdjListNode* current = vertices_[first].head;

  while ( current ) {
    if ( current->value == second ) {
      connected1 = true;
    }
    current = current->next;
  }

  current = vertices_[second].head;

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
