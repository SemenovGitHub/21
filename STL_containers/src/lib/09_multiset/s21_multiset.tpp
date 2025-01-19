#include "./s21_multiset.h"

namespace s21 {
template <typename T>
multiset<T>::multiset() : tree_() {}

template <typename T>
multiset<T>::multiset(multiset<T>&& s) {
  this->tree_ = std::move(s.tree_);
  this->allocator = std::move(s.allocator);
}

template <typename T>
multiset<T>::multiset(std::initializer_list<value_type> const& items)
    : tree_() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <typename T>
multiset<T>::multiset(const multiset& s)
    : s21::set<T>(s), tree_(s.get_tree()) {}
template <typename T>
multiset<T>& multiset<T>::operator=(multiset<T>&& s) {
  if (this != &s) {
    tree_ = std::move(s.tree_);
  }
  return *this;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::begin() const {
  Node<T, T>* node = tree_.GetRoot();
  if (node == nullptr) {
    return iterator(nullptr);
  }
  while (node->left != nullptr && !node->left->isSentinel) {
    node = node->left;
  }
  if (node->isSentinel) {
    return iterator(nullptr);
  } else {
    return iterator(node);
  }
}

template <typename T>
typename multiset<T>::iterator multiset<T>::end() const {
  return iterator(nullptr, tree_.GetRoot());
}

template <typename T>
bool multiset<T>::empty() {
  if (this->tree_.GetRoot() == nullptr) {
    return true;
  }
  if (this->tree_.GetRoot()->size_ == 0) {
    return true;
  }
  return false;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::size() {
  if (this->tree_.GetRoot() == nullptr) {
    return 0;
  }
  return tree_.GetRoot()->size_;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::max_size() {
  return allocator.max_size() / 10;
}

template <typename T>
void multiset<T>::clear() {
  if (this->tree_.GetRoot()) {
    Node<T, T>* root = this->tree_.GetRoot();
    this->tree_.Clear(root);
    this->tree_.SetRoot(nullptr);
  }
}

template <typename T>
std::pair<typename multiset<T>::iterator, bool> multiset<T>::insert(
    const T& value) {
  std::pair<typename multiset<T>::iterator, bool> result;

  result =
      std::make_pair(iterator(this->tree_.InsertMultiSet(value, value)), true);

  return result;
}

template <typename T>
void multiset<T>::erase(multiset<T>::iterator pos) {
  if (pos != nullptr) {
    tree_.Remove(pos.getKey());
  }
}

template <typename T>
void multiset<T>::swap(multiset<T>& other) {
  tree_.Swap(other.tree_);
}

template <typename T>
void multiset<T>::merge(multiset<T>& other) {
  if (this != &other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      insert(*i);
    }
  }
  other.clear();
}

template <typename T>
bool multiset<T>::contains(const T& key) {
  return tree_.Search(key) != nullptr;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::find(const T& key) {
  return iterator(tree_.Search(key));
}

template <typename T>
const AVLTree<T, T>& multiset<T>::get_tree() const {
  return tree_;
}
}  // namespace s21

template <typename T>
template <class... Args>
std::vector<std::pair<typename s21::multiset<T>::iterator, bool>>
s21::multiset<T>::insert_many(Args&&... args) {
  std::vector<std::pair<typename set<T>::iterator, bool>> vec;
  for (const auto& arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename T>
std::pair<typename s21::multiset<T>::iterator,
          typename s21::multiset<T>::iterator>
s21::multiset<T>::equal_range(const T& key) {
  iterator lower = lower_bound(key);
  iterator upper = upper_bound(key);
  return std::make_pair(lower, upper);
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::lower_bound(
    const T& key) {
  iterator it = begin();
  while (it != end() && *it < key) {
    ++it;
  }
  return it;
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::upper_bound(
    const T& key) {
  iterator it = begin();
  while (it != end() && !(key < *it)) {
    ++it;
  }
  return it;
}

template <typename T>
typename s21::multiset<T>::size_type s21::multiset<T>::count(
    const T& key) const {
  size_t count = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      ++count;
    }
  }
  return count;
}
