#include "../s21_list.h"

#include <gtest/gtest.h>

#include <list>

TEST(List, DefaultConstructor) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, ParamConstructor) {
  s21::list<int> s21_list(5);
  std::list<int> std_list(5);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, InitConstructor) {
  s21::list<int> s21_list = {1, 3, 5, 7};
  std::list<int> std_list = {1, 3, 5, 7};
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, CopyConstructor) {
  s21::list<int> s21_a = {1, 3, 5, 7};
  std::list<int> std_a = {1, 3, 5, 7};
  s21::list<int> s21_list(s21_a);
  std::list<int> std_list(std_a);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, MoveConstructor) {
  s21::list<int> s21_a = {1, 3, 5, 7};
  std::list<int> std_a = {1, 3, 5, 7};
  s21::list<int> s21_list(std::move(s21_a));
  std::list<int> std_list(std::move(std_a));
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());

  EXPECT_EQ(s21_a.size(), std_a.size());
  EXPECT_EQ(s21_a.empty(), std_a.empty());
}

TEST(list, front_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.front(), s21_list1.front());
}

TEST(list, back_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.back(), s21_list1.back());
}

TEST(list, begin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.begin(), *s21_list1.begin());
}

TEST(list, end_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.end()), *(s21_list1.last()));
}

TEST(list, empty_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.empty(), s21_list1.empty());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.empty(), s21_list2.empty());
}

TEST(list, size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, max_size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.max_size(), s21_list1.max_size());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.max_size(), s21_list2.max_size());
}

TEST(list, clear_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.clear();
  s21_list1.clear();

  EXPECT_EQ(std_list1.size(), s21_list1.size());
}

TEST(list, insert_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto std_pos = std_list1.insert(std_list1.begin(), 0);
  auto s21_pos = s21_list1.insert(s21_list1.begin(), 0);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(*std_pos, *s21_pos);

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_pos = std_list1.insert(--std_list1.end(), 0);
  s21_pos = s21_list1.insert(s21_list1.last(), 0);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(*std_pos, *s21_pos);

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, erase_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};
  std::list<int> std_list2 = {6};
  s21::list<int> s21_list2 = {6};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.erase(std_list1.begin());
  s21_list1.erase(s21_list1.begin());

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1.erase(--std_list1.end());
  s21_list1.erase(s21_list1.last());

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list2.erase(--std_list2.end());
  s21_list2.erase(s21_list2.last());

  EXPECT_EQ(std_list2.size(), s21_list2.size());

  s21_it = s21_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, push_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.push_back(6);
  s21_list1.push_back(6);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, pop_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.pop_back();
  s21_list1.pop_back();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, push_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.push_front(6);
  s21_list1.push_front(6);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, pop_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.pop_front();
  s21_list1.pop_front();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, swap_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  s21::list<int> s21_list2 = {5, 4, 3, 2, 1};

  std_list1.swap(std_list2);
  s21_list1.swap(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  EXPECT_EQ(*std_list1.begin(), *s21_list1.begin());
  EXPECT_EQ(*std_list2.begin(), *s21_list2.begin());
}

TEST(list, merge_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {9, 8, 7};
  s21::list<int> s21_list2 = {9, 8, 7};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {9, 8, 7};
  s21_list1 = {9, 8, 7};

  std_list2 = {1, 2, 3, 4, 5};
  s21_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {1, 2, 3, 4, 5};
  s21_list1 = {1, 2, 3, 4, 5};

  std_list2 = {1, 2, 3, 4, 5};
  s21_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  s21::list<int> s21_list;
  std::list<int> std_list;

  std_list.merge(std_list1);
  s21_list.merge(s21_list1);

  EXPECT_EQ(std_list.size(), s21_list.size());

  s21_it = s21_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, splice_function) {
  std::list<int> std_list1 = {1, 2, 3, 4};
  s21::list<int> s21_list1 = {1, 2, 3, 4};

  std::list<int> std_list2 = {9, 8, 7};
  s21::list<int> s21_list2 = {9, 8, 7};

  std_list1.splice(std_list1.end(), std_list2);
  s21_list1.splice(s21_list1.end(), s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list2.splice(std_list2.begin(), std_list1);
  s21_list2.splice(s21_list2.begin(), s21_list1);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, reverse_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std_list1.reverse();
  s21_list1.reverse();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, unique_function) {
  std::list<int> std_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};
  s21::list<int> s21_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};

  std_list1.unique();
  s21_list1.unique();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, sort_function) {
  std::list<int> std_list1 = {2, 7, 1, 3, 8, 2};
  s21::list<int> s21_list1 = {2, 7, 1, 3, 8, 2};

  std_list1.sort();
  s21_list1.sort();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {9, 8, 7, 6, 5};
  s21_list1 = {9, 8, 7, 6, 5};

  std_list1.sort();
  s21_list1.sort();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_function) {
  std::list<int> std_list1 = {1, 6, 7, 8, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  auto pos = s21_list1.insert_many(++s21_list1.begin(), 6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());
  EXPECT_EQ(2, *pos);

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {1, 6, 7, 8, 2, 3, 4, 0, 0, 0, 5};

  pos = s21_list1.insert_many(s21_list1.last(), 0, 0, 0);

  EXPECT_EQ(11, s21_list1.size());
  EXPECT_EQ(5, *pos);

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  s21_list1.insert_many_back(6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_front_function) {
  std::list<int> std_list1 = {6, 7, 8, 1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  s21_list1.insert_many_front(6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
