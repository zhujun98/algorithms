//
// Created by jun on 8/19/17.
//
#include "graph.h"


template <class T>
Graph<T>::Graph() {
  valueToIndex_.max_load_factor(0.5);
}

template <class T>
Graph<T>::Graph(const Graph<T>& g) {
  for (int i=0; i != g.vertices_.size(); ++i) {
    graph::Vertex<T>* new_vertex =
        new graph::Vertex<T>(*g.vertices_[i]);
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

template <class T>
Graph<T>::~Graph() {
  for (auto i = 0; i < vertices_.size() ; ++i) {
    clearList(vertices_[i]->value);
    delete vertices_[i];
  }
}

template <class T>
graph::Vertex<T>* Graph<T>::getVtx(T value) {
  auto search = valueToIndex_.find(value);
  if ( search == valueToIndex_.end() ) {
    return NULL;
  } else {
    return vertices_[search->second];
  }
}

template <class T>
void Graph<T>::clearList(T value) {
  graph::Vertex<T>* v = getVtx(value);
  if ( !v->next ) { return; }

  graph::Edge<T>* current = v->next;
  while ( current ) {
    v->next = current->next;
    delete current;
    current = v->next;
  }
}

template <class T>
void Graph<T>::addEdge(T tail, T head, double weight) {
  if ( tail == head ) { return; }

  graph::Vertex<T>* v_tail = getVtx(tail);
  if ( !v_tail ) {
    graph::Vertex<T>* new_vertex = graph::newVertex<T>(tail);
    vertices_.push_back(new_vertex);
    valueToIndex_.insert(std::pair<T, int> (tail, vertices_.size() - 1));
  }

  graph::Vertex<T>* v_head = getVtx(head);
  if ( !v_head ) {
    graph::Vertex<T>* new_vertex = graph::newVertex<T>(head);
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

template <class T>
double Graph<T>::delEdge(T tail, T head) {
  if ( tail == head ) { return 0; }

  double weight;
  graph::Vertex<T>* v_tail = getVtx(tail);
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

template <class T>
std::size_t Graph<T>::size() const { return vertices_.size(); }

template <class T>
int const Graph<T>::valueToIndex(T value) const {
  auto search = valueToIndex_.find(value);
  if ( search == valueToIndex_.end() ) {
    return -1;
  } else {
    return search->second;
  }
}

template <class T>
T const Graph<T>::indexToValue(int idx) const {
  if ( idx > vertices_.size() ) {
    throw std::invalid_argument("Input index is out of range!");
  }

  return vertices_[idx]->value;
}

template <class T>
graph::Vertex<T> const* Graph<T>::getVertex(T value) const {
  auto search = valueToIndex_.find(value);
  if ( search == valueToIndex_.end() ) {
    return NULL;
  } else {
    return vertices_[search->second];
  }
}

template <class T>
graph::Vertex<T> const* Graph<T>::getVertexByIndex(int index) const {
  if ( index < 0 || index >= vertices_.size() ) {
    return NULL;
  } else {
    return vertices_[index];
  }
}

template <class T>
int Graph<T>::countEdge() const {
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

template <class T>
double Graph<T>::countWeightedEdge() const {
  int count = 0;
  for (int i = 0; i < vertices_.size(); ++i ) {
    graph::Edge<T>* current = vertices_[i]->next;
    while ( current ) {
      count += current->weight;
      current = current->next;
    }
  }

  return count;
}

template <class T>
std::vector<T> Graph<T>::getConnectedVertices() const {
  std::vector<T> connectedVertices;
  for (int i = 0; i < vertices_.size(); ++i) {
    if ( vertices_[i]->next ) {
      connectedVertices.push_back(vertices_[i]->value);
    }
  }

  return connectedVertices;
}

template <class T>
bool Graph<T>::isConnected(T tail, T head) {
  graph::Vertex<T>* v_tail = getVtx(tail);
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

template <class T>
bool Graph<T>::connect(T tail, T head, double weight) {
  if ( isConnected(tail, head) ) { return false; }

  addEdge(tail, head, weight);

  return true;
}

template <class T>
double Graph<T>::disconnect(T tail, T head) {
  double weight = delEdge(tail, head);

  return weight;
}

template <class T>
void Graph<T>::collapse(T src, T dst) {};

template <class T>
void Graph<T>::display() const {
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

template class Graph<int>;
template class Graph<double>;
template class Graph<std::string>;