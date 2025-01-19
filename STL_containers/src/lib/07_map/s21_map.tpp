#include "s21_map.h"

namespace s21 {

template <typename K, typename V>
map<K, V>::map() : tree_() {}

template <typename K, typename V>
map<K, V>::map(
    std::initializer_list<typename map<K, V>::value_type> const& items)
    : tree_() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <typename K, typename V>
map<K, V>::map(const map& m) : tree_(m.tree_) {}

template <typename K, typename V>
map<K, V> map<K, V>::operator=(map<K, V>&& m) {
  if (this != &m) {
    tree_ = std::move(m.tree_);
  }
  return *this;
}

template <typename K, typename V>
map<K, V>::~map() {}

template <typename K, typename V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert(
    const value_type& value) {
  std::pair<typename map<K, V>::iterator, bool> result;
  auto res = this->tree_.Search(value.first);
  if (not check_duplicates(std::make_pair(value.first, value.second))) {
    this->tree_.Insert(value.first, value.second);
    res = this->tree_.Search(value.first);
    if (this->tree_.GetInserted()) {
      result = std::make_pair(iterator(res), true);
    } else {
      result = std::make_pair(iterator(res), false);
    }
  }
  return result;
}

template <typename K, typename V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert_or_assign(
    const value_type& value) {
  std::pair<typename map<K, V>::iterator, bool> result;
  auto res = this->tree_.Search(value.first);
  if (res) {
    res->value = value.second;
    result = std::make_pair(iterator(res), false);
  } else {
    this->tree_.Insert(value.first, value.second);
    res = this->tree_.Search(value.first);
    if (this->tree_.GetInserted()) {
      result = std::make_pair(iterator(res), true);
    } else {
      result = std::make_pair(iterator(res), false);
    }
  }
  return result;
}

template <typename K, typename V>
template <class... Args>
std::vector<std::pair<typename map<K, V>::iterator, bool>>
map<K, V>::insert_many(Args&&... args) {
  std::vector<std::pair<typename map<K, V>::iterator, bool>> vec;
  for (const auto& arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename K, typename V>
typename map<K, V>::mapped_type& map<K, V>::at(const K& key) {
  return operatorHelper(key, false);
}

template <typename K, typename V>
typename map<K, V>::mapped_type& map<K, V>::operator[](const K& key) {
  return operatorHelper(key, true);
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::begin() const {
  Node<K, V>* node = tree_.GetRoot();
  if (!node) {
    return iterator(nullptr);
  }
  while (node && node->left && !node->left->isSentinel) {
    node = node->left;
  }
  return node ? iterator(node) : iterator(nullptr);
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::end() const {
  return iterator(nullptr, tree_.GetRoot());
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::find(const K& key) {
  Node<K, V>* node = tree_.Search(key);
  return node ? iterator(node) : end();
}

template <typename K, typename V>
bool map<K, V>::empty() {
  return tree_.GetRoot() == nullptr || tree_.GetRoot()->size_ == 0;
}

template <typename K, typename V>
typename map<K, V>::size_type map<K, V>::size() {
  return tree_.GetRoot() ? tree_.GetRoot()->size_ : 0;
}

template <typename K, typename V>
typename map<K, V>::size_type map<K, V>::max_size() const {
  return std::allocator_traits<Allocator>::max_size(allocator);
}

template <typename K, typename V>
void map<K, V>::clear() {
  if (tree_.GetRoot()) {
    iterator i = this->begin();
    while (i != this->end()) {
      iterator temp = i;
      ++i;
      this->erase(temp);
    }
  }
}

template <typename K, typename V>
void map<K, V>::erase(typename map<K, V>::iterator pos) {
  if (pos != this->end()) {
    this->tree_.Remove(pos.getKey());
  }
}

template <typename K, typename V>
void map<K, V>::swap(map& other) {
  tree_.Swap(other.tree_);
}

template <typename K, typename V>
void map<K, V>::merge(map& other) {
  std::pair<typename map<K, V>::iterator, bool> result;
  iterator iter = other.begin();
  while (iter != other.end()) {
    result = this->insert(*iter);
    if (result.second) other.erase(iter);
    ++iter;
  }
}

template <typename K, typename V>
bool map<K, V>::contains(const K& key) {
  for (iterator i = this->begin(); i != this->end(); ++i) {
    if (i->first == key) return true;
  }
  return false;
}

template <typename K, typename V>
typename map<K, V>::mapped_type& map<K, V>::operatorHelper(const K& key,
                                                           bool flag) {
  auto res = this->tree_.Search(key);
  if (res) {
    return const_cast<mapped_type&>(res->value);
  }
  if (flag) {
    auto inserted_pair = insert(value_type(key, mapped_type()));
    return const_cast<mapped_type&>(inserted_pair.first->second);
  } else {
    throw std::out_of_range("key doesn't exist");
  }
}

template <typename K, typename V>
bool map<K, V>::check_duplicates(const value_type& value) {
  auto i = this->begin();
  for (; i != this->end(); ++i) {
    if (i->first == value.first) {
      return true;
    }
  }
  return false;
}

}  // namespace s21
