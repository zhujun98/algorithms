//
// Created by jun on 9/12/17.
//
#include <iostream>

#define BOOST_TEST_MODULE test_macro_overview
#include <boost/test/included/unit_test.hpp>

#include "../bst.h"


/**
 *                  (6, 3)
 *             /             \
 *        (2, 1)              (8, 2)
 *       /      \            /      \
 *   (1, 3)    (3, 6)    (7, 1)    (9, 2)
 *                 \
 *                  (5, 8)
 *
 */
BOOST_AUTO_TEST_CASE(test_macro_overview)
{
  auto tree = bst<int, int>();

  tree.insert(std::make_pair(6, 3));
  tree.insert(std::make_pair(2, 1));
  tree.insert(std::make_pair(3, 6));
  tree.insert(std::make_pair(8, 2));
  tree.insert(std::make_pair(1, 3));
  tree.insert(std::make_pair(7, 1));
  tree.insert(std::make_pair(5, 8));
  tree.insert(std::make_pair(9, 2));

  BOOST_TEST(tree.min().first == std::make_pair(1, 3).first);
  BOOST_TEST(tree.max().first == std::make_pair(9, 2).first);

  BOOST_TEST(tree.find(8).second == 2);
  BOOST_TEST(tree.find(2).second == 1);

  BOOST_TEST(tree.predecessor(7).first == 6);
  BOOST_TEST(tree.predecessor(6).first == 5);
  BOOST_TEST(tree.successor(6).first == 7);
  BOOST_TEST(tree.successor(5).first == 6);

  tree.erase(5);
  BOOST_TEST(tree.predecessor(6).first == 3);
  tree.erase(6);
  BOOST_TEST(tree.getRoot()->key == 7);
  BOOST_TEST(tree.getRoot()->value == 1);
}