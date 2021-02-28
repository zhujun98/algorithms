//
// Created by jun on 9/12/17.
//
#include <iostream>

#include "bst.h"


int main()
{
  auto tree = bst<int, int>();

  tree.insert(std::make_pair(2, 1));
  tree.insert(std::make_pair(3, 6));
  tree.insert(std::make_pair(6, 3));
  tree.insert(std::make_pair(4, 2));
  tree.insert(std::make_pair(1, 9));

  tree.inorderTreeWalk();

  tree.erase(9);

  tree.inorderTreeWalk();
}
