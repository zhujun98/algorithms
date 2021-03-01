#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "linked_list.hpp"
#include "binary_tree.hpp"

#include "001.hpp"
#include "002.hpp"
#include "003.hpp"
#include "005.hpp"
#include "006.hpp"
#include "007.hpp"
#include "008.hpp"
#include "009.hpp"
#include "011.hpp"
#include "012.hpp"
#include "013.hpp"
#include "014.hpp"
#include "015.hpp"
#include "018.hpp"
#include "019.hpp"
#include "020.hpp"
#include "022.hpp"
#include "024.hpp"
#include "027.hpp"
#include "029.hpp"
#include "031.hpp"
#include "048.hpp"
#include "050.hpp"
#include "058.hpp"
#include "062.hpp"
#include "063.hpp"
#include "066.hpp"
#include "067.hpp"
#include "069.hpp"
#include "071.hpp"
#include "083.hpp"
#include "086.hpp"

using ::testing::UnorderedElementsAre;
using ::testing::ElementsAre;


TEST(Test001, GeneralTest) {
  EXPECT_THAT(twoSum({3, 2, 4}, 6), UnorderedElementsAre(1, 2));
  EXPECT_THAT(twoSum({2, 7, 11, 15}, 9), UnorderedElementsAre(0, 1));
  EXPECT_THAT(twoSum2Passes({3, 2, 4}, 6), UnorderedElementsAre(1, 2));
  EXPECT_THAT(twoSum2Passes({2, 7, 11, 15}, 9), UnorderedElementsAre(0, 1));
}

TEST(Test002, GeneralTest) {
  using list = LinkedList<int>;
  
  auto l0a = list({2, 4, 3});
  auto l0b = list({5, 6, 4});
  auto head0 = addTwoNumbers(l0a.head(), l0b.head());
  EXPECT_THAT(listToVector<int>(head0), ElementsAre(7, 0, 8));
  free_list(head0);
  
  auto l1a = list({2, 4, 6});
  auto l1b = list({5, 6, 4});
  auto head1 = addTwoNumbers(l1a.head(), l1b.head());
  EXPECT_THAT(listToVector<int>(head1), ElementsAre(7, 0, 1, 1));
  free_list(head1);

  auto l2a = list({});
  auto l2b = list({});
  auto head2 = addTwoNumbers(l2a.head(), l2b.head());
  EXPECT_THAT(listToVector<int>(head2), ElementsAre());
  free_list(head2);
}

TEST(Test003, GeneralTest) {
  EXPECT_EQ(lengthOfLongestSubstring(""), 0);
  EXPECT_EQ(lengthOfLongestSubstring("*"), 1);
  EXPECT_EQ(lengthOfLongestSubstring("abcabcbb"), 3);
  EXPECT_EQ(lengthOfLongestSubstring("bbbb"), 1);
  EXPECT_EQ(lengthOfLongestSubstring("pwwkew"), 3);

  EXPECT_EQ(lengthOfLongestSubstringASCII(""), 0);
  EXPECT_EQ(lengthOfLongestSubstringASCII("*"), 1);
  EXPECT_EQ(lengthOfLongestSubstringASCII("abcabcbb"), 3);
  EXPECT_EQ(lengthOfLongestSubstringASCII("bbbb"), 1);
  EXPECT_EQ(lengthOfLongestSubstringASCII("pwwkew"), 3);
}

TEST(Test005, GeneralTest) {
  EXPECT_EQ(longestPalindrome({""}), "");
  EXPECT_EQ(longestPalindrome({"a"}), "a");
  EXPECT_EQ(longestPalindrome({"abbd"}), "bb");
  EXPECT_EQ(longestPalindrome({"abebd"}), "beb");
  EXPECT_EQ(longestPalindrome({"adbbb"}), "bbb");
  EXPECT_EQ(longestPalindrome({"aaddaa"}), "aaddaa");
}

