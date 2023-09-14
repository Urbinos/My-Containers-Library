#ifndef CONTAINERS_SRC_S21_SET_H_
#define CONTAINERS_SRC_S21_SET_H_

#include <cmath>
#include <iostream>
#include <memory>

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set : public BinaryTree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key>::iterator;
  using const_iterator = typename BinaryTree<Key>::const_iterator;
  using size_type = size_t;

  set() {}
  set(std::initializer_list<key_type> const &items)
      : BinaryTree<key_type>::BinaryTree(items) {}
  set(const set &s) : BinaryTree<key_type>::BinaryTree(s) {}
  set(set &&s) noexcept { *this = std::move(s); }
  ~set() {}

  set &operator=(const set &other) {
    if (this == &other) {
      return *this;
    }
    this->clear();
    this->CopyTree(other.root_);
    return *this;
  }

  set &operator=(set &&s) noexcept {
    this->root_ = s.root_;
    s.root_ = nullptr;
    this->size_ = s.size_;
    this->allocator_ = s.allocator_;
    return *this;
  }
};  // class set
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_SET_H_
