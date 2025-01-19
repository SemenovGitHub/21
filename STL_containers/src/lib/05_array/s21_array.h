#pragma once

// Temporary libs
#include "../../s21_containers.h"
namespace s21 {

template <typename T, std::size_t N>
class s21_array {
 private:
  // Attributes
  T data_[N];
  size_t size_;

 public:
  // Vector Member functions
  s21_array();
  s21_array(std::initializer_list<T> const& items);
  s21_array(const s21_array& other);
  s21_array(s21_array&& other);
  ~s21_array();
  s21_array& operator=(s21_array& other);
  s21_array& operator=(s21_array&& other);

  // Vector Element access
  T& at(size_t pos);
  T& operator[](size_t pos);
  const T& front();
  const T& back();
  T* data();

  // Vector Iterators
  T* begin();
  T* end();

  // Vector Capacity
  bool empty();
  size_t size();
  size_t max_size();

  // Vector Modifiers
  void fill(const T& value);
  void swap(s21_array& other);
};
}  // namespace s21

#include "s21_array.tpp"