TEST(Test006, GeneralTest) {
  EXPECT_EQ(convert("PAYPALISHIRING", 3), "PAHNAPLSIIGYIR");
  EXPECT_EQ(convert("A", 1), "A");
  EXPECT_EQ(convert("AB", 1), "AB");
  EXPECT_EQ(convert("ABCDE", 2), "ACEBD");
}

TEST(Test007, GeneralTest) {
  EXPECT_EQ(reverse(123), 321);
  EXPECT_EQ(reverse(-123), -321);
  EXPECT_EQ(reverse(1534236469), 0);
  EXPECT_EQ(reverse(-1534236469), 0);
}

TEST(Test008, GeneralTest) {
  EXPECT_EQ(myAtoi(""), 0);
  EXPECT_EQ(myAtoi("23"), 23);
  EXPECT_EQ(myAtoi("    922337203685477580"), 2147483647);
  EXPECT_EQ(myAtoi("-9922337203685477580  "), -2147483648);
  EXPECT_EQ(myAtoi("words and 987"), 0);
  EXPECT_EQ(myAtoi("-4193 words on"), -4193);
}

TEST(Test009, GenralTest) {
  EXPECT_TRUE(isPalindrome(1));
  EXPECT_FALSE(isPalindrome(10));
  EXPECT_FALSE(isPalindrome(2147483647));
  EXPECT_FALSE(isPalindrome(-1234));
  EXPECT_TRUE(isPalindrome(12321));
  EXPECT_TRUE(isPalindrome(1221));
}

TEST(Test011, GeneralTest) {
  EXPECT_EQ(maxArea({1, 1}), 1);
  EXPECT_EQ(maxArea({1, 2, 3, 1, 6, 2, 6}), 12);
}

TEST(Test012, GeneralTest) {
  EXPECT_EQ(intToRoman(0), "");
  EXPECT_EQ(intToRoman(10), "X");
  EXPECT_EQ(intToRoman(34), "XXXIV");
  EXPECT_EQ(intToRoman(2544), "MMDXLIV");
}

TEST(Test013, GeneralTest) {
  EXPECT_EQ(romanToInt(""), 0);
  EXPECT_EQ(romanToInt("X"), 10);
  EXPECT_EQ(romanToInt("IVXL"), 34); // not standard Roman number
  EXPECT_EQ(romanToInt("XXXIV"), 34);
  EXPECT_EQ(romanToInt("MCLMIXDV"), 2544); // not standard Roman number
  EXPECT_EQ(romanToInt("MMDXLIV"), 2544);

  EXPECT_THROW(romanToInt("ABC"), std::out_of_range);
}

TEST(Test014, GeneralTest) {
  std::vector<std::string> input1 {""};
  EXPECT_EQ(longestCommonPrefix(input1), "");

  std::vector<std::string> input2 {"aa", "a", "aaa"};
  EXPECT_EQ(longestCommonPrefix(input2), "a");
}

TEST(Test015, GeneralTest) {
  std::vector<int> input0;
  EXPECT_THAT(threeSum(input0, 0), UnorderedElementsAre());

  std::vector<int> input1 {-1, 0, 1, 2, -1, -4};
  EXPECT_THAT(threeSum(input1, 0), UnorderedElementsAre(
  UnorderedElementsAre(-1, 0, 1),
  UnorderedElementsAre(-1, -1, 2)));

  std::vector<int> input2 {2, -1, -5, 0, -1, -1, -1};
  EXPECT_THAT(threeSum(input2, 5), UnorderedElementsAre());
}

