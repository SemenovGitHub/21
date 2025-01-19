#pragma once

// Temporary libs
#include "../../s21_containers.h"
namespace s21 {

template <typename T>
class s21_vector {
 private:
  // Attributes
  size_t size_;
  size_t capacity_;
  T* data_;

 public:
  // Vector Member functions
  s21_vector();                         //+
  s21_vector(size_t size);              //+
  s21_vector(const s21_vector& other);  //+
  s21_vector(s21_vector&& other);       //+
  s21_vector<T>& operator=(s21_vector& other);
  s21_vector<T>& operator=(s21_vector&& other);
  s21_vector(std::initializer_list<T> const& items);  //+
  ~s21_vector();                                      //+

  // Vector Element access
  T& at(size_t pos);          //+
  T& operator[](size_t pos);  //+
  const T& front();           //+
  const T& back();            //+
  T* data();                  //+

  // Vector Iterators
  T* begin();  //+
  T* end();    //+

  // Vector Capacity
  bool empty();               //+
  size_t size();              //+
  size_t max_size();          //+
  void reserve(size_t size);  //+
  size_t capacity();          //+
  void shrink_to_fit();       //+

  // Vector Modifiers
  void clear();                       //+
  T* insert(T* pos, const T& value);  //+
  void erase(T* pos);                 //+
  void push_back(const T& value);     //+
  void pop_back();                    //+
  void swap(s21_vector& other);
  template <typename... Args>
  T* insert_many(const T* pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  template <typename... Rest>
  T* insert_many_impl(T* pos, const T& first, const Rest&... rest);
  template <typename... Rest>
  void insert_many_back_impl(const T& first, const Rest&... rest);
};
}  // namespace s21

#include "s21_vector.tpp"