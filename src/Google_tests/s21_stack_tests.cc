#include <iostream>

#include "../s21_stack.h"
#include "gtest/gtest.h"

TEST(StackTest, stack) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  EXPECT_EQ(k.empty(), false);
}

TEST(StackTest, stackMove) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  s21::stack<int> l(std::move(k));
  s21::stack<int> q;
  EXPECT_EQ(q.empty(), true);
}

TEST(StackTest, stackSwap) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  s21::stack<int> l(std::move(k));
  s21::stack<int> q;
  q = std::move(l);
  s21::stack<int> m;
  m.swap(q);
  EXPECT_EQ(m.size(), 4);
}

TEST(StackTest, stackPushPop) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  s21::stack<int> l(std::move(k));
  s21::stack<int> q;
  q = std::move(l);
  s21::stack<int> m;
  m.swap(q);
  m.push(5);
  m.insert_many_front(6);
  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(m.top(), i);
    m.pop();
  }
}
