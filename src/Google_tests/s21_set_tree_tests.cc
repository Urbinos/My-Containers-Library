#include <iostream>
#include <set>

#include "../s21_binary_tree.h"
#include "../s21_set.h"
#include "gtest/gtest.h"

template <typename key_type>
bool compare_set(s21::set<key_type> my_set, std::set<key_type> std_set) {
  bool res = true;
  auto i2 = my_set.begin();
  for (auto i1 = std_set.begin(); i1 != std_set.end(); ++i1, ++i2) {
    if ((*i1) != (*i2)) res = false;
  }
  return res;
}

TEST(BinaryTreeTests, StandartConstructor) {
  s21::BinaryTree<std::string> b;
  s21::BinaryTree<std::string> a;
}

TEST(BinaryTreeTests, Insert) {
  s21::BinaryTree<int> a;
  a.insert(11);
  a.insert(15);
}

TEST(BinaryTreeTests, IteratorPlus) {
  s21::BinaryTree<int> a;
  a.insert(11);
  a.insert(15);
  auto it = a.begin();
  ++it;
  EXPECT_EQ(15, *it);
  const s21::BinaryTree<int> tree({98, 23, 56, 4, 15, 2, 9, 1});
  s21::BinaryTree<int>::const_iterator it2 = tree.begin();
  ++it2;
  EXPECT_EQ(2, *it2);
  it2++;
}

TEST(BinaryTreeTests, OperatorRavno) {
  s21::BinaryTree<int> a;
  a.insert(11);
  a.insert(15);
  s21::BinaryTree<int> b;
  b = a;
  ASSERT_EQ(true, b.contains(11));
  ASSERT_EQ(true, b.contains(15));
}

TEST(BinaryTreeTests, Search) {
  s21::BinaryTree<int> a;
  a.insert(72);
  a.insert(12);
  a.insert(45);
  a.insert(111112);
  ASSERT_EQ(72, *a.find(72));
  ASSERT_EQ(45, *a.find(45));
  s21::set<std::string> b;
  b.insert("aa1aa");
  b.insert("bb4bb");
  b.insert("cc3cc");
  b.insert("ee6ee");
  b.insert("vv2vv");
  ASSERT_EQ(true, b.contains("aa1aa"));
  ASSERT_EQ(true, b.contains("vv2vv"));
}

TEST(BinaryTreeTests, IteratorOperatorPointer) {
  s21::BinaryTree<int> a;
  a.insert(11);
  a.insert(15);
  s21::BinaryTree<int>::iterator it = a.begin();
  ASSERT_EQ(11, *it);
  it++;
  ASSERT_EQ(15, *it);
}

TEST(BinaryTreeTests, IteratorBegin) {
  s21::BinaryTree<int> a;
  a.insert(11);
  a.insert(15);
  s21::BinaryTree<int>::iterator it = a.begin();
  ASSERT_EQ(11, *it);
}

TEST(BinaryTreeTests, ConstIteratorBegin) {
  s21::BinaryTree<int> a;
  a.insert(11);
  a.insert(15);
  const s21::BinaryTree<int>::iterator it = a.begin();
  ASSERT_EQ(11, *it);
}

TEST(SetTest, SetConstructor) {
  s21::set<char> a;
  a.insert('a');
  s21::set<std::string> b;
  b.insert("sdfsdf");
  b.clear();
}

TEST(SetTest, InitialConstructor) {
  s21::set<char> a;
  a.insert('a');
  s21::set<std::string> b;
  b.insert("sdfsdf");
  s21::set<int> c({8, 4, 6});
  s21::set<int> d({8,  4,  6,  54, 65, 76,  43,  23,  56,  45,
                   98, 21, 49, -3, -5, -23, -34, -21, -56, -20});
}

TEST(SetTest, Find) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  auto it = a.find("aaa");
  ASSERT_EQ("aaa", *it);
  auto it2 = a.find("b");
}

TEST(SetTest, CopyConstructor) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  s21::set<std::string> b(a);
  ASSERT_EQ("aaa", *b.find("aaa"));
  ASSERT_EQ("aaa", *a.find("aaa"));
  ASSERT_EQ("bbb", *b.find("bbb"));
}

