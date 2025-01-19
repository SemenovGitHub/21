#include "s21_queue.h"

using namespace s21;

template <typename T>
s21_queue<T>::s21_queue() : s21_list<T>() {}

template <typename T>
s21_queue<T>::s21_queue(std::initializer_list<T> const &items)
    : s21_list<T>(items) {}

template <typename T>
s21_queue<T>::s21_queue(const s21_queue &other) : s21_list<T>(other) {}

template <typename T>
s21_queue<T>::s21_queue(s21_queue &&other) : s21_list<T>(std::move(other)) {}

template <typename T>
s21_queue<T> &s21_queue<T>::operator=(s21_queue &&other) {
  s21_list<T>::operator=(std::move(other));
  return *this;
}

template <typename T>
s21_queue<T>::~s21_queue() {
  s21_list<T>::clear();
}

template <typename T>
void s21_queue<T>::push(const T &data) {
  s21_list<T>::push_back(data);
}

template <typename T>
void s21_queue<T>::pop() {
  s21_list<T>::pop_front();
}