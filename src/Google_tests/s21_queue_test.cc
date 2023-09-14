#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

template <typename value_type1, typename value_type2>
bool compare_queues(s21::queue<value_type1> my_queue,
                    std::queue<value_type2> std_queue) {
  bool res = (my_queue.size() == std_queue.size());
  while (!my_queue.empty() && !std_queue.empty()) {
    if (my_queue.front() != std_queue.front()) res = false;
    my_queue.pop();
    std_queue.pop();
  }
  return res;
}

TEST(queue, test_1) {
  s21::queue<int> A;
  ASSERT_TRUE(A.empty());
  ASSERT_EQ(A.size(), 0);
}

TEST(queue, test_2) {
  s21::queue<int> A{1, 2, 3, 4};
  std::queue<int> B;
  for (int i = 1; i < 5; ++i) B.push(i);
  EXPECT_TRUE(compare_queues(A, B));
}

TEST(queue, test_3) {
  s21::queue<char> A{'a', 'b', 'c'};
  std::queue<char> B;
  for (char i = 'b'; i < 'g'; ++i) B.push(i);
  EXPECT_FALSE(compare_queues(A, B));
}

TEST(queue, test_4) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  std::queue<char> D(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_5) {
  const s21::queue<char> A{'a', 'b', 'c'};
  const s21::queue<char> B(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_6) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B(std::move(A));
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D(std::move(C));
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_7) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = A;
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D = C;
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_8) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = A;
  std::queue<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::queue<int> D = C;
  EXPECT_FALSE(compare_queues(B, D));
}

TEST(queue, test_9) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = std::move(A);
  std::queue<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::queue<int> D = std::move(C);
  EXPECT_FALSE(compare_queues(B, D));
}

TEST(queue, test_10) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = std::move(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D = std::move(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_11) {
  s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('a', A.front());
}

TEST(queue, test_12) {
  const s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('a', A.front());
}

TEST(queue, test_13) {
  s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.back());
}
TEST(queue, test_14) {
  const s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.back());
}

TEST(queue, test_16) {
  const s21::queue<int> A{6, 7, 8, 9, 78};
  EXPECT_EQ(5, A.size());
}

TEST(queue, test_17) {
  s21::queue<int> A{6, 7, 8, 9, 78};
  A.push(std::move(187));
  EXPECT_EQ(187, A.back());
}

TEST(queue, test_18) {
  s21::queue<int> A{6, 7, 8, 9, 78};
  A.pop();
  EXPECT_EQ(7, A.front());
}
TEST(queue, test_15) {
  s21::queue<char> A{'a', 'd', 'g'};
  s21::queue<char> B{'c', 'g', 'y'};
  std::queue<char> C;
  C.push('a');
  C.push('d');
  C.push('g');
  std::queue<char> D;
  D.push('c');
  D.push('g');
  D.push('y');
  A.swap(B);
  C.swap(D);
  EXPECT_TRUE(compare_queues(B, D));
  EXPECT_TRUE(compare_queues(A, C));
}

TEST(queue, func_insert_many_back_1) {
  std::queue<int> A;
  for (char i = 1; i < 9; ++i) A.push(i);
  s21::queue<int> B{1, 2, 3, 4, 5};

  B.insert_many_back(6, 7, 8);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_queues(B, A));
}

TEST(stack, func_insert_many_back_2) {
  std::queue<char> A;
  for (char i = 'a'; i < 'd'; ++i) A.push(i);
  s21::queue<char> B;

  B.insert_many_back('a', 'b', 'c');

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_queues(B, A));
}