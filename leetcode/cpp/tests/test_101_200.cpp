#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "121.hpp"
#include "125.hpp"
#include "127.hpp"
#include "155.hpp"
#include "160.hpp"
#include "168.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


TEST(Test121, GeneralTest) {
  std::vector<int> prices0 {7, 1, 5, 3, 6, 4};
  EXPECT_EQ(maxProfit(prices0), 5);
  std::vector<int> prices1 {7, 6, 4, 3, 1};
  EXPECT_EQ(maxProfit(prices1), 0);
  std::vector<int> prices2;
  EXPECT_EQ(maxProfit(prices2), 0);
  std::vector<int> prices3 {1};
  EXPECT_EQ(maxProfit(prices3), 0);
}

TEST(Test125, GeneralTest) {
  EXPECT_TRUE(isPalindrome(""));
  EXPECT_TRUE(isPalindrome("*"));
  EXPECT_TRUE(isPalindrome(".,"));
  EXPECT_FALSE(isPalindrome("hello world!"));
  EXPECT_TRUE(isPalindrome("(hell,o ol@leh."));
}

TEST(Test155, GeneralTest) {
  MinStack ms;
  EXPECT_THROW(ms.top(), std::out_of_range);
  ms.push(2);
  EXPECT_EQ(ms.top(), 2);
  EXPECT_EQ(ms.getMin(), 2);
  ms.push(-3);
  EXPECT_EQ(ms.top(), -3);
  EXPECT_EQ(ms.getMin(), -3);
  ms.push(2);
  EXPECT_EQ(ms.top(), 2);
  EXPECT_EQ(ms.getMin(), -3);
  ms.pop();
  EXPECT_EQ(ms.top(), -3);
  EXPECT_EQ(ms.getMin(), -3);
  ms.pop();
  EXPECT_EQ(ms.top(), 2);
  EXPECT_EQ(ms.getMin(), 2);
}

TEST(Test160, TestGetIntersectionNode) {

}

TEST(Test168, TestGeneral) {
  ASSERT_EQ("AB", convertToTitle(28));
  ASSERT_EQ("A", convertToTitle(1));
  ASSERT_EQ("AAA", convertToTitle(26*27 + 1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}