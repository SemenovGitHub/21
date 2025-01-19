#include "s21_vector.h"

template <typename T>
s21_vector<T>::s21_vector() {
  this->size_ = 0;
  this->capacity_ = 0;
  this->data_ = nullptr;
}

template <typename T>
s21_vector<T>::s21_vector(size_t size) {
  this->size_ = size;
  this->capacity_ = size;
  this->data_ = new T[this->capacity_];
}

template <typename T>
s21_vector<T>::s21_vector(const s21_vector& other) {
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;

  this->data_ = new T[this->size_];
  for (size_t i = 0; i < this->size_; ++i) {
    this->data_[i] = other.data_[i];
  }
}

template <typename T>
s21_vector<T>::s21_vector(s21_vector&& other) {
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;
  this->data_ = other.data_;

  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
s21_vector<T>& s21_vector<T>::operator=(s21_vector& other) {
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;

  if (this->data_) {
    delete[] this->data_;
  }
  this->data_ = new T[this->size_];
  for (size_t i = 0; i < this->size_; ++i) {
    this->data_[i] = other.data_[i];
  }
  return *this;
}

template <typename T>
s21_vector<T>& s21_vector<T>::operator=(s21_vector&& other) {
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;

  this->data_ = other.data_;

  for (int i = 0; i < other.size_; ++i) {
    other.data_[i].~T();
  }
  if (other->data_) {
    delete[] other->data_;
  }
  return *this;
}

template <typename T>
s21_vector<T>::s21_vector(std::initializer_list<T> const& items) {
  this->size_ = items.size();
  this->capacity_ = items.size();
  this->data_ = new T[this->size_];

  std::copy(items.begin(), items.end(), this->data_);
}

template <typename T>
s21_vector<T>::~s21_vector() {
  if (this->data_) {
    delete[] this->data_;
  }
  this->size_ = 0;
  this->capacity_ = 0;
  this->data_ = nullptr;
}

template <typename T>
T& s21_vector<T>::at(size_t pos) {
  if (pos >= this->size_) {
    throw std::out_of_range("s21_vector::at: pos out of range");
  }
  return this->data_[pos];
}

template <typename T>
T& s21_vector<T>::operator[](size_t pos) {
  return this->data_[pos];
}

template <typename T>
const T& s21_vector<T>::front() {
  if (this->size_ == 0) {
    throw std::out_of_range("s21_vector::back: vector is empty");
  }
  return this->data_[0];
}

template <typename T>
const T& s21_vector<T>::back() {
  if (this->size_ == 0) {
    throw std::out_of_range("s21_vector::back: vector is empty");
  }
  return this->data_[this->size_ - 1];
}

template <typename T>
T* s21_vector<T>::data() {
  return this->data_;
}

template <typename T>
T* s21_vector<T>::begin() {
  return this->data_;
}

template <typename T>
T* s21_vector<T>::end() {
  return this->data_ + this->size_;
}

template <typename T>
bool s21_vector<T>::empty() {
  return this->size_ == 0;
}

template <typename T>
size_t s21_vector<T>::size() {
  return this->size_;
}

template <typename T>
size_t s21_vector<T>::max_size() {
  return std::allocator<T>().max_size();
}

template <typename T>
void s21_vector<T>::reserve(size_t size) {
  if (size > this->size_) {
    T* new_data = new T[size];
    for (size_t i = 0; i < this->size_; ++i) {
      new_data[i] = this->data_[i];
    }
    for (size_t i = 0; i < this->size_; ++i) {
      this->data_[i].~T();
    }
    delete[] this->data_;
    this->data_ = new_data;
    this->capacity_ = size;
    new_data = nullptr;
  }
}

template <typename T>
size_t s21_vector<T>::capacity() {
  return this->capacity_;
}

template <typename T>
void s21_vector<T>::shrink_to_fit() {
  if (this->size_ >= this->capacity_) {
    throw std::out_of_range(
        "s21_vector::shrink_to_fit: the size is equal to capacity");
  }
  if (this->size_ < this->capacity_) {
    s21_vector<T> tmp(*this);
    if (this->data_) {
      delete[] this->data_;
    }
    this->data_ = new T[this->size_];
    this->size_ = tmp.size_;
    this->capacity_ = tmp.size_;
    for (size_t i = 0; i < this->size_; ++i) {
      this->data_[i] = tmp.data_[i];
    }
  }
}

template <typename T>
void s21_vector<T>::clear() {
  for (size_t i = 0; i < this->size_; ++i) {
    this->data_[i].~T();
  }
  this->size_ = 0;
}

template <typename T>
T* s21_vector<T>::insert(T* pos, const T& value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("s21_vector::insert: the iterator is out of data");
  }
  T* ptr = nullptr;
  size_t index = 0;
  for (ptr = this->data_; ptr != pos; ++ptr) {
    ++index;
  }
  if (this->size_ == this->capacity_ && this->size_) {
    this->reserve(this->capacity_ * 2);
  } else if (this->size_ == this->capacity_ && this->size_ == 0) {
    this->reserve(this->capacity_ + 1);
  }
  for (size_t i = this->size_; i > index; --i) {
    this->data_[i] = this->data_[i - 1];
  }
  this->data_[index] = value;
  ++this->size_;
  ptr = this->data_ + index;

  return ptr;
}

template <typename T>
void s21_vector<T>::erase(T* pos) {
  if (pos < begin() || pos >= end()) {
    throw std::out_of_range("s21_vector::erase: pos out of range");
  }
  for (; pos < this->data_ + this->size_ - 1; ++pos) {
    *pos = *(pos + 1);
  }
  --this->size_;
}

template <typename T>
void s21_vector<T>::push_back(const T& value) {
  if (this->size_ == this->capacity_) {
    this->reserve(this->capacity_ * 2);
  }
  *(this->data_ + this->size_) = value;
  ++this->size_;
}

template <typename T>
void s21_vector<T>::pop_back() {
  if (this->size_ > 0) {
    --this->size_;
    this->data_[this->size_] = ~T();
  }
}

template <typename T>
void s21_vector<T>::swap(s21_vector& other) {
  T* tmp = this->data_;
  size_t tmp_size = this->size_;
  size_t tmp_capacity = this->capacity_;

  this->data_ = other.data_;
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;

  other.data_ = tmp;
  other.size_ = tmp_size;
  other.capacity_ = tmp_capacity;

  tmp = nullptr;
}

template <typename T>
template <typename... Args>
T* s21_vector<T>::insert_many(const T* pos, Args&&... args) {
  T* mutable_pos = const_cast<T*>(pos);

  return insert_many_impl(mutable_pos, std::forward<Args>(args)...);
}

template <typename T>
template <typename... Rest>
T* s21_vector<T>::insert_many_impl(T* pos, const T& first,
                                   const Rest&... rest) {
  T* new_pos = insert(pos, first);

  if constexpr (sizeof...(rest) > 0) {
    return insert_many_impl(new_pos + 1, rest...);
  } else {
    return new_pos;
  }
}

template <typename T>
template <typename... Args>
void s21_vector<T>::insert_many_back(Args&&... args) {
  insert_many_back_impl(std::forward<Args>(args)...);
}

template <typename T>
template <typename... Rest>
void s21_vector<T>::insert_many_back_impl(const T& first, const Rest&... rest) {
  insert(end(), first);

  if constexpr (sizeof...(rest) > 0) {
    insert_many_back_impl(rest...);
  }
}