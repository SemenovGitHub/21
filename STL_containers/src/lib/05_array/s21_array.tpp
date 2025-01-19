#include "s21_array.h"

template <typename T, std::size_t N>
s21_array<T, N>::s21_array() {
  this->size_ = N;
}

template <typename T, std::size_t N>
s21_array<T, N>::s21_array(std::initializer_list<T> const& items) {
  if (items.size() > N) {
    throw std::out_of_range("Initializer list size does not match array size");
  }
  for (size_t i = 0; i < N; ++i) {
    this->data_[i] = T();
  }
  for (size_t i = 0; i < items.size(); ++i) {
    this->data_[i] = *(items.begin() + i);
  }
  this->size_ = N;
}

template <typename T, std::size_t N>
s21_array<T, N>::s21_array(const s21_array& other) {
  for (size_t i = 0; i < N; ++i) {
    this->data_[i] = other.data_[i];
  }
  this->size_ = other.size_;
}

template <typename T, std::size_t N>
s21_array<T, N>::s21_array(s21_array&& other) {
  for (size_t i = 0; i < N; ++i) {
    this->data_[i] = other.data_[i];
  }
  this->size_ = other.size_;

  other.~s21_array();
}

template <typename T, std::size_t N>
s21_array<T, N>::~s21_array() {
  for (size_t i = 0; i < this->size_; ++i) {
    this->data_[i].~T();
  }
}

template <typename T, std::size_t N>
s21_array<T, N>& s21_array<T, N>::operator=(s21_array& other) {
  std::copy(other.begin(), other.end(), this->data_);
  this->size_ = other.size_;

  return *this;
}

template <typename T, std::size_t N>
s21_array<T, N>& s21_array<T, N>::operator=(s21_array&& other) {
  std::copy(other.begin(), other.end(), this->data_);
  this->size_ = other.size_;
  for (int i = 0; i < other.size_; ++i) {
    other.data_[i].~T();
  }
}

template <typename T, std::size_t N>
T& s21_array<T, N>::at(size_t pos) {
  if (pos >= this->size_) {
    throw std::out_of_range("s21_array::at: pos out of range");
  }
  return this->data_[pos];
}

template <typename T, std::size_t N>
T& s21_array<T, N>::operator[](size_t pos) {
  return this->data_[pos];
}

template <typename T, std::size_t N>
const T& s21_array<T, N>::front() {
  if (this->size_ == 0) {
    throw std::out_of_range("s21_array::back: array is empty");
  }
  return this->data_[0];
}

template <typename T, std::size_t N>
const T& s21_array<T, N>::back() {
  if (this->size_ == 0) {
    throw std::out_of_range("s21_array::back: array is empty");
  }
  return this->data_[this->size_ - 1];
}

template <typename T, std::size_t N>
T* s21_array<T, N>::data() {
  return this->data_;
}

template <typename T, std::size_t N>
T* s21_array<T, N>::begin() {
  return data_;
}

template <typename T, std::size_t N>
T* s21_array<T, N>::end() {
  return this->data_ + this->size_;
}

template <typename T, std::size_t N>
bool s21_array<T, N>::empty() {
  return this->size_ == 0;
}

template <typename T, std::size_t N>
size_t s21_array<T, N>::size() {
  return this->size_;
}

template <typename T, std::size_t N>
size_t s21_array<T, N>::max_size() {
  return this->size_;
}

template <typename T, std::size_t N>
void s21_array<T, N>::fill(const T& value) {
  for (size_t i = 0; i < this->size_; ++i) {
    this->data_[i] = value;
  }
}

template <typename T, std::size_t N>
void s21_array<T, N>::swap(s21_array& other) {
  std::swap_ranges(this->data_, this->data_ + this->size_, other.data_);
  size_t tmp = this->size_;
  this->size_ = other.size_;
  other.size_ = tmp;
}