TEST(Test018, GeneralTest) {
  std::vector<int> input0;
  EXPECT_THAT(fourSum(input0, 0), UnorderedElementsAre());

  std::vector<int> input1 {1, 0, -1, 0, -2, 2};
  EXPECT_THAT(fourSum(input1, 0), UnorderedElementsAre(
    UnorderedElementsAre(-2, -1, 1, 2),
    UnorderedElementsAre(-2,  0, 0, 2),
    UnorderedElementsAre(-1, 0, 0, 1)
  ));

  std::vector<int> input2 {2, -1, -5, 0, -1, -1, -1};
  EXPECT_THAT(fourSum(input2, 5), UnorderedElementsAre());

  std::vector<int> input3 {-3, -1, 0, 2, 4, 5};
  EXPECT_THAT(fourSum(input3, 1), UnorderedElementsAre(UnorderedElementsAre(-3, -1, 0, 5))
  );

  std::vector<int> input4 {-3, -2, -1, 0, 0, 1, 2, 3};
  EXPECT_THAT(fourSum(input4, 0), UnorderedElementsAre(
    UnorderedElementsAre(-3, -2, 2, 3),
    UnorderedElementsAre(-3, 0, 0, 3),
    UnorderedElementsAre(-3, 0, 1, 2),
    UnorderedElementsAre(-3, -1, 1, 3),
    UnorderedElementsAre(-2, -1, 0, 3),
    UnorderedElementsAre(-2, -1, 1, 2),
    UnorderedElementsAre(-2, 0, 0, 2),
    UnorderedElementsAre(-1, 0, 0, 1))
  );
}

TEST(Test019, GeneralTest) {
  using list = LinkedList<int>;

  list l0 {0, 1, 2, 3, 4};
  auto head0 = removeNthFromEnd(l0.head(), 1);
  EXPECT_THAT(listToVector(head0), ElementsAre(0, 1, 2, 3));

  list l1 {0, 1, 2, 3};
  auto head1 = removeNthFromEnd(l1.head(), 0);
  EXPECT_THAT(listToVector(head1), ElementsAre(0, 1, 2, 3));

  list l2 {0, 1, 2, 3};
  auto head2 = removeNthFromEnd(l2.head(), 4);
  EXPECT_THAT(listToVector(head2), ElementsAre(1, 2, 3));
}

TEST(Test020, GeneralTest) {
  EXPECT_TRUE(isValid("()"));
  EXPECT_TRUE(isValid("()[]{}"));
  EXPECT_FALSE(isValid("(]"));
  EXPECT_FALSE(isValid("([)]"));
  EXPECT_TRUE(isValid("{[]}"));
}

TEST(Test022, GeneralTest) {
  EXPECT_THAT(generateParenthesis(0), ElementsAre(""));
  EXPECT_THAT(generateParenthesis(1), ElementsAre("()"));
  EXPECT_THAT(generateParenthesis(2), UnorderedElementsAre("()()", "(())"));
  EXPECT_THAT(generateParenthesis(3),
    UnorderedElementsAre("()()()","()(())","(())()","(()())","((()))"));
}

TEST(Test024, GeneralTest) {
  LinkedList<int> l0;
  auto head0 = swapPairs(l0.head());
  EXPECT_THAT(listToVector(head0), ElementsAre());
  free_list(head0);
  l0.nullify();

  LinkedList<int> l1 {1};
  auto head1 = swapPairs(l1.head());
  EXPECT_THAT(listToVector(head1), ElementsAre(1));
  free_list(head1);
  l1.nullify();

  LinkedList<int> l2 {1, 2};
  auto head2 = swapPairs(l2.head());
  EXPECT_THAT(listToVector(head2), ElementsAre(2, 1));
  free_list(head2);
  l2.nullify();

  LinkedList<int> l3 {1, 2, 3};
  auto head3 = swapPairs(l3.head());
  EXPECT_THAT(listToVector(head3), ElementsAre(2, 1, 3));
  free_list(head3);
  l3.nullify();

  LinkedList<int> l4 {1, 2, 3, 4};
  auto head4 = swapPairs(l4.head());
  EXPECT_THAT(listToVector(head4), ElementsAre(2, 1, 4, 3));
  free_list(head4);
  l4.nullify();
}

