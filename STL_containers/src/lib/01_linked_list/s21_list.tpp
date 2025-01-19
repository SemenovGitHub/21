#include "s21_list.h"

using namespace s21;

// Constructors
template <typename T>
s21_list<T>::s21_list() : head_(nullptr), tail_(nullptr), size_(0){};

template <typename T>
s21_list<T>::s21_list(size_type size) : s21_list() {
  for (size_type i = 0; i < size; i++) {
    push_back(0);
  }
}

template <typename T>
s21_list<T>::~s21_list() {
  clear();
}

template <typename T>
s21_list<T>::s21_list(const s21_list &l) : s21_list() {
  NODE *tmp_src = l.head_;

  while (tmp_src) {
    push_back(tmp_src->value);
    tmp_src = tmp_src->next;
  }
}

template <typename T>
s21_list<T>::s21_list(std::initializer_list<T> const &items) : s21_list() {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
s21_list<T>::s21_list(s21_list &&l) : s21_list() {
  while (l.head_) {
    push_back(l.head_->value);
    l.pop_front();
  };
}

// overloads

template <typename T>
s21_list<T> &s21_list<T>::operator=(s21_list &&l) {
  clear();
  if (this != &l) {
    while (l.head_) {
      push_back(l.head_->value);
      l.pop_front();
    };
  }
  return *this;
}

// functions
template <typename T>
void s21_list<T>::push_back(const_reference val) {
  NODE *new_node = new NODE;
  new_node->value = val;
  new_node->prev = tail_;
  new_node->next = nullptr;

  if (tail_)
    tail_->next = new_node;
  else
    head_ = new_node;
  tail_ = new_node;
  size_++;
}

template <typename T>
void s21_list<T>::push_front(const_reference val) {
  NODE *new_node = new NODE;
  new_node->value = val;
  new_node->prev = nullptr;
  new_node->next = head_;

  if (head_)
    head_->prev = new_node;
  else
    tail_ = new_node;
  head_ = new_node;
  size_++;
}

template <typename T>
void s21_list<T>::pop_front() {
  if (head_) {
    NODE *next = head_->next;
    if (next) next->prev = nullptr;
    delete head_;
    head_ = next;
    size_--;
    if (!size_) tail_ = nullptr;
  } else
    throw std::out_of_range("You tried to pop empty class");
}

template <typename T>
void s21_list<T>::pop_back() {
  if (tail_) {
    NODE *prev = tail_->prev;
    if (prev) prev->next = nullptr;
    delete tail_;
    tail_ = prev;
    size_--;
    if (!size_) head_ = nullptr;
  } else
    throw std::out_of_range("You tried to pop empty class");
}
template <typename T>
const T &s21_list<T>::back() {
  if (tail_)
    return tail_->value;
  else
    throw std::out_of_range("You tried to get uninitializate value");
};

template <typename T>
const T &s21_list<T>::front() {
  return head_->value;
};

template <typename T>
size_t s21_list<T>::size() const {
  return size_;
};

template <typename T>
typename s21_list<T>::iterator s21_list<T>::begin() {
  return iterator(head_, *this);
}

template <typename T>
typename s21_list<T>::iterator s21_list<T>::end() {
  return iterator(nullptr, *this);
}

template <typename T>
typename s21_list<T>::const_iterator s21_list<T>::cbegin() const {
  return const_iterator(head_, *this);
}

template <typename T>
typename s21_list<T>::const_iterator s21_list<T>::cend() const {
  return const_iterator(nullptr, *this);
}

template <typename T>
bool s21_list<T>::empty() {
  return (!tail_ && !head_ && size_ == 0);
}
template <typename T>
void s21_list<T>::clear() {
  while (head_) {
    pop_front();
  }
}

template <typename T>
typename s21_list<T>::iterator s21_list<T>::insert(s21_list<T>::iterator pos,
                                                   const T &value) {
  NODE *new_node = new NODE;
  new_node->value = value;

  if (pos.current_ != nullptr) {
    new_node->next = pos.current_;
    new_node->prev = pos.current_->prev;

    if (pos.current_->prev)
      pos.current_->prev->next = new_node;
    else
      head_ = new_node;

    pos.current_->prev = new_node;
  } else {
    new_node->prev = tail_;
    new_node->next = nullptr;
    if (tail_)
      tail_->next = new_node;
    else
      head_ = new_node;

    tail_ = new_node;
  }

  pos.current_ = new_node;  // Устанавливаем позицию на новый узел
  size_++;
  return pos;
}

template <typename T>
void s21_list<T>::erase(typename s21_list<T>::iterator it) {
  if (it.current_) {
    if (it.current_->prev) it.current_->prev->next = it.current_->next;
    if (it.current_->next) it.current_->next->prev = it.current_->prev;
    if (it.current_ == tail_) {
      tail_ = it.current_->prev;
      tail_->next = nullptr;
    }
    delete it.current_;
    size_--;
  }
}

template <typename T>
void s21_list<T>::swap(s21_list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void s21_list<T>::sort() {
  auto it_1 = begin();
  auto it_2 = begin();

  while (it_1 != end()) {
    it_2++;
    while (it_2 != end()) {
      if (*it_1 > *it_2) {
        std::swap(it_1.current_->value, it_2.current_->value);
      }
      it_2++;
    }
    it_2 = ++it_1;
  }
}

template <typename T>
void s21_list<T>::merge(s21_list &other) {
  auto it_src = begin();
  auto it_dst = other.begin();
  while (it_dst != other.end()) {
    if (it_src.current_) {
      while (it_src.current_ && *it_src <= *it_dst) ++it_src;
    }
    insert(it_src, *it_dst);
    it_dst++;
    other.pop_front();
  }
}

template <typename T>
void s21_list<T>::reverse() {
  if (tail_ && head_) {
    for (auto it = begin(); it.current_ != nullptr;
         it.current_ = it.current_->prev) {
      std::swap(it.current_->next, it.current_->prev);
    }
    std::swap(tail_, head_);
  }
}

template <typename T>
void s21_list<T>::unique() {
  auto it_tmp = begin();
  auto it_tmp_2 = begin();
  for (auto it = begin(); it != end(); it++) {
    it_tmp++;
    while (it_tmp != end() && *it == *it_tmp) {
      it_tmp_2 = it_tmp;
      it_tmp_2++;
      erase(it_tmp);
      it_tmp = it_tmp_2;
    }
    it_tmp = it;
    it_tmp++;
  }
}

template <typename T>
void s21_list<T>::splice(const_iterator pos, s21_list &other) {
  iterator it = begin();
  it = pos;
  if (tail_ && head_) {
    if (other.head_ && other.tail_) {
      if (it.current_ == nullptr) {
        it--;
        it.current_->next = other.head_;
        other.head_->prev = it.current_;
        tail_ = other.tail_;
      } else {
        if (it.current_ != head_) {
          auto it_2 = it;
          it_2--;
          it_2.current_->next = other.head_;
          other.head_->prev = it_2.current_;
        } else
          head_ = other.head_;
        it.current_->prev = other.tail_;
        other.tail_->next = it.current_;
      }
    }
  }
  size_ += other.size_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
size_t s21_list<T>::max_size() {
  return std::numeric_limits<T>::max();
}

template <typename T>
template <typename... Args>
typename s21_list<T>::iterator s21_list<T>::insert_many(const_iterator pos,
                                                        Args &&...args) {
  iterator it;
  it = pos;
  for (const auto &elem : {args...}) {
    it = insert(it, elem);
    if (it.current_ != tail_->next) it++;
  }
  return it;
}

template <typename T>
template <typename... Args>
void s21_list<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}

template <typename T>
template <typename... Args>
void s21_list<T>::insert_many_front(Args &&...args) {
  insert_many(cbegin(), std::forward<Args>(args)...);
}
