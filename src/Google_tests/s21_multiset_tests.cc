#include <iostream>
#include <set>

#include "../s21_multiset.h"
#include "gtest/gtest.h"

namespace s21Multiset {
namespace tests {

class s21MultisetTests : public ::testing::Test {
 protected:
};

template <typename key_type>
bool compare_multiset(s21::multiset<key_type> my_multiset,
                      std::multiset<key_type> std_multiset) {
  bool res = true;
  auto i2 = my_multiset.begin();
  for (auto i1 = std_multiset.begin(); i1 != std_multiset.end(); ++i1, ++i2) {
    if ((*i1) != (*i2)) res = false;
  }
  return res;
}

TEST(MultisetTests, SConstructor) {
  s21::multiset<char> a;
  a.insert('a');
  s21::multiset<std::string> b;
  b.insert("sdfsdf");
  b.clear();
}

TEST(MultisetTests, InitialConstructor) {
  s21::multiset<char> a;
  a.insert('a');
  s21::multiset<std::string> b;
  b.insert("sdfsdf");
  s21::multiset<int> c({8, 4, 6});
  s21::multiset<int> d({8,  4,  6,  54, 65, 76,  43,  23,  56,  45,
                        98, 21, 49, -3, -5, -23, -34, -21, -56, -20});
}

TEST(MultisetTests, Find) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  auto it = a.find("aaa");
  ASSERT_EQ("aaa", *it);
  auto it2 = a.find("b");
}

TEST(MultisetTests, CopyConstructor) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  s21::multiset<std::string> b(a);
  ASSERT_EQ("aaa", *b.find("aaa"));
  ASSERT_EQ("aaa", *a.find("aaa"));
  ASSERT_EQ("bbb", *b.find("bbb"));
}

TEST(MultisetTests, MoveConstructor) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  s21::multiset<std::string> b(std::move(a));
  ASSERT_EQ("aaa", *b.find("aaa"));
  ASSERT_EQ(false, a.contains("aaa"));
  ASSERT_EQ("bbb", *b.find("bbb"));
}

TEST(MultisetTests, IteratorCompare) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  s21::multiset<std::string> b(a);
  auto it1 = a.begin();
  auto it2 = a.begin();
  ASSERT_EQ(true, it1 == it2);
  auto it3 = b.begin();
  ASSERT_EQ(false, it1 == it3);
}

TEST(MultisetTests, Contains) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("eee");
  ASSERT_EQ(true, a.contains("aaa"));
  ASSERT_EQ(false, a.contains("hhh"));
  ASSERT_EQ(true, a.contains("bbb"));
  ASSERT_EQ(true, a.contains("eee"));
}

TEST(MultisetTests, IteratorInsert) {
  s21::multiset<std::string> a;
  auto pair = a.insert("aaa");
  auto pair1 = a.insert("bbb");
  auto pair2 = a.insert("ccc");
  auto pair3 = a.insert("eee");
  ASSERT_EQ("aaa", *pair);
  ASSERT_EQ(false, a.contains("hhh"));
  ASSERT_EQ(true, a.contains("bbb"));
  ASSERT_EQ(true, a.contains("eee"));
}

TEST(MultisetTests, Swap) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("ddd");
  s21::multiset<std::string> b;
  b.insert("eee");
  b.insert("fff");
  b.insert("ggg");
  b.insert("hhh");
  a.swap(b);
  ASSERT_EQ(false, a.contains("aaa"));
  ASSERT_EQ(true, b.contains("aaa"));
  ASSERT_EQ(true, b.contains("ddd"));
}

TEST(MultisetTests, Erase) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("ddd");
  auto it = a.find("ccc");
  a.erase(it);
  a.erase(a.begin());
  ASSERT_EQ(false, a.contains("aaa"));
  ASSERT_EQ(false, a.contains("ccc"));
  ASSERT_EQ(true, a.contains("bbb"));
  ASSERT_EQ(true, a.contains("ddd"));
}

