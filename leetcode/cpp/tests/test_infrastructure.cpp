#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"


using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;
using ListType = LinkedList<int>;

TEST(TestLinkedList, TestCtor) {
  ListType l1 {0, 6, 2};
  ASSERT_THAT(l1.head()->val, 0);
  ASSERT_THAT(l1.toVector(), ElementsAre(0, 6, 2));
  ListType l2;
  ASSERT_THAT(l2.toVector(), ElementsAre());
}

TEST(TestLinkedList, TestCopyCTor)
{
  ListType l1 {0, 6, 2};
  ListType l1c(l1);
  ASSERT_THAT(l1c.toVector(), ElementsAre(0, 6, 2));
  l1.addItem(5);  // test modify l0 will not affect l2
  ASSERT_THAT(l1.toVector(), ElementsAre(0, 6, 2, 5));
  ASSERT_THAT(l1c.toVector(), ElementsAre(0, 6, 2));

  ListType l2;
  ListType l2c(l2);
  ASSERT_TRUE(l2c.head() == nullptr);
}

TEST(TestLinkedList, TestCopyAssignmentCTor) {
  ListType l1 {0, 6, 2};

  l1 = l1; // self assignment
  ASSERT_THAT(l1.toVector(), ElementsAre(0, 6, 2));

  ListType l1c;
  l1c = l1;
  ASSERT_THAT(l1c.toVector(), ElementsAre(0, 6, 2));
  l1.addItem(5);  // test modify l0 will not affect l2
  ASSERT_THAT(l1.toVector(), ElementsAre(0, 6, 2, 5));
  ASSERT_THAT(l1c.toVector(), ElementsAre(0, 6, 2));

  ListType l2;
  ListType l2c;
  l2c = l2;
  ASSERT_TRUE(l2c.head() == nullptr);
}

TEST(TestLinkedList, TestMoveCTor) {
  ListType l1 {0, 6, 2};
  ListType l1m(std::move(l1));
  ASSERT_TRUE(l1.head() == nullptr);
  ASSERT_THAT(l1m.toVector(), ElementsAre(0, 6, 2));
}

TEST(TestLinkedList, TestMoveAssignmentCTor) {
  ListType l1 {0, 6, 2};
  ListType l1m {1, 2, 3};
  l1m = std::move(l1);
  ASSERT_TRUE(l1.head() == nullptr);
  ASSERT_THAT(l1m.toVector(), ElementsAre(0, 6, 2));
}

TEST(TestLinkedList, TestAddItem) {
  ListType l1;
  l1.addItem(3);
  ASSERT_THAT(l1.toVector(), ElementsAre(3));
  l1.addItem(13);
  ASSERT_THAT(l1.toVector(), ElementsAre(3, 13));
}

TEST(TestLinkedList, TestNthNode) {
  ListType l1;
  ASSERT_EQ(l1.nthNode(0), nullptr);
  EXPECT_THROW(l1.nthNode(1), std::out_of_range);

  ListType l2 {0, 6, 2};
  ASSERT_EQ(l2.nthNode(0)->val, 0);
  ASSERT_EQ(l2.nthNode(1)->val, 6);
  ASSERT_EQ(l2.nthNode(2)->val, 2);
  EXPECT_THROW(l2.nthNode(100), std::out_of_range);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
