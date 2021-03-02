#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}