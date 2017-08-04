//
// Created by jun on 8/3/17.
//
#include <iostream>
#include <queue>
#include <assert.h>

#include "Huffman.h"


Huffman::Huffman() {}

Huffman::~Huffman() {
  destroyTree(root_);
}

// comparator for ranking nodes
bool compareNode(const Node* a, const Node* b) {
  return ( a->frequency > b->frequency );
}

void Huffman::buildTree(const std::vector<int>& values, const std::vector<int>& weights) {
  assert(values.size() == weights.size());

  // build a minimum priority queue
  std::priority_queue<Node*, std::vector<Node*>, decltype(&compareNode)> huff_tree(compareNode);

  for ( auto i = 0; i < values.size(); ++i) {
    Node* new_node = newNode(values[i], weights[i]);
    huff_tree.push(new_node);
  }

  while ( huff_tree.size() > 1 ) {
    // pop the first two nodes
    Node* left_node = huff_tree.top();
    huff_tree.pop();
    Node* right_node = huff_tree.top();
    huff_tree.pop();

    // make a new node with the frequency being the sum of the deleted two
    // Here we assume -1 is not a value of data
    Node* new_node = newNode(-1, left_node->frequency + right_node->frequency);
    new_node->left = left_node;
    new_node->right = right_node;

    huff_tree.push(new_node);
  }

  root_ = huff_tree.top();
}

void Huffman::destroyTree(Node* node) {
  if ( node != nullptr ) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete [] node;
  }
}

void Huffman::printTree() const {
  printTree(root_);
  std::cout << std::endl;

  std::cout << "The minimum depth is: " << minDepth() << std::endl;
  std::cout << "The maximum depth is: " << maxDepth() << std::endl;
}

void Huffman::printTree(Node* node) const {
  if ( node != nullptr ) {
    if ( node->left == nullptr && node->right == nullptr ) {
      std::cout << 1 << "(" << node->value << ")";
    } else {
      std::cout << 0;

      printTree(node->left);
      printTree(node->right);
    }
  }
}

int Huffman::minDepth() const { minDepth(root_); }

int Huffman::minDepth(Node* node) const {
  if ( node == nullptr ) { return 0; }

  if ( node->left == nullptr || node->right == nullptr ) {
    return 1;
  } else {
    int depth_left = minDepth(node->left);
    int depth_right = minDepth(node->right);

    if ( depth_left > depth_right ) {
      return depth_right + 1;
    } else {
      return depth_left + 1;
    }
  }
}

int Huffman::maxDepth() const { maxDepth(root_); }

int Huffman::maxDepth(Node* node) const {
  if ( node == nullptr ) { return 0; }

  if ( node->left == nullptr && node->right == nullptr ) {
    return 1;
  } else if ( node->left == nullptr ) {
    return maxDepth(node->right) + 1;
  } if ( node->right == nullptr ) {
    return maxDepth(node->left) + 1;
  } else {
    int depth_left = maxDepth(node->left);
    int depth_right = maxDepth(node->right);

    if ( depth_left < depth_right ) {
      return depth_right + 1;
    } else {
      return depth_left + 1;
    }
  }
}
