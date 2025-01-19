#pragma once

// Temporary libs
#include "../../s21_containers.h"
namespace s21 {
template <typename T>
class s21_queue : public s21_list<T> {
  using NODE = typename s21_list<T>::NODE;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  s21_queue();
  s21_queue(std::initializer_list<T> const &items);
  s21_queue(const s21_queue &other);
  s21_queue(s21_queue &&s);
  ~s21_queue();

  void push(const T &data);
  void pop();

  s21_queue &operator=(s21_queue &&other);

 private:
  NODE *head_;
  NODE *tail_;
  size_type size_;
};
}  // namespace s21

#include "s21_queue.tpp"