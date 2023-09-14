#ifndef CONSTAINERS_SRC_S21_STACK_H_
#define CONSTAINERS_SRC_S21_STACK_H_
#include <memory>

namespace s21 {

template <class T>
class stack {
 public:
  // Stack Member type
  using value_type = T;   // the template parameter T
  using reference = T &;  // defines the type of the reference to an element
  using const_reference =
      const T &;             // defines the type of the constant reference
  using size_type = size_t;  // defines the type of the container size (standard
                             // type is size_t)
  struct node {
    value_type val;
    node *next;
    node *prev;
    node() : val(), next(nullptr), prev(nullptr){};
    node(value_type value) : val(value), next(nullptr), prev(nullptr){};
  };

 public:
  // Stack Member functions
  // default constructor, creates empty stack
  stack() : head(nullptr), tail(nullptr), stackSize(0U){};
  stack(std::initializer_list<value_type> const &items) : stack() {
    for (auto it = items.begin(); it != items.end(); it++) {
      push(*it);
    }
  }
  // copy constructor
  stack(const stack &s) : stack() {
    for (size_type i = 0; i < s.size(); ++i) {
      push(s[i]->val);
    }
  }

  node *operator[](const size_type index) const {
    if (!head) return nullptr;
    node *p = head;
    for (size_type i = 0; i < index; i++) {
      p = p->next;
      if (!p) return nullptr;
    }
    return p;
  }
  // move constructor
  stack(stack &&s) noexcept : stack() {
    swap(s);
    s.clear();
  }
  // destructor
  ~stack() { this->clear(); }
  // assignment operator overload for moving object
  stack &operator=(stack &&s) {
    swap(s);
    s.clear();
    return *this;
  }

  // Stack Element access
  // accesses the top element
  const_reference top() const { return tail->val; }

  // Stack Capacity
  // checks whether the container is empty
  bool empty() const noexcept { return head == nullptr; }
  // returns the number of elements
  size_type size() const noexcept { return stackSize; }
  // Stack Modifiers
  // removes the top element
  void push(const_reference val) {
    std::unique_ptr<node> buff(new node(val));
    if (empty()) {
      head = tail = buff.get();
    } else {
      buff->prev = tail;
      tail->next = buff.get();
      tail = buff.get();
    }
    buff.release();
    stackSize++;
  }  // inserts element at the top
  // removes the top element
  void pop() {
    if (empty()) return;
    std::unique_ptr<node> buff(tail);
    if (tail->prev == nullptr) {
      tail = head = nullptr;
    } else {
      tail->prev->next = nullptr;
      tail = tail->prev;
    }
    stackSize--;
  }
  // swaps the contents
  void swap(stack &other) {
    std::swap(other.head, head);
    std::swap(other.tail, tail);
    std::swap(other.stackSize, stackSize);
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    value_type temp_(std::forward<Args>(args)...);
    push(temp_);
  }

 private:
  //  Container cont;
  node *head;
  node *tail;
  size_type stackSize;
  void clear() {
    stackSize = 0U;
    node *current = head;
    while (current) {
      node *next = current->next;
      delete current;
      current = next;
    }
  }
};
}  // namespace s21

#endif  // CONSTAINERS_SRC_S21_STACK_H_
