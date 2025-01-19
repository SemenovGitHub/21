#pragma once

#include "../../s21_containers.h"

template <typename T>
class s21_stack : public s21_list<T> {
  using NODE = typename s21_list<T>::NODE;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  s21_stack();
  s21_stack(std::initializer_list<T> const &items);
  s21_stack(const s21_stack &other);
  s21_stack(s21_stack &&s);
  ~s21_stack();

  void push(const T &data);
  void pop();
  const T &top();

  s21_stack &operator=(s21_stack &&other);

 private:
  NODE *head_;
  size_type size_;
};

#include "s21_stack.tpp"