TEST(SetTest, MoveConstructor) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  s21::set<std::string> b(std::move(a));
  ASSERT_EQ("aaa", *b.find("aaa"));
  ASSERT_EQ(false, a.contains("aaa"));
  ASSERT_EQ("bbb", *b.find("bbb"));
}

TEST(SetTest, IteratorCompare) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  s21::set<std::string> b(a);
  auto it1 = a.begin();
  auto it2 = a.begin();
  ASSERT_EQ(true, it1 == it2);
  auto it3 = b.begin();
  ASSERT_EQ(false, it1 == it3);
}

TEST(SetTest, Contains) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("eee");
  ASSERT_EQ(true, a.contains("aaa"));
  ASSERT_EQ(false, a.contains("hhh"));
  ASSERT_EQ(true, a.contains("bbb"));
  ASSERT_EQ(true, a.contains("eee"));
}

TEST(SetTest, IteratorInsert) {
  s21::set<std::string> a;
  auto pair = a.insert("aaa");
  auto pair1 = a.insert("bbb");
  auto pair2 = a.insert("ccc");
  auto pair3 = a.insert("eee");
  ASSERT_EQ("aaa", *pair.first);
  ASSERT_EQ(false, a.contains("hhh"));
  ASSERT_EQ(true, a.contains("bbb"));
  ASSERT_EQ(true, a.contains("eee"));
}

TEST(SetTest, Swap) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("ddd");
  s21::set<std::string> b;
  b.insert("eee");
  b.insert("fff");
  b.insert("ggg");
  b.insert("hhh");
  a.swap(b);
  ASSERT_EQ(false, a.contains("aaa"));
  ASSERT_EQ(true, b.contains("aaa"));
  ASSERT_EQ(true, b.contains("ddd"));
}

TEST(SetTest, Erase) {
  s21::set<std::string> a;
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

TEST(SetTest, Merge) {
  s21::set<int> a;
  a.insert(3);
  a.insert(6);
  a.insert(4);
  a.insert(5);
  s21::set<int> b;
  b.insert(2);
  b.insert(7);
  b.insert(8);
  b.insert(1);
  a.merge(b);
  a.contains(7);
  ASSERT_EQ(true, a.contains(7));
  ASSERT_EQ(true, a.contains(3));
}

TEST(SetTest, Merge2) {
  s21::set<std::string> a;
  a.insert("aaa");
  a.insert("bbb");
  a.insert("ccc");
  a.insert("ddd");
  s21::set<std::string> b;
  b.insert("eee");
  b.insert("fff");
  b.insert("ccc");
  b.insert("ggg");
  a.merge(b);
  ASSERT_EQ(false, b.contains("ccc"));
  ASSERT_EQ(true, a.contains("eee"));
  ASSERT_EQ(true, a.contains("aaa"));
}

TEST(SetTest, DefaultConstructor1) {
  s21::set<int> a;
  ASSERT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
}

TEST(SetTest, DefaultConstructor2) {
  s21::set<char> a;
  ASSERT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
}

TEST(SetTest, Constructor2) {
  s21::set<int> a{1, 2, 3, 4};
  std::set<int> b{1, 2, 3, 4};
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), 4);
}

TEST(SetTest, Insert) {
  s21::set<int> a;
  std::set<int> b;
  a.insert(21);
  b.insert(21);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, CopyConstructor2) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  auto a1 = a;
  auto b1 = b;
  b.operator=(b1);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(SetTest, MoveConstructor1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  auto a1 = std::move(a);
  auto b1 = std::move(b);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(SetTest, OperatorCopy) {
  s21::set<char> a = {
      'b',
      'c',
  };
  s21::set<char> a1 = {'b', 'c', 'd', 'a'};
  std::set<char> b = {
      'b',
      'c',
  };
  std::set<char> b1 = {'b', 'c', 'd', 'a'};
  a = a1;
  b = b1;
  EXPECT_TRUE(compare_set(a1, b1));
}

TEST(SetTest, OperatorMove) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  s21::set<int> a1;
  a1 = std::move(a);
  std::set<int> b1;
  b1 = std::move(b);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(SetTest, Begin1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  auto a1 = a.begin();
  auto b1 = b.begin();
  EXPECT_EQ((*a1), (*b1));
}

//  TODO

TEST(SetTest, Begin2Erase) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  auto a1 = a.begin();
  auto b1 = b.begin();
  a.erase(a1);
  b.erase(b1);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, End2) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};

  auto it1 = a.begin();
  auto it2 = a.end();
  auto it3 = b.begin();
  for (; it1 != it2; ++it1) {
    EXPECT_EQ(*it1, *it3);
    it3++;
  }
}

