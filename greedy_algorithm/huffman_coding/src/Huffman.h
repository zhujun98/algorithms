//
// Created by jun on 8/3/17.
//

#ifndef HUFFMAN_CODING_HUFFMAN_H
#define HUFFMAN_CODING_HUFFMAN_H

#include <iostream>
#include <vector>


struct Node {
  int value;
  int frequency;
  Node* left;
  Node* right;
};

inline Node* newNode(int value, int frequency) {
  Node* node = new Node();
  node->value = value;
  node->frequency = frequency;
  node->left = nullptr;
  node->right = nullptr;
}

class Huffman {
private:

  Node* root_;

  void destroyTree(Node* node);

public:
  Huffman();

  ~Huffman();

  void buildTree(const std::vector<int>& value, const std::vector<int>& frequency);

  void printTree() const;
  void printTree(Node* node) const;

  int minDepth() const;
  int minDepth(Node* node) const;

  int maxDepth() const;
  int maxDepth(Node* node) const;
};


#endif //HUFFMAN_CODING_HUFFMAN_H
