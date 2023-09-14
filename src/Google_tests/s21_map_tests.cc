#include <iostream>
#include <map>

#include "../s21_map.h"
#include "gtest/gtest.h"

template <typename key_type, typename value_type>
bool compare_map(s21::map<key_type, value_type> my_map,
                 std::map<key_type, value_type> std_map) {
  bool res = true;
  auto i2 = my_map.begin();
  for (auto i1 = std_map.begin(); i1 != std_map.end(); ++i1, ++i2) {
    if ((*i1).first != (*i2).first || (*i1).second != (*i2).second) res = false;
  }
  return res;
}

TEST(MapTest, DefaultConstructor1) {
  s21::map<int, int> a;
  ASSERT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
}

TEST(MapTest, DefaultConstructor2) {
  s21::map<char, int> a;
  ASSERT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
}

TEST(MapTest, ListInit) {
  s21::map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> b{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_TRUE(compare_map(a, b));
  auto it = a.begin();
  EXPECT_EQ(a.size(), 4);
}

TEST(MapTest, Insert) {
  s21::map<int, int> a;
  std::map<int, int> b;
  a.insert({21, 21});
  b.insert({21, 21});
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto a1 = a;
  auto b1 = b;
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto a1 = std::move(a);
  auto b1 = std::move(b);
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(MapTest, OperatorCopy) {
  s21::map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  s21::map<int, int> a1{{1, 1}, {2, 2}, {3, 3},  {4, 4},
                        {8, 4}, {9, 5}, {10, 6}, {-1, 0}};
  std::map<int, int> b{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> b1{{1, 1}, {2, 2}, {3, 3},  {4, 4},
                        {8, 4}, {9, 5}, {10, 6}, {-1, 0}};
  a = a1;
  b = b1;
  EXPECT_TRUE(compare_map(a1, b1));
}

TEST(MapTest, MoveOperator) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  s21::map<int, int> a1;
  a1 = std::move(a);
  std::map<int, int> b1;
  b1 = std::move(b);
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(MapTest, At1) {
  s21::map<int, int> a = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::pair<const int, int> i(1, 1);
  EXPECT_EQ(a.at(1), 1);
  a.at(1) = 11;
  EXPECT_EQ(a.at(1), 11);
}

// TEST(MapTest, At2) {
//   s21::map<int, int> a = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std::map<int, int> b = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   EXPECT_ANY_THROW(a.at(21));
// }

// TEST(MapTest, At3) {
//   s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
//   std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
//   EXPECT_EQ(a[9], b[9]);
//   EXPECT_NO_THROW(a[5]);
//   EXPECT_NO_THROW(b[5]);
//   EXPECT_TRUE(compare_map(a, b));
// }

TEST(MapTest, Begin) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto a1 = a.begin();
  auto b1 = b.begin();
  EXPECT_EQ((*a1).second, (*b1).second);
}

TEST(MapTest, Empty1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_FALSE(a.empty());
}

TEST(MapTest, Empty2) {
  s21::map<int, int> a;
  EXPECT_TRUE(a.empty());
}

TEST(MapTest, Clear1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  a.clear();
  EXPECT_TRUE(a.empty());
}

TEST(MapTest, Clear2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, Clear3) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, Size1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, Size2) {
  s21::map<int, int> a;
  std::map<int, int> b;
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertPair1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(a.insert(pair).second, b.insert(pair).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertPair2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::pair<int, int> pair = {9, 1};
  EXPECT_EQ(a.insert(pair).second, b.insert(pair).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertPair3) {
  s21::map<int, int> a;
  std::map<int, int> b;
  std::pair<int, int> pair = {9, 1};
  EXPECT_EQ(a.insert(pair).second, b.insert(pair).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertOrAssign1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(a.insert_or_assign(1, 1).second, b.insert_or_assign(1, 1).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertOrAssign2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(a.insert_or_assign(9, 1).second, b.insert_or_assign(9, 1).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertOrAssign3) {
  s21::map<int, int> a;
  std::map<int, int> b;
  EXPECT_EQ(a.insert_or_assign(9, 1).second, b.insert_or_assign(9, 1).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertKeyObj1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_FALSE(a.insert(9, 1).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertKeyObj2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}, {1, 1}};
  EXPECT_TRUE(a.insert(1, 1).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, InsertKeyObj3) {
  s21::map<int, int> a;
  std::map<int, int> b = {{9, 1}};
  EXPECT_TRUE(a.insert(9, 1).second);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, Erase1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto a1 = a.begin();
  auto b1 = b.begin();
  a.erase(a1);
  b.erase(b1);
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, Erase2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  a.erase(a.end());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_TRUE(compare_map(a, b));
}

TEST(MapTest, Swap1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  s21::map<int, int> a1;
  std::map<int, int> b1;
  a1.swap(a);
  b1.swap(b);
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
}

TEST(MapTest, Swap2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> b1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  a1.swap(a);
  b1.swap(b);
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_TRUE(compare_map(a, b));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MapTest, Swap3) {
  s21::map<int, int> a;
  std::map<int, int> b;
  s21::map<int, int> a1;
  std::map<int, int> b1;
  a1.swap(a);
  b1.swap(b);
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
}

TEST(MapTest, Merge1) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  s21::map<int, int> a1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> b1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  a1.merge(a);
  b1.merge(b);
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MapTest, Merge2) {
  s21::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  s21::map<int, int> a1;
  std::map<int, int> b1;
  a1.merge(a);
  b1.merge(b);
  EXPECT_TRUE(compare_map(a1, b1));
  EXPECT_EQ(a1.size(), b1.size());
  EXPECT_EQ(a1.empty(), b1.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

//  TODO
TEST(MapTest, Contains1) {
  s21::map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_TRUE(a.contains(1));
  EXPECT_FALSE(a.contains(8));
}

TEST(MapTest, Contains2) {
  s21::map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_FALSE(a.contains(6));
}

TEST(MapTest, MaxSize) {
  s21::map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> b{{1, 1}, {2, 2}, {3, 3}, {4, 4}};

  EXPECT_TRUE(a.max_size() > b.max_size());

  std::map<int, int> a1;
  s21::map<int, int> b1;

  EXPECT_TRUE(a1.max_size() < b1.max_size());
}

TEST(MapTest, Move) {
  std::map<int, int> a = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> b = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  a = std::move(a);
  b = std::move(b);
}
