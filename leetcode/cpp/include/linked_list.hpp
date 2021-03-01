/**
 * Author: Jun Zhu, zhujun981661@gmail.com
 *
 */
 
#ifndef LEECODE_LINKED_LIST_H
#define LEECODE_LINKED_LIST_H

#include <iostream>
#include <vector>
#include <memory>


template<typename T>
struct Node {
  using value_type = T;
  
  value_type val;
  Node* next;
  
  explicit Node(int x) : val(x), next(nullptr) {}
};


using ListNode = Node<int>;


template<typename T>
std::vector<T> listToVector(Node<T>* node) {
  std::vector<T> vec;
  
  auto current = node;
  while (current != nullptr) {
    vec.push_back(current->val);
    current = current->next;
  }
  
  return vec;
}


template<typename T>
void free_list(Node<T>* node) {
  Node<T>* current = node;
  Node<T>* next = current;

  while (current != nullptr) {
      next = current->next;
      delete current;
      current = next;
  }
}


template<typename T>
class LinkedList {
  using node_type = Node<T>;
  
  node_type* head_ = nullptr;
  node_type* tail_ = nullptr;
  
public:
  
  using value_type = typename node_type::value_type;
  
  LinkedList() = default;
  
  LinkedList(std::initializer_list<value_type> init_list) {
    for (auto v : init_list) addItem(v);
  }
  
  ~LinkedList() {
    free_list(head_);
  };
  
  node_type* head() const { return head_; }
  
  void nullify() { head_ = nullptr; }
  
  void addItem(value_type v) {
    auto tmp = new node_type(v);
    
    if (head_ == nullptr) {
      head_ = tmp;
      tail_ = head_;
    } else {
      tail_->next = tmp;
      tail_ = tmp;
    }
  }
  
  std::vector<value_type> toVector() const {
    return listToVector(head_);
  }
};

#endif  // LEECODE_LINKED_LIST_H
