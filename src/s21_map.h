#ifndef CONTAINERS_SRC_S21_MAP_H_
#define CONTAINERS_SRC_S21_MAP_H_

#include <cmath>
#include <functional>

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class T, class Compare>
class MyComparator {
 public:
  bool operator()(const std::pair<const Key, T> &lhs,
                  const std::pair<const Key, T> &rhs) const {
    return Compare()(lhs.first, rhs.first);
  }
};

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map : public BinaryTree<std::pair<const Key, T>,
                              MyComparator<Key, T, Compare>, Allocator> {
 public:
  using key_type = Key;
  using Comp = s21::MyComparator<key_type, T, Compare>;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename s21::BinaryTree<value_type, Comp, Allocator>::iterator;
  using const_iterator =
      typename s21::BinaryTree<value_type, Comp, Allocator>::const_iterator;
  using size_type =
      typename s21::BinaryTree<value_type, Comp, Allocator>::size_type;
  using BTree = typename s21::BinaryTree<value_type, Comp, Allocator>;
  using node_pointer_type =
      typename s21::BinaryTree<value_type, Comp, Allocator>::Node *;
  map() {}
  map(std::initializer_list<value_type> const &items) {
    try {
      for (auto it = items.begin(); it != items.end(); it++) {
        this->insert(*it);
      }
    } catch (...) {
      this->clear();
      throw;
    }
  }
  map(const map &m) : BTree(m) {}
  map(map &&other) noexcept : BTree(std::move(other)) {}
  ~map() = default;

  mapped_type &at(const key_type &key) {
    node_pointer_type search = SearchMap(key);
    if (search == nullptr) {
      throw std::out_of_range("Fail");
    }
    return search->key.second;
  }

  mapped_type &operator[](const Key &key) {
    node_pointer_type search = SearchMap(key);
    node_pointer_type ins{};
    if (search == nullptr) {
      mapped_type val{};
      BTree::root_ =
          BTree::InsertIt(BTree::root_, std::make_pair(key, val), &ins);
      if (ins == nullptr) {
        throw std::out_of_range("out_of_range");
      }
      return ins->key.second;
    }
    return search->key.second;
  }

  map &operator=(const map &other) {
    if (this == &other) {
      return *this;
    }
    this->clear();
    this->CopyTree(other.root_);
    return *this;
  }

  map &operator=(map &&s) noexcept {
    if (this != &s) {
      this->root_ = s.root_;
      s.root_ = nullptr;
      this->size_ = s.size_;
      this->allocator_ = s.allocator_;
    }
    return *this;
  }

  bool contains(const Key &key) { return (SearchMap(key) != nullptr); }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    node_pointer_type search = SearchMap(key);
    if (search == nullptr) return BTree::insert(std::make_pair(key, obj));
    search->key.second = obj;
    iterator it(search);
    return std::make_pair(it, false);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return BTree::insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return BTree::insert(value);
  }

 private:
  bool LessMap(Key a, Key b, Compare cmp = Compare{}) { return cmp(a, b); }
  node_pointer_type SearchMap(const key_type &key) {
    return SearchMap(BTree::root_, key);
  }

  node_pointer_type SearchMap(node_pointer_type node, const key_type &key) {
    if (node == nullptr) return nullptr;
    //  node->key == key
    if (!LessMap(key, (node->key).first) && !LessMap((node->key).first, key))
      return node;
    //  key < node->key
    return (LessMap(key, (node->key).first) ? SearchMap(node->left, key)
                                            : SearchMap(node->right, key));
  }
};
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_MAP_H_
