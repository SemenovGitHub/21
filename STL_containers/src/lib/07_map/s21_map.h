#ifndef AVL_MAP_H_
#define AVL_MAP_H_

#include <initializer_list>
#include <memory>
#include <vector>

#include "../06_helpers/avl_tree.h"

namespace s21 {
template <typename K, typename V>
class map {
 public:
  using key_type = K;
  using mapped_type = V;
  using default_value = mapped_type&;
  using value_type = std::pair<const key_type, mapped_type>;
  using iterator = Iterator<K, V>;
  using const_iterator = ConstIterator<K, V>;
  using size_type = size_t;
  using Allocator = std::allocator<K>;

  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) = default;
  map<K, V> operator=(map&& m);
  ~map();

  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size() const;

  void clear();

  std::pair<iterator, bool> insert(const value_type& value);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  std::pair<iterator, bool> insert_or_assign(const value_type& value);
  iterator find(const K& key);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const key_type& key);

 private:
  AVLTree<K, V> tree_;
  Allocator allocator;

  mapped_type& operatorHelper(const key_type& key, bool flag);
  bool check_duplicates(const value_type& value);
};

}  // namespace s21
#include "s21_map.tpp"
#endif
