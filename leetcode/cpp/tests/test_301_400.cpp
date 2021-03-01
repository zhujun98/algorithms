#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"
#include "binary_tree.hpp"

#include "344.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


TEST(Test344, Generaltest) {
  EXPECT_EQ(reverseString(""), "");
  EXPECT_EQ(reverseString("abc"), "cba");
}


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Test*List.*";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}