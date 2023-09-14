#ifndef CONTAINERS_SRC_S21_MULTISET_H_
#define CONTAINERS_SRC_S21_MULTISET_H_

#include <cmath>
#include <functional>

#include "s21_stack.h"
#include "s21_vector.h"

namespace s21 {
template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key>>
class multiset {
 public:
  class Node;
  class MultisetIterator;
  class ConstMultisetIterator;
  using iterator = MultisetIterator;
  using const_iterator = ConstMultisetIterator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using allocator_type =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
  class Node {
   public:
    Key key{};
    Node *left{};
    Node *right{};
    Node(Key key) : key(key) {}
  };  //  Class Node

  class MultisetIterator {
    friend class multiset;

   public:
    using value_type = Key;
    using pointer = value_type *;
    using reference = value_type &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    MultisetIterator(Node *node) : current_node_(node) {
      while (current_node_ != nullptr) {
        nodeStack.push(current_node_);
        current_node_ = current_node_->left;
      }

      if (!nodeStack.empty()) {
        current_node_ = nodeStack.top();
        nodeStack.pop();
      }
    }
    reference operator*() const { return current_node_->key; }
    pointer operator->() const { return &(current_node_->key); }
    bool operator==(const iterator &other) const {
      return (other.current_node_ == current_node_);
    }

    bool operator!=(const iterator &other) const {
      return !(current_node_ == other.current_node_);
    }

    iterator &operator++() {
      if (current_node_->right != nullptr) {
        Node *temp = current_node_->right;
        while (temp != nullptr) {
          nodeStack.push(temp);
          temp = temp->left;
        }
      }
      if (!nodeStack.empty()) {
        current_node_ = nodeStack.top();
        nodeStack.pop();
      } else {
        current_node_ = nullptr;
      }
      return *this;
    }
    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

   private:
    Node *current_node_;
    s21::stack<Node *> nodeStack;

  };  //  class MultisetIterator
  class ConstMultisetIterator {
    friend class multiset;

   public:
    using value_type = Key;
    using pointer = const value_type *;
    using reference = const value_type &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    ConstMultisetIterator(Node *node) : current_node_(node) {
      while (current_node_ != nullptr) {
        nodeStack.push(current_node_);
        current_node_ = current_node_->left;
      }
      if (!nodeStack.empty()) {
        current_node_ = nodeStack.top();
        nodeStack.pop();
      }
    }

    reference operator*() const { return current_node_->key; }
    pointer operator->() const { return &(current_node_->key); }
    bool operator==(const const_iterator &other) const {
      return (other.current_node_ == current_node_);
    }
    bool operator!=(const const_iterator &other) const {
      return !(current_node_ == other.current_node_);
    }

    const_iterator &operator++() {
      if (current_node_->right != nullptr) {
        Node *temp = current_node_->right;
        while (temp != nullptr) {
          nodeStack.push(temp);
          temp = temp->left;
        }
      }
      if (!nodeStack.empty()) {
        current_node_ = nodeStack.top();
        nodeStack.pop();
      } else {
        current_node_ = nullptr;
      }
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

   private:
    Node *current_node_;
    s21::stack<Node *> nodeStack;
  };  // class const MultisetIterator

  multiset() { root_ = nullptr; }
  multiset(std::initializer_list<Key> const &items) : multiset() {
    try {
      for (auto it = items.begin(); it != items.end(); it++) {
        insert(*it);
      }
    } catch (...) {
      clear();
      throw;
    }
  }
  multiset(const multiset &s) { CopyTree(s.root_); };
  multiset(multiset &&s) noexcept { *this = std::move(s); }
  ~multiset() { clear(); }

  multiset operator=(multiset &&s) {
    if (this != &s) {
      clear();
      root_ = s.root_;
      s.root_ = nullptr;
      allocator_ = s.allocator_;
      size_ = s.size_;
    }
    return *this;
  };

  multiset &operator=(const multiset &other) {
    if (this == &other) {
      return *this;
    }
    this->clear();
    this->CopyTree(other.root_);
    return *this;
  }

  void clear() {
    DestroyTree(root_);
    root_ = nullptr;
  }

  iterator begin() { return iterator(root_); }
  iterator end() { return iterator(nullptr); }
  const_iterator begin() const { return const_iterator(root_); }
  const_iterator end() const { return const_iterator(nullptr); }
  bool empty() { return (root_ == nullptr); }
  size_type size() { return size_; }
  size_type max_size() const {
    return std::allocator_traits<allocator_type>::max_size(allocator_);
  }

  bool contains(const Key &key) { return (Search(key) != nullptr); }

  iterator insert(const Key &value) {
    Node *ins{};
    root_ = InsertIt(root_, value, &ins);
    return iterator(ins);
  }

  void erase(iterator pos) { erase(pos.current_node_, root_); }

  void merge(multiset &other) {
    if (other.root_ == nullptr) {
      return;
    }
    if (root_ == nullptr) {
      this->swap(other);
    } else {
      iterator it = other.begin();
      iterator fin = other.end();
      for (; it != fin; ++it) {
        this->insert(*it);
      }
      other.clear();
    }
  }

