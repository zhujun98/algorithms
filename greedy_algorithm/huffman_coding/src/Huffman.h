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

//
// Generate a new node
//
inline Node* newNode(int value, int frequency) {
  Node* node = new Node();
  node->value = value;
  node->frequency = frequency;
  node->left = nullptr;
  node->right = nullptr;
}

class Huffman {
private:

  Node* root_; // store root of the hoffman tree

  //
  // release the memory of tree nodes rooted at a certain node
  //
  void destroyTree(Node* node);

public:

  //
  // constructor
  //
  Huffman();

  //
  // destructor
  //
  ~Huffman();

  //
  // Build a Hoffman tree
  //
  // @param values: a vector of node values
  // @param weights: a vector of node weights (frequencies)
  //
  void buildTree(const std::vector<int>& values, const std::vector<int>& weights);

  //
  // Print out a tree structure
  // The rule is:
  // - If leaf-node: Output 1 followed by the node value
  // - If not leaf-node, output 0. Then encode both child nodes in the same way
  //
  void printTree() const;
  void printTree(Node* node) const;

  //
  // Get the minimum depth of leaf nodes. The depth is defined as number
  // of edges from the root to the current node.
  //
  int minDepth() const;
  int minDepth(Node* node) const;

  //
  // Get the maximum depth of leaf nodes. The depth is defined as number
  // of edges from the root to the current node.
  //
  int maxDepth() const;
  int maxDepth(Node* node) const;
};


#endif //HUFFMAN_CODING_HUFFMAN_H
