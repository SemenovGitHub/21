#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

// Тестовый случай для pop_back
TEST(ListTest, PopBack1) {
  s21::s21_list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  myList.pop_back();
  EXPECT_EQ(myList.back(), 2);
  myList.pop_back();
  EXPECT_EQ(myList.back(), 1);
  myList.pop_back();
  EXPECT_TRUE(myList.empty());
  EXPECT_THROW(myList.pop_back(), std::out_of_range);
}

TEST(ListTest, clear) {
  s21_list<int> data{1, 2, 3};
  data.clear();
  EXPECT_TRUE(data.empty());
}

// Тестовый случай для insert
TEST(ListTest, Insert1) {
  s21::s21_list<int> myList{1, 2, 3};
  std::list<int> data{1, 2, 3};
  auto it_d = data.insert(data.begin(), 0);

  auto it = myList.insert(myList.begin(), 0);
  EXPECT_EQ(*it, *it_d);

  it_d = data.insert(data.end(), 4);
  it = myList.insert(myList.end(), 4);
  EXPECT_EQ(*it, *it_d);

  it_d = data.insert(++data.begin(), 5);
  it = myList.insert(++myList.begin(), 5);
  EXPECT_EQ(*it, *it_d);

  it_d = data.begin();
  it = myList.begin();
  while (it != myList.end()) {
    ASSERT_EQ(*it, *it_d);
    it_d++;
    it++;
  }
  myList.clear();
  myList.insert(myList.begin(), 0);
  ASSERT_EQ(myList.front(), 0);
}

TEST(ListTest, DefaultConstructor) {
  s21::s21_list<int> myList;
  EXPECT_TRUE(myList.empty());
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, InitializerListConstructor) {
  s21::s21_list<int> myList = {1, 2, 3};
  EXPECT_FALSE(myList.empty());
  EXPECT_EQ(myList.size(), 3);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);
}

TEST(ListTest, InsertMany1) {
  s21::s21_list<int> l;
  l.push_back(1);
  l.push_back(4);
  auto it = l.insert_many(++(l.cbegin()), 2, 3);
  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(*it, 4);
}

TEST(ListTest, PopFrontEmpty1) {
  s21::s21_list<int> l;
  EXPECT_THROW(l.pop_front(), std::out_of_range);
}

TEST(ListTest, PopBackEmpty1) {
  s21::s21_list<int> l;
  EXPECT_THROW(l.pop_back(), std::out_of_range);
}
TEST(ListTest, SWAP) {
  s21::s21_list<int> data_1{1, 2, 3};
  s21::s21_list<int> data_2{4, 5, 6};
  int i = 1;
  data_1.swap(data_2);
  for (auto it = data_2.begin(); it != data_2.end(); it++, i++) {
    ASSERT_EQ(*it, i);
  }
  for (auto it = data_1.begin(); it != data_1.end(); it++, i++) {
    ASSERT_EQ(*it, i);
  }
}

TEST(ListTest, CopyConstructor) {
  s21::s21_list<int> original = {1, 2, 3};
  s21::s21_list<int> copy(original);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.front(), 1);
  EXPECT_EQ(copy.back(), 3);
}

TEST(ListTest, MoveConstructor) {
  s21::s21_list<int> original = {1, 2, 3};
  s21::s21_list<int> moved(std::move(original));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(ListTest, PushBack) {
  s21::s21_list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 2);
}

TEST(ListTest, PushFront) {
  s21::s21_list<int> myList;
  myList.push_front(1);
  myList.push_front(2);
  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), 2);
  EXPECT_EQ(myList.back(), 1);
}

TEST(ListTest, PopBack) {
  s21::s21_list<int> myList = {1, 2, 3};
  myList.pop_back();
  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.back(), 2);
}

TEST(ListTest, PopFront) {
  s21::s21_list<int> myList = {1, 2, 3};
  myList.pop_front();
  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), 2);
}

TEST(ListTest, Erase) {
  s21::s21_list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  ++it;
  myList.erase(it);
  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);
}

TEST(ListTest, sort) {
  s21_list<int> data{5, 6, 3, 1, 2, 4};
  int i = 1;
  data.sort();
  for (auto it = data.begin(); it != data.end(); it++, i++) {
    ASSERT_EQ(*it, i);
  }
}