TEST(MultisetTests, Merge) {
  s21::multiset<int> a;
  a.insert(3);
  a.insert(6);
  a.insert(4);
  a.insert(5);
  s21::multiset<int> b;
  b.insert(2);
  b.insert(7);
  b.insert(8);
  b.insert(1);
  a.merge(b);
  a.contains(7);
  ASSERT_EQ(true, a.contains(7));
  ASSERT_EQ(true, a.contains(3));
}

TEST(MultisetTests, Merge2) {
  s21::multiset<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("ddd");
  s21::multiset<std::string> b;
  b.insert("eee");
  b.insert("fff");
  b.insert("ccc");
  b.insert("ggg");
  a.merge(b);
  ASSERT_EQ(false, b.contains("ccc"));
  ASSERT_EQ(true, a.contains("eee"));
  ASSERT_EQ(true, a.contains("aaa"));
}

TEST(MultisetTests, DefaultConstructor1) {
  s21::multiset<int> a;
  ASSERT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
}

TEST(MultisetTests, DefaultConstructor2) {
  s21::multiset<char> a;
  ASSERT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
}

TEST(MultisetTests, Constructor2) {
  s21::multiset<int> a{1, 2, 3, 4};
  std::multiset<int> b{1, 2, 3, 4};
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), 4);
}

TEST(MultisetTests, Insert) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.insert(21);
  b.insert(21);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, CopyConstructor2) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  auto a1 = a;
  auto b1 = b;
  b.operator=(b1);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(MultisetTests, MoveConstructor1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  auto a1 = std::move(a);
  auto b1 = std::move(b);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(MultisetTests, OperatorCopy) {
  s21::multiset<char> a = {
      'b',
      'c',
  };
  s21::multiset<char> a1 = {'b', 'c', 'd', 'a'};
  std::multiset<char> b = {
      'b',
      'c',
  };
  std::multiset<char> b1 = {'b', 'c', 'd', 'a'};
  a = a1;
  b = b1;
  EXPECT_TRUE(compare_multiset(a1, b1));
}

TEST(MultisetTests, OperatorMove) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  s21::multiset<int> a1;
  a1 = std::move(a);
  std::multiset<int> b1;
  b1 = std::move(b);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(MultisetTests, Begin1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  auto a1 = a.begin();
  auto b1 = b.begin();
  EXPECT_EQ((*a1), (*b1));
}

//  TODO

TEST(MultisetTests, Begin2Erase) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  auto a1 = a.begin();
  auto b1 = b.begin();
  a.erase(a1);
  b.erase(b1);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, End2) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};

  auto it1 = a.begin();
  auto it2 = a.end();
  auto it3 = b.begin();
  for (; it1 != it2; ++it1) {
    EXPECT_EQ(*it1, *it3);
    it3++;
  }
}

TEST(MultisetTests, Empty1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  EXPECT_FALSE(a.empty());
}

TEST(MultisetTests, Empty2) {
  s21::multiset<int> a;
  EXPECT_TRUE(a.empty());
}

TEST(MultisetTests, Empty3) {
  s21::multiset<int> a = {9, 10, 123, -4};
  a.clear();
  EXPECT_TRUE(a.empty());
}

TEST(MultisetTests, Size1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Size2) {
  s21::multiset<int> a;
  std::multiset<int> b;
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Clear0) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Insert1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  // EXPECT_EQ(a.insert(3).second, b.insert(3).second);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Insert2) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  // EXPECT_EQ(a.insert(9).second, b.insert(9).second);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Insert3) {
  s21::multiset<int> a;
  std::multiset<int> b;
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Insert4) {
  s21::multiset<int> a = {9, 10, 123, -4, 5, 5, 5, 5, 5};
  std::multiset<int> b = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  a.insert(9);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}
