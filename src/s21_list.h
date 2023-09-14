#ifndef CONTAINERS_SRC_S21_LIST_H_
#define CONTAINERS_SRC_S21_LIST_H_

#include <cmath>
#include <limits>
#include <memory>

namespace s21 {
template <typename T>
class list {
  // list Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  struct Node;

  // public attribures
 public:
  template <typename value_type>
  class listIterator {
   public:
    friend class list<T>;
    listIterator() { current = nullptr; }
    listIterator(Node* ptr) : current(ptr){};

    reference operator*() { return current->value; }

    value_type* operator->() const { return &(current->value); }

    listIterator& operator++() {
      current = current->next;
      return *this;
    }

    listIterator& operator--() {
      current = current->prev;
      return *this;
    }

    listIterator& operator++(int) {
      iterator it = *this;
      current = current->next;
      return it;
    }

    listIterator& operator--(int) {
      iterator it = *this;
      current = current->prev;
      return it;
    }

    bool operator==(const listIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const listIterator& other) const {
      return !(current == other.current);
    }

   private:
    friend class list<T>;  // can use private of list
    Node* current = nullptr;
  };

  template <typename value_type>
  class listConstIterator : public listIterator<T> {
   public:
    listConstIterator();
    listConstIterator(listIterator<T> other) : listIterator<T>(other) {}

    const_reference operator*() const { return listIterator<T>::operator*(); }
  };
  // list Member type
  using iterator = listIterator<T>;
  using const_iterator = listConstIterator<T>;

  // list Functions
  list()
      : head_(nullptr),
        tail_(nullptr),
        size_(0){};  // default constructor, creates empty list 

  list(size_type n)
      : head_(nullptr),
        tail_(nullptr),
        size_(0) {  // parameterized constructor, creates the list of size_ n
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const& items)
      : head_(nullptr),
        tail_(nullptr),
        size_(0) {  // initializer list constructor, creates list initizialized
                    // using std::initializer_list
    for (const auto& item : items) {
      push_back(item);
    }
  }

  list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
    operator=(l);
  }  // copy constructor

  list(list&& l) : head_(nullptr), tail_(nullptr), size_(0) {
    swap(l);
  }  // move constructor

  ~list() {  // destructor
    clear();
  }

  reference front() { return head_->value; }
  const_reference front() const {
    return head_->value;
  }  // access the first element
  const_reference back() const {
    return tail_->value;
  }  //  access the last element
  reference back() { return tail_->value; }

  // list Iterators
  iterator begin() noexcept {
    return iterator(head_);
  }  // returns an iterator to the beginning
  iterator end() noexcept {
    return iterator(nullptr);
  }  //  returns an iterator to the end

  iterator last() noexcept {
    if (begin() == end()) return end();
    auto it = begin();
    ++it;
    auto result = begin();
    while (it != end()) {
      result = it;
      ++it;
    }
    return result;
  }

  // list Capacity
  bool empty() const noexcept {
    return head_ == nullptr;
  }  // checks whether the container is empty