TEST(ListTest, merge) {
  s21_list<int> data{1, 1, 2, 3};
  s21_list<int> data_2{2, 4};
  data.merge(data_2);

  std::list<int> data_orig{1, 1, 2, 3};
  std::list<int> data_2_orig{2, 4};
  data_orig.merge(data_2_orig);

  auto it = data.begin();
  auto it_orig = data_orig.begin();

  ASSERT_EQ(data.size(), data_orig.size());

  for (; it != data.end(); ++it_orig, ++it) {
    ASSERT_EQ(*it, *it_orig);
  }
}

TEST(ListTest, reverse) {
  s21_list<int> data{1, 2, 3};
  data.reverse();
  int i = 3;
  for (auto it = data.begin(); it != data.end(); it++, i--) {
    ASSERT_EQ(i, *it);
  }
}

TEST(ListTest, unique) {
  s21_list<int> data{1, 1, 2, 3, 2};
  data.unique();
  std::list<int> data_orig{1, 1, 2, 3, 2};
  data_orig.unique();

  auto it = data.begin();
  auto it_orig = data_orig.begin();

  ASSERT_EQ(data.size(), data_orig.size());

  for (; it != data.end(); ++it_orig, ++it) {
    ASSERT_EQ(*it, *it_orig);
  }
}
TEST(ListTest, SpliceAllPositions) {
  s21_list<int> list1;
  s21_list<int> list2;

  // Инициализация list1 и list2
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  list2.push_back(4);
  list2.push_back(5);

  auto it = list1.cbegin();
  list1.splice(it, list2);

  EXPECT_EQ(list1.size(), 5);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_EQ(*list1.begin(), 4);  // Первый элемент должен быть 4
  EXPECT_EQ(*(++list1.begin()), 5);  // Второй элемент должен быть 5
  EXPECT_EQ(*(++(++list1.begin())), 1);  // Третий элемент должен быть 1

  // Переинициализируем list2 для следующей операции
  list2.push_back(0);
  list2.push_back(0);
  it = list1.cbegin();
  list1.splice(++list1.cbegin(), list2);
  EXPECT_EQ(*it, 4);  // Первый элемент должен быть 4005123
  EXPECT_EQ(*(it++), 0);
  EXPECT_EQ(*(it++), 0);
  EXPECT_EQ(*(it++), 5);

  // 3. Splice в конец
  list2.push_back(0);
  list2.push_back(0);
  it = list1.cend();
  list1.splice(it, list2);

  EXPECT_EQ(list1.size(), 9);
  EXPECT_EQ(list1.back(), 0);
}
TEST(ListTest, max_size) {
  s21_list<int> data;
  std::list<int> data_orig;
  ASSERT_EQ(data.max_size(), std::numeric_limits<int>::max());
}

TEST(ListTest, InsertManyBack) {
  s21::s21_list<int> myList = {1, 2};
  myList.insert_many_back(3, 4);
  EXPECT_EQ(myList.size(), 4);
  EXPECT_EQ(myList.back(), 4);
}

TEST(ListTest, InsertManyFront) {
  s21::s21_list<int> myList = {3, 4};
  myList.insert_many_front(1, 2);

  EXPECT_EQ(myList.size(), 4);

  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);

  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(ListTest, InsertMany) {
  s21::s21_list<int> myList = {1, 4};
  auto it = myList.cbegin();
  ++it;
  myList.insert_many(it, 2, 3);
  EXPECT_EQ(myList.size(), 4);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 4);
  it = myList.cbegin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, additon_tests) {
  s21::s21_list<int> list = {1, 2, 3};
  auto it = list.end();
  EXPECT_THROW(*it, std::out_of_range);
  it--;
  ASSERT_EQ(*it, 3);
  list.erase(list.end()--);
  ASSERT_EQ(list.back(), 2);
  list.clear();
  EXPECT_THROW(list.back(), std::out_of_range);
  EXPECT_THROW(list.begin()--, std::out_of_range);
  EXPECT_THROW(list.end()++, std::out_of_range);
  EXPECT_THROW(list.cbegin()--, std::out_of_range);
  EXPECT_THROW(list.cend()++, std::out_of_range);
  EXPECT_THROW(*list.cend(), std::out_of_range);
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(*(list.cend()--), 2);
  EXPECT_EQ(*((list.cend()--)--), 1);
}