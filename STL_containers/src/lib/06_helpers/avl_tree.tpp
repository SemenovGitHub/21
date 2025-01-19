#include "avl_tree.h"

namespace s21 {

template <typename K, typename V>
AVLTree<K, V>::AVLTree() : root(nullptr), nil(nullptr), inserted(false) {}

template <typename K, typename V>
AVLTree<K, V>::AVLTree(const AVLTree& other)
    : root(CopyTree(other.GetRoot())) {}

template <typename K, typename V>
AVLTree<K, V>& AVLTree<K, V>::operator=(AVLTree&& other) {
  if (this != &other) {
    Clear(root);
    root = std::exchange(other.root, nullptr);
  }
  return *this;
}

template <typename K, typename V>
int AVLTree<K, V>::Height(Node<K, V>* node) const {
  return node ? node->height : 0;
}

template <typename K, typename V>
int AVLTree<K, V>::BalanceFactor(Node<K, V>* node) const {
  return node ? Height(node->left) - Height(node->right) : 0;
}

template <typename K, typename V>
void AVLTree<K, V>::UpdateHeight(Node<K, V>* node) {
  int hl = Height(node->left);
  int hr = Height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::RotateRight(Node<K, V>* node) {
  Node<K, V>* newRoot = node->left;
  node->left = newRoot->right;
  if (newRoot->right) {
    newRoot->right->parent = node;
  }
  newRoot->right = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;
  UpdateHeight(newRoot);
  UpdateHeight(node);
  return newRoot;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::RotateLeft(Node<K, V>* node) {
  Node<K, V>* newRoot = node->right;
  node->right = newRoot->left;
  if (newRoot->left) {
    newRoot->left->parent = node;
  }
  newRoot->left = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;
  UpdateHeight(newRoot);
  UpdateHeight(node);
  return newRoot;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::Balance(Node<K, V>* node) {
  UpdateHeight(node);
  if (BalanceFactor(node) == 2) {
    if (BalanceFactor(node->right) < -1) {
      node->left = RotateLeft(node->left);
      UpdateSize(node->left);
    }
    node = RotateRight(node);
    UpdateSize(node);
  } else if (BalanceFactor(node) == -2) {
    if (BalanceFactor(node->left) > 1) {
      node->right = RotateRight(node->right);
      UpdateSize(node->right);
    }
    node = RotateLeft(node);
    UpdateSize(node);
  }
  UpdateSize(node);
  return node;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::Insert(Node<K, V>* node, const K& key,
                                  const V& value, Node<K, V>* parent) {
  if (!node) {
    node = new Node<K, V>(key, value);
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    inserted = true;
    return Balance(node);
  }
  if (key < node->key) {
    node->left = Insert(node->left, key, value, node);
  } else if (key > node->key) {
    node->right = Insert(node->right, key, value, node);
  } else {
    node->value = value;
    inserted = false;
  }
  return Balance(node);
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::InsertMultiSet(Node<K, V>* node, const K& key,
                                          const V& value, Node<K, V>* parent) {
  if (!node) {
    node = new Node<K, V>(key, value);
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    inserted = true;
    return Balance(node);
  }
  if (key < node->key) {
    node->left = InsertMultiSet(node->left, key, value, node);
    inserted = true;
  } else if (key >= node->key) {
    node->right = InsertMultiSet(node->right, key, value, node);
    inserted = true;
  }
  return Balance(node);
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::FindMin(Node<K, V>* node) const {
  return !node->left ? node : FindMin(node->left);
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::RemoveMin(Node<K, V>* node) {
  if (!node->left) return node->right;
  node->left = RemoveMin(node->left);
  return Balance(node);
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::Remove(Node<K, V>* node, const K& key) {
  if (!node) return nullptr;
  if (key < node->key) {
    node->left = Remove(node->left, key);
    if (node->left) node->left->parent = node;
  } else if (key > node->key) {
    node->right = Remove(node->right, key);
    if (node->right) node->right->parent = node;
  } else {
    Node<K, V>* left = node->left;
    Node<K, V>* right = node->right;
    delete node;
    if (!right) return left;
    if (!left) return right;
    Node<K, V>* min = FindMin(right);
    min->right = RemoveMin(right);
    if (min->right) min->right->parent = min;
    min->left = left;
    if (min->left) min->left->parent = min;
    min->size_--;
    min->parent = nullptr;
    UpdateHeight(min);
    return Balance(min);
  }
  node->size_--;
  UpdateHeight(node);
  return Balance(node);
}

template <typename K, typename V>
AVLTree<K, V>::~AVLTree() {
  Clear(root);
}

template <typename K, typename V>
void AVLTree<K, V>::Clear(Node<K, V>* node) {
  if (node != nullptr) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
  root = nullptr;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::Search(const K& key) const {
  Node<K, V>* node = root;
  while (node != nullptr) {
    if (key < node->key) {
      node = node->left;
    } else if (key > node->key) {
      node = node->right;
    } else {
      return node;
    }
  }
  return nullptr;
}

template <typename K, typename V>
void AVLTree<K, V>::SetRoot(Node<K, V>* root) {
  this->root = root;
  if (this->root != nullptr) {
    this->root->parent = nullptr;
  }
}

template <typename K, typename V>
void AVLTree<K, V>::UpdateSize(Node<K, V>* node) {
  if (node) {
    node->size_ = 1 + Size(node->left) + Size(node->right);
    UpdateSize(node->left);
    UpdateSize(node->right);
  }
}

template <typename K, typename V>
int AVLTree<K, V>::Size(Node<K, V>* node) const {
  return node ? node->size_ : 0;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::Insert(const K& key, const V& value) {
  root = Insert(root, key, value, nullptr);
  return root;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::InsertMultiSet(const K& key, const V& value) {
  root = InsertMultiSet(root, key, value, nullptr);
  return root;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::Remove(const K& key) {
  root = Remove(root, key);
  return root;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::GetRoot() const {
  return this->root;
}

template <typename K, typename V>
void AVLTree<K, V>::Swap(AVLTree<K, V>& other) {
  std::swap(root, other.root);
}

template <typename K, typename V>
bool AVLTree<K, V>::GetInserted() {
  return inserted;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::CopyTree(Node<K, V>* node) {
  if (node == nullptr) {
    return nullptr;
  }
  Node<K, V>* new_node = new Node<K, V>(node->key, node->value);
  new_node->size_ = node->size_;
  new_node->left = CopyTree(node->left);
  new_node->right = CopyTree(node->right);
  new_node->parent = node->parent;
  return new_node;
}

template <typename K, typename V>
Node<K, V>* AVLTree<K, V>::MaximumKey(Node<K, V>* node) const {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

}  // namespace s21
