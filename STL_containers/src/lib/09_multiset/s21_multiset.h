#pragma once

#include <algorithm>

#include "../../s21_containers.h"
#include "../06_helpers/avl_tree.h"

namespace s21 {

template <typename T>
class multiset : public set<T> {
 public:
  using value_type = T;
  using iterator = SetIterator<T>;
  using const_iterator = ConstIterator<T, T>;
  using size_type = size_t;
  using Allocator = std::allocator<T>;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& s);
  multiset(multiset<T>&& s);
  multiset<T>& operator=(multiset&& s);
  ~multiset() {}

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const T& value);
  void erase(iterator pos);
  void swap(multiset<T>& other);
  void merge(multiset<T>& other);

  bool contains(const T& key);
  iterator find(const T& key);
  const AVLTree<T, T>& get_tree() const;
  std::pair<iterator, iterator> equal_range(const T& key);
  iterator lower_bound(const T& key);
  iterator upper_bound(const T& key);
  size_type count(const T& key) const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  AVLTree<T, T> tree_;
  Allocator allocator;
};
}  // namespace s21

#include "s21_multiset.tpp"