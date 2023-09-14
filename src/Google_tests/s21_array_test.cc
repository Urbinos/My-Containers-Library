#include <gtest/gtest.h>

#include <array>

#include "../s21_containers_plus.h"

TEST(array, defaullt_constructor) {
  std::array<int, 5> std_arr1;
  s21::array<int, 5> s21_arr1;
  EXPECT_EQ(std_arr1.size(), s21_arr1.size());

  std::array<int, 0> std_arr2;
  s21::array<int, 0> s21_arr2;
  EXPECT_EQ(std_arr2.size(), s21_arr2.size());
}

TEST(array, list_constructor) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  s21::array<int, 5> s21_arr1 = {1, 2, 3};
  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[i], s21_arr1[i]);

  std::array<int, 5> std_arr2 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_arr2 = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], s21_arr2[i]);

  std::array<int, 0> std_arr3 = {};
  s21::array<int, 0> s21_arr3 = {};
  EXPECT_EQ(std_arr3.size(), s21_arr3.size());
}

TEST(array, copy_constructor) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  s21::array<int, 5> s21_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2(std_arr1);
  s21::array<int, 5> s21_arr2(s21_arr1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], s21_arr2[i]);
}

TEST(array, move_constructor) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  s21::array<int, 5> s21_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2(std::move(std_arr1));
  s21::array<int, 5> s21_arr2(std::move(s21_arr1));

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], s21_arr2[i]);
}

TEST(array, copy_operator) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  s21::array<int, 5> s21_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2;
  s21::array<int, 5> s21_arr2;

  std_arr2 = std_arr1;
  s21_arr2 = s21_arr1;

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], s21_arr2[i]);
}

TEST(array, move_operator) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  s21::array<int, 5> s21_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2;
  s21::array<int, 5> s21_arr2;

  std_arr2 = std::move(std_arr1);
  s21_arr2 = std::move(s21_arr1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], s21_arr2[i]);
  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[i], s21_arr1[i]);
}

TEST(array, at_function) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  s21::array<int, 5> s21_arr1 = {1, 2, 3};

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1.at(i), s21_arr1.at(i));
}

TEST(array, bracket_operator) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[i], s21_arr1[i]);
}

TEST(array, front_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.front(), s21_arr1.front());
}

TEST(array, back_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.back(), s21_arr1.back());
}

TEST(array, data_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.data(), &std_arr1[0]);
  EXPECT_EQ(s21_arr1.data(), &s21_arr1[0]);
}

TEST(array, begin_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.begin(), &std_arr1[0]);
  EXPECT_EQ(s21_arr1.begin(), &s21_arr1[0]);
}

TEST(array, const_begin_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.cbegin(), &std_arr1[0]);
  EXPECT_EQ(s21_arr1.const_begin(), &s21_arr1[0]);
}

TEST(array, end_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.end(), &std_arr1[5]);
  EXPECT_EQ(s21_arr1.end(), &s21_arr1[5]);
}

TEST(array, const_end_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.cend(), &std_arr1[5]);
  EXPECT_EQ(s21_arr1.const_end(), &s21_arr1[5]);
}

TEST(array, empty_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};
  EXPECT_EQ(std_arr1.empty(), s21_arr1.empty());

  std::array<int, 0> std_arr2;
  s21::array<int, 0> s21_arr2;
  EXPECT_EQ(std_arr2.empty(), s21_arr2.empty());
}

TEST(array, size_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};
  EXPECT_EQ(std_arr1.size(), s21_arr1.size());

  std::array<int, 0> std_arr2;
  s21::array<int, 0> s21_arr2;
  EXPECT_EQ(std_arr2.size(), s21_arr2.size());
}

TEST(array, max_size_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};
  EXPECT_EQ(std_arr1.max_size(), s21_arr1.max_size());

  std::array<int, 0> std_arr2;
  s21::array<int, 0> s21_arr2;
  EXPECT_EQ(std_arr2.max_size(), s21_arr2.max_size());
}

TEST(array, swap_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  std::array<int, 5> std_arr2 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_arr2 = {1, 2, 3, 4, 5};

  std_arr1.swap(std_arr2);
  s21_arr1.swap(s21_arr2);

  EXPECT_EQ(std_arr1[0], s21_arr1[0]);
  EXPECT_EQ(std_arr2[0], s21_arr2[0]);
}

TEST(array, fill_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> s21_arr1 = {5, 4, 3, 2, 1};

  std_arr1.fill(10);
  s21_arr1.fill(10);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[0], s21_arr1[0]);
}