TEST(Test027, GeneralTest) {
  std::vector<int> nums0 {3, 2, 2, 3};
  EXPECT_EQ(removeElement(nums0, 3), 2);
  EXPECT_EQ(removeElement1(nums0, 3), 2);
  std::vector<int> nums1;
  EXPECT_EQ(removeElement(nums1, 3), 0);
  EXPECT_EQ(removeElement1(nums1, 3), 0);
  std::vector<int> nums2 {2};
  EXPECT_EQ(removeElement(nums2, 3), 1);
  EXPECT_EQ(removeElement1(nums2, 3), 1);
  std::vector<int> nums3 {3};
  EXPECT_EQ(removeElement(nums3, 3), 0);
  EXPECT_EQ(removeElement1(nums3, 3), 0);
}

TEST(Test029, GeneralTest) {
  EXPECT_EQ(divide(0, 0), std::numeric_limits<int>::max());
  EXPECT_EQ(divide(-1, 1), -1);
  EXPECT_EQ(divide(1, -1), -1);
  EXPECT_EQ(divide(111, 5), 22);
  EXPECT_EQ(divide(111, 222), 0);
  EXPECT_EQ(divide(-pow(2, 31), 2), -pow(2, 30));
  EXPECT_EQ(divide(-pow(2, 31), -1), std::numeric_limits<int>::max());
}

TEST(Test031, GeneralTest) {
  EXPECT_THAT(nextPermutation({}), ElementsAre());
  EXPECT_THAT(nextPermutation({2}), ElementsAre(2));
  EXPECT_THAT(nextPermutation({5, 1, 1}), ElementsAre(1, 1, 5));
  EXPECT_THAT(nextPermutation({1, 5, 8, 4, 7, 6, 5, 3, 1}),
      ElementsAre(1, 5, 8, 5, 1, 3, 4, 6, 7));
}

TEST(Test048, GeneralTest) {
  std::vector<std::vector<int>> matrix = {{1, 2, 3, 4},
                                          {5, 6, 7, 8},
                                          {9, 10, 11, 12},
                                          {13, 14, 15, 16}};
  rotate(matrix);
  ASSERT_THAT(matrix, ElementsAre(ElementsAre(13, 9, 5, 1),
                                  ElementsAre(14, 10, 6, 2),
                                  ElementsAre(15, 11, 7, 3),
                                  ElementsAre(16, 12, 8, 4)));
}

TEST(Test050, GeneralTest) {
  EXPECT_EQ(myPow(2.0, -2147483648), 0.0);
  EXPECT_EQ(myPow(0.0, 0.0), 1.0);
  EXPECT_EQ(myPow(3.0, 3), 27);
  EXPECT_EQ(myPow(3.0, 4), 81);

  EXPECT_EQ(myPowRecursive(2.0, -2147483648), 0.0);
  EXPECT_EQ(myPowRecursive(0.0, 0.0), 1.0);
  EXPECT_EQ(myPowRecursive(3.0, 3), 27);
  EXPECT_EQ(myPowRecursive(3.0, 4), 81);
}

TEST(Test058, GeneralTest) {
  EXPECT_EQ(lengthOfLastWord(""), 0);
  EXPECT_EQ(lengthOfLastWord("   "), 0);
  EXPECT_EQ(lengthOfLastWord("Hello world"), 5);
  EXPECT_EQ(lengthOfLastWord("Hello w     "), 1);
}

TEST(Test062, GeneralTest) {
  EXPECT_EQ(uniquePaths(2, 1), 1);
  EXPECT_EQ(uniquePaths(2, 2), 2);
  EXPECT_EQ(uniquePaths(5, 10), 715);
  EXPECT_EQ(uniquePaths(10, 5), 715);
}

