#pragma once

#include "../../s21_containers.h"

namespace s21 {

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class s21_list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  friend ListConstIterator<T>;
  friend ListIterator<T>;

 protected:
  struct NODE {
    value_type value;
    NODE *next;
    NODE *prev;
  };

 public:
  // Constructors
  s21_list();                   // Default constructor +
  s21_list(size_type n);        // Constructor with size +
  ~s21_list();                  // Destructor +
  s21_list(const s21_list &l);  // Copy constructor +
  s21_list(s21_list &&l);       // Move constructor +
  s21_list(std::initializer_list<value_type> const
               &items);  // Initializer list constructor +

  // Move assignment operator
  s21_list &operator=(s21_list &&l);  //

  // Iterators
  iterator begin();               //
  iterator end();                 //
  const_iterator cbegin() const;  //
  const_iterator cend() const;    //

  // Methods to modify the list
  void clear();                                          //
  iterator insert(iterator pos, const_reference value);  //
  void erase(iterator pos);                              //
  void push_back(const_reference value);                 //
  void pop_back();                                       //
  void push_front(const_reference value);                //
  void pop_front();                                      //
  void swap(s21_list &other);                            //
  void merge(s21_list &other);                           //
  void splice(const_iterator pos, s21_list &other);      //
  void reverse();                                        //
  void unique();                                         //
  void sort();                                           //
  bool empty();                                          //

  const_reference back();   //
  const_reference front();  //
  size_type max_size();     //
  size_type size() const;   //

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  NODE *head_;
  NODE *tail_;
  size_type size_;
};

template <typename T>
class ListIterator {
  friend s21_list<T>;
  friend ListConstIterator<T>;
  using IT_NODE_ = typename s21_list<T>::NODE *;

 private:
  IT_NODE_ current_;

 public:
  ListIterator();
  ListIterator(const ListIterator &i);  // copy
  ~ListIterator();
  ListIterator(IT_NODE_ NODE, s21_list<T> &list);

  typename s21_list<T>::reference operator*();
  ListIterator &operator++();
  ListIterator &operator++(int);
  ListIterator &operator--();
  ListIterator &operator--(int);
  bool operator!=(const ListIterator &other) const;
  bool operator==(const ListIterator &other) const;
  ListIterator &operator=(ListConstIterator<T> &other);
  ListIterator &operator=(const ListIterator &other);

 protected:
  IT_NODE_ head_exemp_;
  IT_NODE_ tail_exemp_;
};

template <typename T>
class ListConstIterator {
  friend s21_list<T>;
  friend ListIterator<T>;
  using IT_NODE_ = typename s21_list<T>::NODE *;

 private:
  IT_NODE_ current_;

 public:
  ListConstIterator();
  ListConstIterator(const ListConstIterator &i);  // copy
  ~ListConstIterator();
  ListConstIterator(IT_NODE_ NODE, const s21_list<T> &list);

  ListConstIterator(const IT_NODE_ *node);
  typename s21_list<T>::const_reference operator*() const;
  ListConstIterator &operator++();
  ListConstIterator &operator++(int);
  ListConstIterator &operator--();
  ListConstIterator &operator--(int);
  bool operator!=(const ListConstIterator &other) const;
  bool operator==(const ListConstIterator &other) const;
  ListConstIterator &operator=(const ListConstIterator<T> &other);

 protected:
  IT_NODE_ head_exemp_;
  IT_NODE_ tail_exemp_;
};

}  // namespace s21

#include "s21_ListIterator.tpp"
#include "s21_list.tpp"