#include "s21_stack.h"

template <typename T>
s21_stack<T>::s21_stack() : s21_list<T>() {}

template <typename T>
s21_stack<T>::s21_stack(std::initializer_list<T> const &items)
    : s21_list<T>(items) {}

template <typename T>
s21_stack<T>::s21_stack(const s21_stack &other) : s21_list<T>(other) {}
template <typename T>
s21_stack<T>::s21_stack(s21_stack &&other) : s21_list<T>(std::move(other)) {}

template <typename T>
s21_stack<T> &s21_stack<T>::operator=(s21_stack &&other) {
  s21_list<T>::operator=(std::move(other));
  return *this;
}

template <typename T>
s21_stack<T>::~s21_stack() {
  s21_list<T>::clear();
}

template <typename T>
void s21_stack<T>::push(const T &data) {
  s21_list<T>::push_back(data);
}

template <typename T>
const T &s21_stack<T>::top() {
  return s21_list<T>::back();
}

template <typename T>
void s21_stack<T>::pop() {
  s21_list<T>::pop_back();
}