TEST(Test063, GeneralTest) {
  using T = std::vector<std::vector<int>>;

  T grid1 {{1}};
  EXPECT_EQ(uniquePathsWithObstacles(grid1), 0);
  T grid2 {{0}};
  EXPECT_EQ(uniquePathsWithObstacles(grid2), 1);
  T grid3 {{0}, {0}};
  EXPECT_EQ(uniquePathsWithObstacles(grid3), 1);
  T grid4 {{0, 0}};
  EXPECT_EQ(uniquePathsWithObstacles(grid4), 1);
  T grid5 {{0, 0}, {0, 1}};
  EXPECT_EQ(uniquePathsWithObstacles(grid5), 0);
  T grid6 {{1, 0, 0}, {0, 1, 0}};
  EXPECT_EQ(uniquePathsWithObstacles(grid6), 0);
  T grid7 {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}};
  EXPECT_EQ(uniquePathsWithObstacles(grid7), 4);
}

TEST(Test066, GeneralTest) {
  EXPECT_THAT(plusOne(std::vector<int>{1, 0}), ElementsAre(1, 1));
  EXPECT_THAT(plusOne(std::vector<int>{9, 9}), ElementsAre(1, 0, 0));
}

TEST(Test067, GeneralTest) {
  EXPECT_EQ(addBinary("0", "0"), "0");
  EXPECT_EQ(addBinary("1", "11"), "100");
  EXPECT_EQ(addBinary("1111", "1111"), "11110");
}

TEST(Test069, TestBinarySearchImplementation) {
  EXPECT_EQ(mySqrt(0), 0);
  EXPECT_EQ(mySqrt(5), 2);
  EXPECT_EQ(mySqrt(21), 4);
  EXPECT_EQ(mySqrt(2147483647), 46340);
}

TEST(Test069, TestNewtonImplementation) {
  EXPECT_EQ(mySqrtNewton(0), 0);
  EXPECT_EQ(mySqrtNewton(5), 2);
  EXPECT_EQ(mySqrtNewton(21), 4);
  EXPECT_EQ(mySqrtNewton(2147483647), 46340);
}

TEST(Test071, TestSimplifyPath) {
//  EXPECT_EQ("/name", simplifyPath("/name/"));
  EXPECT_EQ("/", simplifyPath("/../"));
  EXPECT_EQ("/home/foo", simplifyPath("/home//foo/"));
  EXPECT_EQ("/c", simplifyPath("/a/./b/../../c/"));
  EXPECT_EQ("/a/b/c", simplifyPath("/a//b////c/d//././/.."));
  EXPECT_EQ("/c", simplifyPath("/a/../../b/../c//.//"));
}

TEST(Test083, GeneralTest) {
  LinkedList<int> l0;
  auto head0 = deleteDuplicates(l0.head());
  EXPECT_THAT(listToVector(head0), ElementsAre());

  LinkedList<int> l1 {1, 1, 2};
  auto head1 = deleteDuplicates(l1.head());
  EXPECT_THAT(listToVector(head1), ElementsAre(1, 2));

  LinkedList<int> l2 {1, 1, 2, 3, 3};
  auto head2 = deleteDuplicates(l2.head());
  EXPECT_THAT(listToVector(head2), ElementsAre(1, 2, 3));
}

TEST(Test086, GeneralTest) {
  LinkedList<int> l0 {};
  auto head0 = partition(l0.head(), 3);
  EXPECT_THAT(listToVector(head0), ElementsAre());
  free_list(head0);
  l0.nullify();
  
  LinkedList<int> l1 {1, 4, 3, 2, 5, 2};
  auto head1 = partition(l1.head(), 3);
  EXPECT_THAT(listToVector(head1), ElementsAre(1, 2, 2, 4, 3, 5));
  free_list(head1);
  l1.nullify();
  
  LinkedList<int> l2 {5, 4, 3, 2, 5, 2};
  auto head2 = partition(l2.head(), 5);
  EXPECT_THAT(listToVector(head2), ElementsAre(4, 3, 2, 2, 5, 5));
  free_list(head2);
  l2.nullify();
}

int main(int argc, char **argv) {
//  ::testing::GTEST_FLAG(filter) = "Test*List.*";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}