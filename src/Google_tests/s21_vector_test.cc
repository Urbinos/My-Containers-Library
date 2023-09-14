#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

TEST(vector, default_constructor) {
  std::vector<int> std_vector;
  s21::vector<int> s21_vector;

  EXPECT_EQ(std_vector.size(), s21_vector.size());
}

TEST(vector, parameterized_constructor) {
  std::vector<int> std_vector1(5);
  s21::vector<int> s21_vector1(5);

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());

  std::vector<int> std_vector2(0);
  s21::vector<int> s21_vector2(0);

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());
}

TEST(vector, list_constructor) {
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector.size(), s21_vector.size());
  EXPECT_EQ(std_vector.capacity(), s21_vector.capacity());

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector[i], s21_vector[i]);
}

TEST(vector, copy_constructor) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2(std_vector1);
  s21::vector<int> s21_vector2(s21_vector1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], s21_vector2[i]);

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());
}

TEST(vector, move_constructor) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2(std::move(std_vector1));
  s21::vector<int> s21_vector2(std::move(s21_vector1));

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], s21_vector2[i]);

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());
}

TEST(vector, copy_operator) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> s21_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std_vector2 = std_vector1;
  s21_vector2 = s21_vector1;

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], s21_vector2[i]);

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());

  std::vector<int> std_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> s21_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::vector<int> std_vector4 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector4 = {1, 2, 3, 4, 5};

  std_vector4 = std_vector3;
  s21_vector4 = s21_vector3;

  for (int i = 0; i < 9; ++i) EXPECT_EQ(std_vector4[i], s21_vector4[i]);

  EXPECT_EQ(std_vector4.size(), s21_vector4.size());
  EXPECT_EQ(std_vector4.capacity(), s21_vector4.capacity());
}

TEST(vector, move_operator) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> s21_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std_vector2 = std::move(std_vector1);
  s21_vector2 = std::move(s21_vector1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], s21_vector2[i]);

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());

  std::vector<int> std_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> s21_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::vector<int> std_vector4 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector4 = {1, 2, 3, 4, 5};

  std_vector4 = std::move(std_vector3);
  s21_vector4 = std::move(s21_vector3);

  for (int i = 0; i < 9; ++i) EXPECT_EQ(std_vector4[i], s21_vector4[i]);

  EXPECT_EQ(std_vector4.size(), s21_vector4.size());
  EXPECT_EQ(std_vector4.capacity(), s21_vector4.capacity());
}

TEST(vector, at_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1.at(i), s21_vector1.at(i));
  }
}

TEST(vector, brackets_operator) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }
}

TEST(vector, front_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.front(), s21_vector1.front());
}

TEST(vector, back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.back(), s21_vector1.back());
}

TEST(vector, data_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_TRUE(std_vector1.data() == &std_vector1.front());
  EXPECT_TRUE(s21_vector1.data() == &s21_vector1.front());
}

TEST(vector, begin_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*std_vector1.begin(), *s21_vector1.begin());
  EXPECT_EQ(*std_vector1.cbegin(), *s21_vector1.const_begin());
}

TEST(vector, end_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*(std_vector1.end() - 1), *(s21_vector1.end() - 1));
  EXPECT_EQ(*(std_vector1.cend() - 1), *(s21_vector1.const_end() - 1));
}

TEST(vector, empty_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.empty(), s21_vector1.empty());

  std::vector<int> std_vector2;
  s21::vector<int> s21_vector2;

  EXPECT_EQ(std_vector2.empty(), s21_vector2.empty());
}

TEST(vector, size_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());

  std::vector<int> std_vector2;
  s21::vector<int> s21_vector2;

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
}

TEST(vector, max_size_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.max_size(), s21_vector1.max_size());

  std::vector<int> std_vector2;
  s21::vector<int> s21_vector2;

  EXPECT_EQ(std_vector2.max_size(), s21_vector2.max_size());
}

TEST(vector, capacity_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());

  std::vector<int> std_vector2;
  s21::vector<int> s21_vector2;

  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());
}

TEST(vector, push_back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std_vector1.push_back(6);
  s21_vector1.push_back(6);

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
  EXPECT_EQ(std_vector1[5], s21_vector1[5]);
}

TEST(vector, pop_back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std_vector1.pop_back();
  s21_vector1.pop_back();

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
}

TEST(vector, shrink_to_fit_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std_vector1.pop_back();
  s21_vector1.pop_back();

  std_vector1.pop_back();
  s21_vector1.pop_back();

  std_vector1.shrink_to_fit();
  s21_vector1.shrink_to_fit();

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
}

TEST(vector, reserve_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std_vector1.reserve(10);
  s21_vector1.reserve(10);

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
}

TEST(vector, clear_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std_vector1.clear();
  s21_vector1.clear();

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
}

TEST(vector, insert_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std_vector1.insert(std_vector1.begin(), 6);
  s21_vector1.insert(s21_vector1.begin(), 6);

  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  auto std_pos = std_vector1.insert(std_vector1.begin() + 3, 7);
  auto s21_pos = s21_vector1.insert(s21_vector1.begin() + 3, 7);

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  EXPECT_EQ(*std_pos, *s21_pos);

  std_pos = std_vector1.insert(std_vector1.end(), 8);
  s21_pos = s21_vector1.insert(s21_vector1.end(), 8);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  EXPECT_EQ(*std_pos, *s21_pos);

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
}

TEST(vector, erase_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};

  std_vector1.erase(std_vector1.begin());
  s21_vector1.erase(s21_vector1.begin());

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  std_vector1.erase(std_vector1.begin() + 3);
  s21_vector1.erase(s21_vector1.begin() + 3);

  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  std_vector1.erase(std_vector1.end() - 1);
  s21_vector1.erase(s21_vector1.end() - 1);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());
}

TEST(vector, swap_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2 = {6, 7, 8, 9};
  s21::vector<int> s21_vector2 = {6, 7, 8, 9};

  std_vector2.swap(std_vector1);
  s21_vector2.swap(s21_vector1);

  EXPECT_EQ(std_vector1[0], s21_vector1[0]);
  EXPECT_EQ(std_vector2[0], s21_vector2[0]);

  EXPECT_EQ(std_vector1.size(), s21_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), s21_vector1.capacity());

  EXPECT_EQ(std_vector2.size(), s21_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), s21_vector2.capacity());
}

TEST(vector, insert_many_function) {
  std::vector<int> std_vector1 = {4, 5, 6, 7, 8};
  s21::vector<int> s21_vector1 = {4, 5};

  auto pos = s21_vector1.insert_many(s21_vector1.end(), 6, 7, 8);

  EXPECT_EQ(6, *pos);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  pos = s21_vector1.insert_many(s21_vector1.begin(), 1, 2, 3);

  EXPECT_EQ(1, *pos);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  std_vector1 = {1, 2, 3, 4, 5, 5, 5, 5, 6, 7, 8};
  pos = s21_vector1.insert_many(s21_vector1.begin() + 4, 5, 5, 5);

  EXPECT_EQ(5, *pos);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }
}

TEST(vector, insert_many_back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector1 = {1, 2, 3};

  s21_vector1.insert_many_back(4, 5);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }

  std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21_vector1.insert_many_back(6, 7, 8);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], s21_vector1[i]);
  }
}
