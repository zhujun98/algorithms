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
  T val;
  Node* next;
  
  explicit Node(int x) : val(x), next(nullptr) {}
};


using ListNode = Node<int>;


template<typename T>
std::vector<T> toVector(Node<T>* node) {
  std::vector<T> vec;
  
  auto current = node;
  while (current != nullptr) {
    vec.push_back(current->val);
    current = current->next;
  }
  
  return vec;
}

template<typename T>
class LinkedList {
  using node_type = Node<T>;
  
  node_type* head_ = nullptr;

public:
  LinkedList() = default;
  LinkedList(std::initializer_list<T> init_list);

  virtual ~LinkedList();

  LinkedList(const LinkedList<T>& rhs);
  LinkedList<T>& operator=(const LinkedList<T>& rhs);

  LinkedList(LinkedList<T>&& rhs) noexcept;
  LinkedList<T>& operator=(LinkedList<T>&& rhs) noexcept;
  
  node_type* head() const { return head_; }

  void addItem(T v);

  node_type* nthNode(size_t n) const;

  std::vector<T> toVector() const;
};

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> init_list) {
  for (auto v : init_list) addItem(v);
}

template<typename T>
LinkedList<T>::~LinkedList() {
  node_type* next = head_;
  while (next != nullptr) {
    next = head_->next;
    delete head_;
    head_ = next;
  }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs) {
  if (rhs.head_ == nullptr) return;

  head_ = new node_type(rhs.head_->val);
  node_type* curr_other = rhs.head_->next;
  node_type* curr = head_;
  while (curr_other != nullptr) {
    curr->next = new node_type(curr_other->val);
    curr = curr->next;
    curr_other = curr_other->next;
  }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
  if (this != &rhs) {
    // memory of the old data will be freed when tmp is deleted.
    LinkedList<T> tmp(rhs);
    std::swap(tmp.head_, head_);
  }
  return *this;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& rhs) noexcept {
  std::swap(rhs.head_, head_);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& rhs) noexcept {
  LinkedList<T> tmp(std::move(rhs));
  std::swap(tmp.head_, head_);
  return *this;
}

template<typename T>
void LinkedList<T>::addItem(T v) {
  auto node = new node_type(v);

  if (head_ == nullptr) {
    head_ = node;
    return;
  }

  node_type* curr = head_;
  while (curr->next != nullptr) curr = curr->next;
  curr->next = node;
}

template<typename T>
typename LinkedList<T>::node_type* LinkedList<T>::nthNode(size_t n) const {
  if (n == 0) return head_;

  size_t i = 0;
  node_type* curr = head_;
  while (curr != nullptr) {
    curr = curr->next;
    if (++i == n) return curr;
  }
  throw std::out_of_range("Invalid input");
}

template<typename T>
std::vector<T> LinkedList<T>::toVector() const {
  return ::toVector(head_);
}

#endif  // LEECODE_LINKED_LIST_H