TEST(MultisetTests, Insert5) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4, 1};
  a.insert(1);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Insert6) {
  s21::multiset<int> a;
  std::multiset<int> b = {9};
  a.insert(9);
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
}
TEST(MultisetTests, Clear1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Clear2) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
}

//  TODO
TEST(MultisetTests, Erase1) {
  s21::multiset<int> a = {9, 9, 9, 9, 9, 10, 123, 45, 76};
  std::multiset<int> b = {9, 9, 9, 9, 9, 10, 123, 45, 76};
  auto it_a = a.begin();
  a.erase(it_a);
  auto it_b = b.begin();
  b.erase(it_b);
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTests, Swap1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  s21::multiset<int> a1;
  std::multiset<int> b1;
  a1.swap(a);
  b1.swap(b);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
}

TEST(MultisetTests, Swap2) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  s21::multiset<int> a1 = {1, 2, 3, 4, 5};
  std::multiset<int> b1 = {1, 2, 3, 4, 5};
  a1.swap(a);
  b1.swap(b);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MultisetTests, Swap3) {
  s21::multiset<int> a;
  std::multiset<int> b;
  s21::multiset<int> a1;
  std::multiset<int> b1;
  a1.swap(a);
  b1.swap(b);
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
}

TEST(MultisetTests, Merge1) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  s21::multiset<int> a1 = {1, 2, 3, 4, 5};
  std::multiset<int> b1 = {1, 2, 3, 4, 5};
  b1.merge(b);
  a1.merge(a);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MultisetTests, Merge3) {
  s21::multiset<int> a = {9, 10, 123, -4};
  std::multiset<int> b = {9, 10, 123, -4};
  s21::multiset<int> a1;
  std::multiset<int> b1;
  a1.merge(a);
  b1.merge(b);
  EXPECT_TRUE(compare_multiset(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MultisetTests, Contains1) {
  s21::multiset<int> a{1, 2, 3, 4, 5};
  EXPECT_TRUE(a.contains(1));
}

TEST(MultisetTests, Contains2) {
  s21::multiset<int> a{1, 2, 3, 4, 5};
  EXPECT_FALSE(a.contains(6));
}

TEST(MultisetTests, Find1) {
  s21::multiset<int> a{1, 2, 3, 4, 5};
  std::multiset<int> b{1, 2, 3, 4, 5};
  auto a1 = a.find(2);
  auto b1 = b.find(2);
  EXPECT_TRUE((*a1) == (*b1));
}

TEST(MultisetTests, Find2) {
  s21::multiset<int> a{1, 2, 3, 4, 5};
  auto a1 = a.find(6);
  auto A2 = a.end();
  EXPECT_TRUE(a1 == A2);
}

TEST(MultisetTests, MaxSize) {
  s21::multiset<int> a{9, 9, 7, 4};
  std::multiset<int> b{9, 9, 7, 4};

  EXPECT_TRUE(a.max_size() > b.max_size());

  s21::multiset<int> a1;
  std::multiset<int> b1;

  EXPECT_TRUE(a1.max_size() > b1.max_size());
}

TEST(MultisetTests, Count) {
  s21::multiset<int> a = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  std::multiset<int> b = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  EXPECT_TRUE(compare_multiset(a, b));
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.count(5), b.count(5));
}

TEST(MultisetTests, Lowerbound) {
  s21::multiset<int> a = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  std::multiset<int> b = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  EXPECT_EQ(*a.lower_bound(5), *b.lower_bound(5));
}

TEST(MultisetTests, Upperbound) {
  s21::multiset<int> a = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  std::multiset<int> b = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  EXPECT_EQ(*a.upper_bound(5), *b.upper_bound(5));
}

TEST(MultisetTests, EqualRange) {
  s21::multiset<int> a = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  std::multiset<int> b = {9, 9, 10, 123, -4, 5, 5, 5, 5, 5};
  EXPECT_EQ(*a.equal_range(5).first, *b.equal_range(5).first);
}

}  // namespace tests
}  // namespace s21Multiset
