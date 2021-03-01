#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"
#include "binary_tree.hpp"

#include "234.hpp"
#include "237.hpp"
#include "268.hpp"
#include "283.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


//TEST(Test234, GeneralTest) {
//  LinkedList l0;
//  EXPECT_TRUE(isPalindromeStack(l0.head()));
//  LinkedList234 ll0;
//  EXPECT_TRUE(ll0.isPalindrome());
//
//  LinkedList l1 {1, 2};
//  EXPECT_FALSE(isPalindromeStack(l1.head()));
//  LinkedList234 ll1 {1, 2};
//  EXPECT_FALSE(ll1.isPalindrome());
//
//  LinkedList l2 {1, 2, 3, 2, 1};
//  EXPECT_TRUE(isPalindromeStack(l2.head()));
//  LinkedList234 ll2 {1, 2, 3, 2, 1};
//  EXPECT_TRUE(ll2.isPalindrome());
//  // Test that the linked list has been recovered after reverse.
//  EXPECT_THAT(ll2.getElements(), ElementsAre(1, 2, 3, 2, 1));
//
//  LinkedList l3 {1, 2, 2, 1};
//  EXPECT_TRUE(isPalindromeStack(l3.head()));
//  LinkedList234 ll3 {1, 2, 2, 1};
//  EXPECT_TRUE(ll3.isPalindrome());
//  EXPECT_THAT(ll3.getElements(), ElementsAre(1, 2, 2, 1));
//}

//TEST(Test237, GeneralTest) {
//  LinkedList l0 {0, 1, 2};
//  deleteNode(l0.nthNode(1));
//  EXPECT_THAT(l0.getElements(), ElementsAre(0, 2));
//
//  LinkedList l1 {0, 1, 2};
//  deleteNode(l1.nthNode(0));
//  EXPECT_THAT(l1.getElements(), ElementsAre(1, 2));
//}

TEST(Test268, GeneralTest) {
  std::vector<int> nums0 {3, 0, 1};
  EXPECT_EQ(missingNumber(nums0), 2);

  std::vector<int> nums1 {1};
  EXPECT_EQ(missingNumber(nums1), 0);

  std::vector<int> nums2 {9, 6, 4, 2, 3, 5, 7, 0, 1};
  EXPECT_EQ(missingNumber(nums2), 8);
}

TEST(Test283, GeneralTest) {
  std::vector<int> nums0 {0, 1, 0, 3, 12};
  moveZeroes(nums0);
  EXPECT_THAT(nums0, ElementsAre(1, 3, 12, 0, 0));

  std::vector<int> nums1 {0};
  moveZeroes(nums1);
  EXPECT_THAT(nums1, ElementsAre(0));

  std::vector<int> nums2 {1, 2};
  moveZeroes(nums2);
  EXPECT_THAT(nums2, ElementsAre(1, 2));
}


int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Test*List.*";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}