  size_type size() const noexcept {
    return size_;
  }  //  returns the number of elements

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }  //  returns the maximum possible number of elements

  // list Modifiers
  void clear() {
    while (!(empty())) {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* newNode = new Node(value);
    if (empty()) {
      head_ = newNode;
      tail_ = newNode;
    } else {
      if (pos == begin()) {
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
      } else if (pos == end()) {
        //  std::cout << "!!!" << std::endl;
        tail_->next = newNode;
        newNode->prev = tail_;
        tail_ = newNode;
      } else {
        Node* current = pos.current;
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
      }
    }
    size_++;
    return iterator(newNode);
  }

  void erase(iterator pos)  //  erases element at pos
  {
    if (pos != end()) {
      if (size_ != 1) {
        if (pos == begin()) {
          Node* oldNode = head_;
          head_ = head_->next;
          head_->prev = nullptr;
          delete oldNode;
        } else if (pos == last()) {
          Node* oldNode = tail_;
          tail_ = tail_->prev;
          tail_->next = nullptr;
          delete oldNode;
        } else {
          Node* oldNode = pos.current;
          oldNode->prev->next = oldNode->next;
          oldNode->next->prev = oldNode->prev;
          delete oldNode;
        }
        size_--;
      } else {
        clear();
      }
    }
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() {
    if (!(empty())) {
      erase(last());
    }
  }

  void push_front(const_reference value)  // adds an element to the head_
  {
    insert(begin(), value);
  }

  void pop_front()  // removes the first element
  {
    if (!(empty())) {
      erase(begin());
    }
  }

  void swap(list& other)  // swaps the contents
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void merge(list& other) {
    if (size_ + other.size_ > max_size()) throw "Maximum of container";
    if ((this != &other) && (!(other.empty()))) {
      if (empty()) {
        copy(other);
      } else {
        iterator itThis = begin();
        iterator itOther = other.begin();
        while (itOther != other.end()) {
          if (itThis != end()) {
            if (itThis.current->value >= itOther.current->value) {
              insert(itThis, itOther.current->value);
              ++itOther;
            } else {
              ++itThis;
            }
          } else {
            insert(itThis, itOther.current->value);
            ++itOther;
          }
        }
      }
      other.clear();
    }
  }

  void splice(
      const_iterator pos,
      list& other)  // transfers elements from list other starting from pos
  {
    if (!(other.empty())) {
      if (empty()) {
      }
      iterator tempIt = pos;
      for (auto it = other.begin(); it != other.end(); ++it) {
        insert(tempIt, *it);
      }
      other.clear();
    }
  }

  void reverse()  // reverses the order of the elements
  {
    if ((!empty()) && (size_ > 1)) {
      auto itLeft = begin();
      auto itRight = last();
      for (size_type i = 0; i < size_ / 2; i++) {
        std::swap(*itLeft, *itRight);
        ++itLeft;
        --itRight;
      }
    }
  }

  void unique()  // removes consecutive duplicate elements
  {
    if (size_ > 1) {
      Node* current = head_;
      while (current->next != nullptr) {
        if (current->value == current->next->value) {
          Node* duplicate = current->next;
          current->next = duplicate->next;
          if (duplicate->next != nullptr) {
            duplicate->next->prev = current;
          }
          delete duplicate;
          --size_;
        } else {
          current = current->next;
        }
      }
    }
  }

  void sort() {
    if (size_ > 1) {
      auto it = ++begin();
      while (it != end()) {
        value_type key = it.current->value;
        auto pos = it;
        while (pos != begin() && pos.current->prev->value > key) {
          pos.current->value = pos.current->prev->value;
          --pos;
        }
        pos.current->value = key;
        ++it;
      }
    }
  }

  void copy(const list& l) {
    if (this != &l) {
      clear();
      Node* current = l.head_;
      for (size_type i = 0; i != l.size_; i++) {
        push_back(current->value);
        current = current->next;
      }
    }
  }

  list& operator=(const list& l) {
    copy(l);
    return *this;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  template <class... Args>
  iterator insert_many(const_iterator pos,
                       Args&&... args)  // inserts new elements into the
                                        // container directly before pos
  {
    for (const auto& arg : {args...}) {
      insert(
          pos,
          arg);  //  вставляем каждый элемент перед позицией `pos` в контейнере
    }
    return pos;
  }

  template <class... Args>
  void insert_many_back(
      Args&&... args)  // appends new elements to the end of the container
  {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }

  template <class... Args>
  void insert_many_front(
      Args&&... args)  // appends new elements to the top of the container
  {
    auto it = begin();
    for (const auto& arg : {args...}) {
      // push_front(arg);
      insert(it, arg);
    }
  }

 private:
  struct Node {
    value_type value;
    Node* prev;
    Node* next;
    Node(const value_type& value)
        : value(value), prev(nullptr), next(nullptr) {}
  };

  Node* head_;      //  first element pointer
  Node* tail_;      //  last element pointer
  size_type size_;  // size of list

};  // class list
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_LIST_H_
