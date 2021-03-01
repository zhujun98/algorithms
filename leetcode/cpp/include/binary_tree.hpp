//
// Created by jun on 12/22/17.
//

#ifndef LEECODE_BINARY_TREE_H
#define LEECODE_BINARY_TREE_H

#include <iostream>
#include <memory>


struct TreeNode {
  int val;
  std::unique_ptr<TreeNode> left;
  std::unique_ptr<TreeNode> right;

  explicit TreeNode(int x) : val(x) {}
};


class BinaryTree {

  std::unique_ptr<TreeNode> root_;

public:
  BinaryTree() = default;

  BinaryTree(std::initializer_list<int> init_list) {}

  ~BinaryTree() {}
};

#endif //LEECODE_BINARY_TREE_H
