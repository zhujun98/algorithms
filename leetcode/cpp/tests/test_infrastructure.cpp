#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"
#include "binary_tree.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


TEST(TestBareLinkedList, GeneralTest) {
  auto l0 = LinkedList<int>({2, 4, 3});
  ASSERT_THAT(listToVector<int>(l0.head()), ElementsAre(2, 4, 3));

  auto l1 = LinkedList<int>({});
  ASSERT_THAT(listToVector<int>(l1.head()), ElementsAre());
}

//TEST(TestLinkedList, GeneralTest) {
//  ASSERT_EQ(std::is_trivial<LinkedList>::value, false);
//  ASSERT_EQ(std::is_standard_layout<LinkedList>::value, false);
//  ASSERT_EQ(std::is_pod<LinkedList>::value, false);
//
//  LinkedList l0 {0, 6, 2};
//  ASSERT_THAT(l0.getElements(), ElementsAre(0, 6, 2));
//  LinkedList l1;
//  ASSERT_THAT(l1.getElements(), ElementsAre());
//
//  // test copy constructor
//  LinkedList l2(l0);
//  ASSERT_THAT(l2.head()->val, 0);
//  ASSERT_THAT(l2.tail()->val, 2);
//  ASSERT_THAT(l2.getElements(), ElementsAre(0, 6, 2));
//  l0.pushBack(5);  // test modify l0 will not affect l2
//  ASSERT_THAT(l0.getElements(), ElementsAre(0, 6, 2, 5));
//  ASSERT_THAT(l2.getElements(), ElementsAre(0, 6, 2));
//
//  LinkedList l3(l1);
//  ASSERT_TRUE(l3.head() == nullptr);
//  ASSERT_TRUE(l3.tail() == nullptr);
//  ASSERT_THAT(l3.getElements(), ElementsAre());
//
//  // test move constructor
//  LinkedList l4(std::move(l2));
//  ASSERT_TRUE(l2.head() == nullptr);
//  ASSERT_TRUE(l2.tail() == nullptr);
//
//  ASSERT_THAT(l4.head()->val, 0);
//  ASSERT_THAT(l4.tail()->val, 2);
//  ASSERT_THAT(l4.getElements(), ElementsAre(0, 6, 2));
//
//  // test nthNode member function
//  ASSERT_EQ(l3.nthNode(0), nullptr);
//  ASSERT_EQ(l4.nthNode(0)->val, 0);
//  ASSERT_EQ(l4.nthNode(1)->val, 6);
//  ASSERT_EQ(l4.nthNode(2)->val, 2);
//  ASSERT_EQ(l4.nthNode(100), nullptr);
//}


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Test*List.*";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
