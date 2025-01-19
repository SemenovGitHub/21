#include "s21_list.h"

namespace s21 {
template <typename T>
ListIterator<T>::ListIterator()
    : current_(nullptr), head_exemp_(nullptr), tail_exemp_(nullptr) {}

template <typename T>

ListIterator<T>::ListIterator(const ListIterator &i) {
  current_ = i.current_;
}  // copy

template <typename T>
ListIterator<T>::~ListIterator() {
  current_ = nullptr;
}

template <typename T>
ListIterator<T>::ListIterator(IT_NODE_ NODE, s21_list<T> &list)
    : ListIterator() {
  if (NODE) current_ = NODE;
  if (list.head_) head_exemp_ = list.head_;
  if (list.tail_) tail_exemp_ = list.tail_;
}

template <typename T>
typename s21_list<T>::reference ListIterator<T>::operator*() {
  if (current_ != nullptr)
    return current_->value;
  else
    throw std::out_of_range("You try to move out of range");
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator++() {
  if (current_)
    current_ = current_->next;
  else
    throw std::out_of_range("You try to move out of range");
  return *this;
}
template <typename T>
ListIterator<T> &ListIterator<T>::operator++(int) {
  return ++(*this);
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator--() {
  if (current_ == nullptr && tail_exemp_ != nullptr)
    current_ = tail_exemp_;
  else if (current_ != head_exemp_)
    current_ = current_->prev;
  else
    throw std::out_of_range("You try to move out of range");
  return *this;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator--(int) {
  return --(*this);
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator &other) const {
  return current_ != other.current_;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator &other) const {
  return current_ == other.current_;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator=(const ListIterator<T> &other) {
  current_ = other.current_;
  return *this;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator=(ListConstIterator<T> &other) {
  current_ = other.current_;
  return *this;
}

// const

template <typename T>
ListConstIterator<T>::ListConstIterator()
    : current_(nullptr), head_exemp_(nullptr), tail_exemp_(nullptr) {}

template <typename T>

ListConstIterator<T>::ListConstIterator(const ListConstIterator &i) {
  current_ = i.current_;
}  // copy

template <typename T>
ListConstIterator<T>::ListConstIterator(IT_NODE_ NODE, const s21_list<T> &list)
    : ListConstIterator() {
  if (NODE) current_ = NODE;
  if (list.head_) head_exemp_ = list.head_;
  if (list.tail_) tail_exemp_ = list.tail_;
}

template <typename T>
ListConstIterator<T>::~ListConstIterator() {
  current_ = nullptr;
}

template <typename T>
typename s21_list<T>::const_reference ListConstIterator<T>::operator*() const {
  if (current_ != nullptr)
    return current_->value;
  else
    throw std::out_of_range("You try to move out of range");
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator++() {
  if (current_)
    current_ = current_->next;
  else
    throw std::out_of_range("You try to move out of range");
  return *this;
}
template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator++(int) {
  return ++(*this);
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator--() {
  if (current_ == nullptr && tail_exemp_ != nullptr)
    current_ = tail_exemp_;
  else if (current_ != head_exemp_)
    current_ = current_->prev;
  else
    throw std::out_of_range("You try to move out of range");
  return *this;
}
template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator--(int) {
  return --(*this);
}

template <typename T>
bool ListConstIterator<T>::operator!=(const ListConstIterator &other) const {
  return current_ != other.current_;
}

template <typename T>
bool ListConstIterator<T>::operator==(const ListConstIterator &other) const {
  return current_ == other.current_;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator=(
    const ListConstIterator<T> &other) {
  current_ = other.current_;
  return *this;
}
}  // namespace s21