TEST(SetTest, Empty1) {
  s21::set<int> a = {9, 10, 123, -4};
  EXPECT_FALSE(a.empty());
}

TEST(SetTest, Empty2) {
  s21::set<int> a;
  EXPECT_TRUE(a.empty());
}

TEST(SetTest, Empty3) {
  s21::set<int> a = {9, 10, 123, -4};
  a.clear();
  EXPECT_TRUE(a.empty());
}

TEST(SetTest, Size1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Size2) {
  s21::set<int> a;
  std::set<int> b;
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Clear0) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Insert1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  EXPECT_EQ(a.insert(3).second, b.insert(3).second);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Insert2) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  EXPECT_EQ(a.insert(9).second, b.insert(9).second);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Insert3) {
  s21::set<int> a;
  std::set<int> b;
  EXPECT_EQ(a.insert(9).second, b.insert(9).second);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Insert4) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  EXPECT_FALSE(a.insert(9).second);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}
TEST(SetTest, Insert5) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4, 1};
  EXPECT_TRUE(a.insert(1).second);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Insert6) {
  s21::set<int> a;
  std::set<int> b = {9};
  EXPECT_TRUE(a.insert(9).second);
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a.size(), b.size());
}
TEST(SetTest, Clear1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Clear2) {
  s21::set<int> a;
  std::set<int> b;
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Erase1) {
  s21::set<int> a = {9, 10, 123, -4, 45, 1, 76, 34, 57, 5, 3, -7};
  std::set<int> b = {9, 10, 123, -4, 45, 1, 76, 34, 57, 5, 3, -7};
  auto it = a.begin();
  a.erase(it);
  auto it2 = b.begin();
  b.erase(it2);
  EXPECT_EQ(a.size(), b.size());
  a.erase(a.begin());
  b.erase(b.begin());
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, Swap1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  s21::set<int> a1;
  std::set<int> b1;
  a1.swap(a);
  b1.swap(b);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
}

TEST(SetTest, Swap2) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  s21::set<int> a1 = {1, 2, 3, 4, 5};
  std::set<int> b1 = {1, 2, 3, 4, 5};
  a1.swap(a);
  b1.swap(b);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_TRUE(compare_set(a, b));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(SetTest, Swap3) {
  s21::set<int> a;
  std::set<int> b;
  s21::set<int> a1;
  std::set<int> b1;
  a1.swap(a);
  b1.swap(b);
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
}

TEST(SetTest, Merge1) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  s21::set<int> a1 = {1, 2, 3, 4, 5};
  std::set<int> b1 = {1, 2, 3, 4, 5};
  b1.merge(b);
  a1.merge(a);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(SetTest, Merge3) {
  s21::set<int> a = {9, 10, 123, -4};
  std::set<int> b = {9, 10, 123, -4};
  s21::set<int> a1;
  std::set<int> b1;
  a1.merge(a);
  b1.merge(b);
  EXPECT_TRUE(compare_set(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(SetTest, Contains1) {
  s21::set<int> a{1, 2, 3, 4, 5};
  EXPECT_TRUE(a.contains(1));
}

TEST(SetTest, Contains2) {
  s21::set<int> a{1, 2, 3, 4, 5};
  EXPECT_FALSE(a.contains(6));
}

TEST(SetTest, Find1) {
  s21::set<int> a{1, 2, 3, 4, 5};
  std::set<int> b{1, 2, 3, 4, 5};
  auto a1 = a.find(2);
  auto b1 = b.find(2);
  EXPECT_TRUE((*a1) == (*b1));
}

TEST(SetTest, Find2) {
  s21::set<int> a{1, 2, 3, 4, 5};
  auto a1 = a.find(6);
  auto A2 = a.end();
  EXPECT_TRUE(a1 == A2);
}

TEST(SetTest, MaxSize) {
  s21::set<int> a{9, 9, 7, 4};
  std::set<int> b{9, 9, 7, 4};

  EXPECT_TRUE(a.max_size() > b.max_size());

  s21::set<int> a1;
  std::set<int> b1;

  EXPECT_TRUE(a1.max_size() > b1.max_size());
}
