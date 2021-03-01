#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"
#include "binary_tree.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Test*List.*";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}