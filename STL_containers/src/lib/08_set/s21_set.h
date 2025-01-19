#pragma once

#include <algorithm>
#include <vector>

#include "../06_helpers/avl_tree.h"

namespace s21 {

template <typename T>
class set {
 public:
  using value_type = T;
  using iterator = SetIterator<T>;
  using const_iterator = ConstIterator<T, T>;
  using size_type = size_t;
  using Allocator = std::allocator<T>;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set<T>&& s);
  set<T>& operator=(set&& s);
  ~set() {}

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const T& value);
  void erase(iterator pos);
  void swap(set<T>& other);
  void merge(set<T>& other);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  bool contains(const T& key);
  iterator find(const T& key);
  const AVLTree<T, T>& get_tree() const;

 private:
  bool check_duplicates(const value_type& value);
  AVLTree<T, T> tree_;
  Allocator allocator;
};
}  // namespace s21

#include "s21_set.tpp"