  void swap(multiset &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(allocator_, other.allocator_);
  }

  iterator find(const Key &key) {
    iterator it = this->begin();
    iterator fin = this->end();
    for (; it != fin; ++it) {
      if (!Less(key, *it) && !Less(*it, key)) {
        break;
      }
    }
    return it;
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    for (const auto &arg : {args...}) {
      auto result = insert(arg);
      results.push_back(result);
    }
    return results;
  }
  size_type count(const Key &key) { return countNodes(root_, key); }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::make_pair(this->lower_bound(key), this->upper_bound(key));
  }
  iterator lower_bound(const Key &key) {
    auto it = this->begin();
    while (it != this->end()) {
      if (!(*it < key)) {
        return it;
      }
      ++it;
    }
    return this->end();
  }

  iterator upper_bound(const Key &key) {
    auto it = this->begin();
    while (it != this->end()) {
      if (key < *it) {
        return it;
      }
      ++it;
    }
    return this->end();
  }

 private:
  //  Tree root_
  Node *root_{};
  allocator_type allocator_{};
  size_type size_{};
  bool Less(Key a, Key b, Compare cmp = Compare{}) { return cmp(a, b); }

  size_type countNodes(Node *node, const int &key) {
    if (node == nullptr) {
      return 0;
    }
    if (key < node->key) {
      return countNodes(node->left, key);
    } else if (key > node->key) {
      return countNodes(node->right, key);
    } else {
      return countNodes(node->left, key) + countNodes(node->right, key) + 1;
    }
  }

  void erase(Node *node, Node *&root_) {
    if (node == nullptr) {
      return;
    }
    Node *parent = nullptr;
    Node *current = root_;
    while (current != nullptr && current->key != node->key) {
      parent = current;
      // node->key < current->key
      if (Less(node->key, current->key)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (current == nullptr) {
      return;
    }
    RouteTree(current, parent);
  }

  void RouteTree(Node *current, Node *parent) {
    if (current->left == nullptr && current->right == nullptr) {
      if (current == root_) {
        root_ = nullptr;
      } else if (parent->left == current) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
      DealocNode(current);
    } else if (current->right == nullptr) {
      if (current == root_) {
        root_ = current->left;
      } else if (parent->left == current) {
        parent->left = current->left;
      } else {
        parent->right = current->left;
      }
      DealocNode(current);
    } else if (current->left == nullptr) {
      if (current == root_) {
        root_ = current->right;
      } else if (parent->left == current) {
        parent->left = current->right;
      } else {
        parent->right = current->right;
      }
      DealocNode(current);
    } else {
      Node *successorParent = current;
      Node *successor = current->right;
      RestructTree(successorParent, successor, current, parent);
    }
  }

  void RestructTree(Node *successorParent, Node *successor, Node *current,
                    Node *parent) {
    while (successor->left != nullptr) {
      successorParent = successor;
      successor = successor->left;
    }
    if (successorParent != current) {
      successorParent->left = successor->right;
      successor->right = current->right;
    }
    if (current == root_) {
      root_ = successor;
    } else if (parent->left == current) {
      parent->left = successor;
    } else {
      parent->right = successor;
    }
    successor->left = current->left;
    DealocNode(current);
  }

  void CopyTree(Node *node) {
    if (node != NULL) {
      CopyTree(node->left);
      CopyTree(node->right);
      insert(node->key);
    }
  }

  void DealocNode(Node *node) {
    std::allocator_traits<allocator_type>::destroy(allocator_, node);
    std::allocator_traits<allocator_type>::deallocate(allocator_, node, 1);
    size_--;
  }
  //  Tree full cleanup
  void DestroyTree(Node *node) {
    if (node != NULL) {
      DestroyTree(node->left);
      DestroyTree(node->right);
      DealocNode(node);
    }
  }

  Node *NewNode(const Key &key) {
    Node *new_node =
        std::allocator_traits<allocator_type>::allocate(allocator_, 1);
    std::allocator_traits<allocator_type>::construct(allocator_, new_node, key);
    size_++;
    return new_node;
  }

  Node *Search(Key key) { return Search(root_, key); }

  Node *Search(Node *node, const Key &key) {
    if (node == nullptr) return nullptr;
    //  node->key == key
    if (!Less(key, node->key) && !Less(node->key, key)) return node;
    //  key < node->key
    if (Less(key, node->key))
      return Search(node->left, key);
    else
      return Search(node->right, key);
  }

  Node *InsertIt(Node *node, const Key &key, Node **insert) {
    if (node == nullptr) {
      Node *tmp = NewNode(key);
      *insert = tmp;
      return tmp;
    }
    //  key < node->key
    if (Less(key, node->key)) {
      node->left = InsertIt(node->left, key, insert);
      //  key >= node->key
    } else {
      node->right = InsertIt(node->right, key, insert);
    }
    return node;
  }

};  // class multiset
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_MULTISET_H_
