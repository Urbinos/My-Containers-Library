#ifndef CONTAINERS_SRC_QUEUE_H_
#define CONTAINERS_SRC_QUEUE_H_

#include <algorithm>

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;

 public:
  queue() : container() {}
  explicit queue(std::initializer_list<value_type> const& other)
      : container(other){};
  queue(const queue& other) : container(other.container){};
  queue(queue&& other) : container(std::move(other.container)){};
  ~queue() {}

  queue& operator=(const queue& other) {
    *this = other;
    return *this;
  }

  queue& operator=(queue&& other) {
    container = std::move(other.container);
    std::swap(container);
    return *this;
  }

  reference front() { return container.front(); }
  const_reference front() const { return container.front(); }
  reference back() { return container.back(); }
  const_reference back() const { return container.back(); }

  bool empty() const { return container.empty(); }
  size_type size() const { return container.size(); }

  void push(const T& value) { container.push_back(value); }
  void push(T&& value) { container.push_back(std::move(value)); }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    container.insert_many_back(std::forward<Args>(args)...);
  }

  void pop() { container.pop_front(); }
  void swap(queue& other) { std::swap(container, other.container); }

  template <typename T1, typename T2>
  bool operator==(queue<T2>& rhs) {
    return equal(rhs);
  }

 private:
  Container container;
};
}  // namespace s21

#endif  // CONTAINERS_SRC_QUEUE_H_
