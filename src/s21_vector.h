#ifndef CONTAINERS_SRC_VECTOR_H_
#define CONTAINERS_SRC_VECTOR_H_

namespace s21 {
template <class T, class Allocator = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using allocator_type = Allocator;
  using allocator_traits = std::allocator_traits<allocator_type>;

  vector() : array_(nullptr), size_(0), capacity_(0){};  // базовый конструктор

  vector(size_type n) {
    array_ = allocator_traits::allocate(alloc_, n);

    for (size_type i = 0; i < n; ++i) {
      allocator_traits::construct(alloc_, array_ + i, value_type{});
    }
    size_ = capacity_ = n;
  }

  vector(std::initializer_list<value_type> const &items) {
    array_ = allocator_traits::allocate(alloc_, items.size());
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); ++it, ++i) {
      allocator_traits::construct(alloc_, array_ + i, *it);
    }
    size_ = capacity_ = items.size();
  }

  vector(const vector &v) {
    array_ = allocator_traits::allocate(alloc_, v.size_);

    for (size_type i = 0; i < v.size_; ++i) {
      allocator_traits::construct(alloc_, array_ + i, v[i]);
    }
    size_ = capacity_ = v.size_;
  }

  vector(vector &&v)
      : array_(v.array_), size_(v.size_), capacity_(v.capacity_) {
    v.array_ = nullptr;
    v.size_ = v.capacity_ = 0;
  }

  ~vector() {
    clear();
    size_ = capacity_ = 0;

    allocator_traits::deallocate(alloc_, array_, capacity_);
  }

  vector &operator=(const vector &v) {
    v.size_ <= size_ ? clear() : reserve(v.size_);

    for (size_type i = 0; i < v.size_; ++i) {
      allocator_traits::construct(alloc_, array_ + i, v[i]);
    }

    size_ = v.size_;

    return *this;
  }

  vector &operator=(vector &&v) {
    clear();
    allocator_traits::deallocate(alloc_, array_, capacity_);
    array_ = v.array_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.array_ = nullptr;
    v.size_ = v.capacity_ = 0;

    return *this;
  }

  void reserve(size_type size) {
    if (size < capacity_) return;

    reserve_capacity(size);
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::invalid_argument("argument is out of range");
    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }
  const_reference operator[](size_type pos) const { return array_[pos]; }

  size_type size() const { return size_; }
  size_type capacity() { return capacity_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void clear() {
    for (size_type i = 0; i < size_; ++i) {
      allocator_traits::destroy(alloc_, array_ + i);
    }
    size_ = 0;
  }

  T *data() { return array_; }

  const_reference front() const { return array_[0]; }
  const_reference back() const { return array_[size_ - 1]; }

  iterator begin() { return array_; }
  iterator end() { return array_ + size_; }
  const_iterator const_begin() const { return array_; }
  const_iterator const_end() const { return array_ + size_; }

  bool empty() const { return size_ == 0; }

  iterator insert(iterator pos, const_reference value) {
    return insert_many(pos, value);
  }

  void erase(iterator pos) {
    for (auto it = pos; it != end() - 1; ++it) {
      *it = *(it + 1);
    }
    allocator_traits::destroy(alloc_, array_ + size_);
    --size_;
  }

  void push_back(const_reference value) { insert_many(end(), value); }

  void pop_back() {
    if (size_ > 0) {
      erase(end() - 1);
    }
  }

  void shrink_to_fit() {
    if (size_ == capacity_) return;

    reserve_capacity(size_);
  }

  void swap(vector &other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type pos_diff = pos - begin();
    size_type arg_count = sizeof...(args);
    size_type newcap = get_capacity(capacity_, arg_count);

    if (newcap != capacity_) reserve_capacity(newcap);
    iterator insert_pos = begin() + pos_diff;

    for (auto it = end() - 1 + arg_count, it2 = end() - 1;
         it2 != insert_pos - 1; --it, --it2) {
      allocator_traits::construct(alloc_, it, *(it2));
    }

    auto it = insert_pos;
    for (auto i : {std::forward<Args>(args)...}) {
      allocator_traits::construct(alloc_, it, i);
      ++it;
    }

    size_ += arg_count;
    return insert_pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

 private:
  T *array_;
  size_type size_;
  size_type capacity_;
  allocator_type alloc_;

  void reserve_capacity(size_type size) {
    value_type *newarr = allocator_traits::allocate(alloc_, size);

    size_type i = 0;
    try {
      for (; i < size_; ++i) {
        allocator_traits::construct(alloc_, newarr + i, array_[i]);
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        allocator_traits::destroy(alloc_, newarr + i);
      }
      allocator_traits::deallocate(alloc_, newarr, size);
      throw;
    }

    for (size_type i = 0; i < size_; ++i) {
      allocator_traits::destroy(alloc_, newarr + i);
    }
    allocator_traits::deallocate(alloc_, array_, capacity_);

    array_ = newarr;
    capacity_ = size;
  }

  size_type get_capacity(size_type capacity, size_type arg_count = 0) {
    while (size_ + arg_count > capacity) capacity *= 2;
    return capacity;
  }
};
}  // namespace s21

#endif  // CONTAINERS_SRC_VECTOR_H_
