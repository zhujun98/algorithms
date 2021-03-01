#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"
#include "binary_tree.hpp"

#include "557.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


TEST(Test557, GeneralTest) {
  EXPECT_EQ(reverseWordsIII(""), "");
  EXPECT_EQ(reverseWordsIII("abc"), "cba");
  EXPECT_EQ(reverseWordsIII("abc ed /&"), "cba de &/");
}


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Test*List.*";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}