#pragma once

#include <iostream>
#include <utility>
using namespace std;

namespace s21 {
template <typename K, typename V>
class Node {
  using reference = const std::pair<const K, V>;

 public:
  K key;
  V value;
  reference ref;
  int height;
  size_t size_;
  bool isSentinel;
  Node<K, V>* left;
  Node<K, V>* right;
  Node<K, V>* parent;

  Node(const K& k, const V& v)
      : key(k),
        value(v),
        ref({k, v}),
        height(1),
        size_(1),
        isSentinel(false),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}

  Node(K& k, V& v)
      : key(k),
        value(v),
        ref({k, v}),
        height(1),
        size_(1),
        isSentinel(false),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
};

template <typename K, typename V>
class AVLTree {
  template <typename T>
  friend class set;
  template <typename T>
  friend class multiset;

 public:
  AVLTree();
  AVLTree(const AVLTree& other);
  ~AVLTree();
  AVLTree<K, V>& operator=(AVLTree&& other);
  Node<K, V>* Insert(const K& key, const V& value);
  Node<K, V>* InsertMultiSet(const K& key, const V& value);
  Node<K, V>* Remove(const K& key);
  Node<K, V>* Search(const K& key) const;
  Node<K, V>* GetRoot() const;
  void SetRoot(Node<K, V>* root);
  void Swap(AVLTree<K, V>& other);
  void Clear(Node<K, V>* node);
  bool GetInserted();
  Node<K, V>* MaximumKey(Node<K, V>* node) const;
  void UpdateSize(Node<K, V>* node);
  K getKeyFromNode(Node<K, V>* node) const;

 private:
  Node<K, V>* root;
  Node<K, V>* nil;
  bool inserted;
  int Size(Node<K, V>* node) const;
  int Height(Node<K, V>* node) const;
  int BalanceFactor(Node<K, V>* node) const;
  void UpdateHeight(Node<K, V>* node);
  Node<K, V>* Balance(Node<K, V>* node);
  Node<K, V>* FindMin(Node<K, V>* node) const;
  Node<K, V>* CopyTree(Node<K, V>* node);
  Node<K, V>* RotateLeft(Node<K, V>* node);
  Node<K, V>* RotateRight(Node<K, V>* node);
  Node<K, V>* RemoveMin(Node<K, V>* node);
  Node<K, V>* Remove(Node<K, V>* node, const K& key);
  Node<K, V>* Insert(Node<K, V>* node, const K& key, const V& value,
                     Node<K, V>* parent);
  Node<K, V>* InsertMultiSet(Node<K, V>* node, const K& key, const V& value,
                             Node<K, V>* parent);
};

template <typename K, typename V>
class Iterator {
 public:
  using key_type = K;
  using reference = const std::pair<const K, V>&;
  using pointer = const std::pair<const K, V>*;

  Iterator(Node<K, V>* node = nullptr) : node_(node) {}
  Iterator(Node<K, V>* nil, Node<K, V>* root) : node_(nil), root_(root) {}
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  ~Iterator() = default;

  explicit operator bool() const { return node_ != nullptr; }

  K getKey() const { return node_ ? node_->key : K{}; }

  Iterator operator+(const size_t value) {
    Iterator tmp = *this;
    for (size_t i = 0; i < value; i++) {
      ++tmp;
    }
    return tmp;
  }

  Iterator& operator++() {
    if (node_ != nullptr) {
      if (node_->right != nullptr) {
        node_ = node_->right;
        while (node_->left != nullptr) {
          node_ = node_->left;
        }
      } else {
        Node<K, V>* parent = node_->parent;
        while (parent != nullptr && node_ == parent->right) {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }
    return *this;
  }

  Iterator& operator++(int) { return ++(*this); }

  Iterator& operator--() {
    if (Size(root_) > 0) {
      if (node_ != nullptr) {
        return OperatorHelper();
      }
      node_ = MaximumKey(root_);
      return *this;
    }
    return OperatorHelper();
  }

  Iterator operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const Iterator& other) const { return node_ == other.node_; }
  bool operator!=(const Iterator& other) const { return node_ != other.node_; }

  reference operator*() const { return node_->ref; }

  pointer operator->() const {
    if (node_ == nullptr) {
      static std::pair<const K, V> default_value = {K{}, V{}};
      return &default_value;
    }
    static std::pair<const K, V> temp_pair = {node_->key, node_->value};
    return &temp_pair;
  }
  int Size(Node<K, V>* node) {
    if (node) {
      return node->size_;
    }
    return 0;
  }
  Node<K, V>* MaximumKey(Node<K, V>* node) {
    if (node != nullptr) {
      while (node->right != nullptr) {
        return this->MaximumKey(node->right);
      }
      return node;
    }
    return nullptr;
  }
  Iterator& OperatorHelper() {
    if (node_ != nullptr) {
      if (node_->left != nullptr) {
        node_ = node_->left;
        while (node_->right != nullptr) {
          node_ = node_->right;
        }
      } else {
        Node<K, V>* parent = node_->parent;
        while (parent != nullptr && node_ == parent->left) {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }
    return *this;
  }

 protected:
  Node<K, V>* node_;
  Node<K, V>* root_;
};

template <typename K>
class SetIterator : public Iterator<K, K> {
  using reference = const K&;

 public:
  SetIterator(Node<K, K>* node = nullptr) : Iterator<K, K>(node) {}
  SetIterator(Node<K, K>* nil, Node<K, K>* root) : Iterator<K, K>(nil, root) {}
  SetIterator& operator=(const SetIterator&) = default;
  SetIterator& operator++() {
    if (this->node_ != nullptr) {
      if (this->node_->right != nullptr) {
        this->node_ = this->node_->right;
        while (this->node_->left != nullptr) {
          this->node_ = this->node_->left;
        }
      } else {
        Node<K, K>* parent = this->node_->parent;
        while (parent != nullptr && this->node_ == parent->right) {
          this->node_ = parent;
          parent = parent->parent;
        }
        this->node_ = parent;
      }
      return *this;
    }
    return *this;
  };
  SetIterator& operator++(int) { return ++(*this); };
  ~SetIterator() = default;
  K& operator*() { return this->node_->key; }
  K& operator->() { return this->node_->key; }
  reference operator*() const { return this->node_->key; }
  // bool operator==(const SetIterator& other) const { return this->node_ ==
  // other->node_; } bool operator!=(const SetIterator& other) const { return
  // this->node_ != other->node_; }
};

template <typename K, typename V>
class ConstIterator : public Iterator<const K, const V> {
 public:
  using Iterator<const K, const V>::Iterator;

  using typename Iterator<const K, const V>::key_type;
  using typename Iterator<const K, const V>::reference;
  using typename Iterator<const K, const V>::pointer;
};

}  // namespace s21
#include "avl_tree.tpp"