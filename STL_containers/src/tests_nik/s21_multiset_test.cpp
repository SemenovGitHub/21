#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "../s21_containers.h"

TEST(Multiset, 1) {
  s21::multiset<double> v = {11, 11, 210};
  std::multiset<double> vc = {11, 11, 210};

  ASSERT_EQ(*v.begin(), *vc.begin());
  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
}

TEST(Multiset, 2) {
  s21::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 3) {
  s21::multiset<double> v;
  std::multiset<double> vc;
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 4) {
  s21::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 5) {
  s21::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  s21::multiset<double> v1 = {10, 20, 30, 40, 50};
  std::multiset<double> vc1 = {10, 20, 30, 40, 50};
  v.swap(v1);
  vc.swap(vc1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 6) {
  s21::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  s21::multiset<double> v1 = {10, 20, 30, 40, 50};
  s21::multiset<double> vc = {-7, 10,  -55, 742, 92, -76, 38, 220, 11,
                              11, 210, 20,  10,  20, 30,  40, 50};
  v.merge(v1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 7) {
  s21::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  std::multiset<double> vc = {-7, 10,  -55, 742, 92,  -76,
                              38, 220, 11,  11,  210, 20};

  ASSERT_EQ(*v.find(20), *vc.find(20));
}

TEST(Multiset, 8) {
  s21::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};

  ASSERT_EQ(v.contains(100), false);
}

TEST(Multiset, 9) {
  s21::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  s21::multiset<double>::iterator x = v.lower_bound(10);
  --x;
  ASSERT_EQ(*x, -7);
}

TEST(Multiset, insert_many) {
  s21::multiset<int> s = {3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  s.insert_many(100, 200, 42, 400);
  EXPECT_EQ(s.size(), 15);
}

TEST(multiset, ConstructorDefault) {
  s21::multiset<int> Set;
  EXPECT_EQ(Set.size(), 0);
}

TEST(multiset, ConstructorList) {
  s21::multiset<int> Set{-1000, 0, 1000, 1000};
  EXPECT_TRUE(Set.contains(0));
  EXPECT_EQ(Set.count(1000), 2);
  EXPECT_EQ(Set.size(), 4);
}

TEST(multiset, ConstructorCopy_1) {
  s21::multiset<int> Set0{-1000, 0, 1000, 1000};
  s21::multiset<int> Set(Set0);
  EXPECT_TRUE(Set.contains(0));
  EXPECT_EQ(Set.count(1000), 2);
  EXPECT_EQ(Set.size(), 4);
}

TEST(multiset, ConstructorCopy_2) {
  s21::multiset<int> Set0{};
  s21::multiset<int> Set(Set0);
  EXPECT_FALSE(Set.contains(0));
  EXPECT_EQ(Set.size(), 0);
}

TEST(multiset, ConstructorCopy_3) {
  s21::multiset<int> *Set0 = new s21::multiset<int>{-1000, 0, 0, 1000};
  s21::multiset<int> Set = *Set0;
  delete Set0;
  EXPECT_TRUE(Set.contains(0));
  EXPECT_EQ(Set.size(), 4);
}

TEST(multiset, ConstructorMove) {
  s21::multiset<int> *Set0 = new s21::multiset<int>{5};
  s21::multiset<int> Set = std::move(*Set0);
  delete Set0;
  EXPECT_TRUE(Set.contains(5));
  EXPECT_EQ(Set.size(), 1);
}

TEST(multiset, ConstructorMove_2) {
  s21::multiset<int> *Set0 = new s21::multiset<int>{5};
  s21::multiset<int> Set;
  Set = std::move(*Set0);
  delete Set0;
  EXPECT_TRUE(Set.contains(5));
  EXPECT_EQ(Set.size(), 1);
}

TEST(multiset, Find_1) {
  s21::multiset<int> Set{-1000, 0, 0, 1000};
  EXPECT_EQ(*(Set.find(0)), 0);
  EXPECT_EQ(Set.size(), 4);
  EXPECT_EQ(Set.find(5), Set.end());
}

TEST(multiset, Begin_1) {
  s21::multiset<int> Set{-1000, 0, 0};
  EXPECT_EQ(*(Set.begin()), -1000);
  EXPECT_EQ(*(++Set.begin()), 0);
  EXPECT_EQ(++(Set.find(0)), --(Set.end()));
  EXPECT_EQ(--(Set.begin()), Set.end());
  EXPECT_NE(Set.begin(), Set.end());
}

TEST(multiset, Empty_1) {
  s21::multiset<int> Set{0, 0, 0};
  EXPECT_EQ(Set.size(), 3);
  EXPECT_FALSE(Set.empty());
}

TEST(multiset, Empty_2) {
  s21::multiset<int> Set{};
  EXPECT_TRUE(Set.empty());
}

TEST(multiset, Erase_1) {
  s21::multiset<int> *Set = new s21::multiset<int>{1, 2, 3, 0, 0, 0, 3, 2, 1};
  for (int i = 0; i < 3; i++) {
    Set->erase(Set->find(0));
  }
  EXPECT_EQ(Set->size(), 6);
  delete Set;
}

TEST(multiset, Content_1) {
  s21::multiset<int> *Set = new s21::multiset<int>{1, 2, 3, 0, 0, 0, 3, 2, 1};
  auto iter = Set->begin();
  int arr[9]{0, 0, 0, 1, 1, 2, 2, 3, 3};
  for (auto i = 0; i < 9; i++) {
    EXPECT_EQ(*iter, arr[i]);
    iter++;
  }
  delete Set;
}

TEST(multiset, Max_size_1) {
  s21::multiset<int> Set;
  EXPECT_GE(Set.max_size(), 1E+6);
}

TEST(multiset, Clear_1) {
  s21::multiset<int> Set{-1000, 0, 0, 1000};
  Set.clear();
  EXPECT_FALSE(Set.contains(0));
  EXPECT_EQ(Set.size(), 0);
}

TEST(multiset, Swap_1) {
  s21::multiset<int> Set1{-1000, 0, 1000};
  s21::multiset<int> Set2{5, 6, 6};
  Set1.swap(Set2);
  EXPECT_TRUE(Set2.contains(0));
  EXPECT_EQ(Set1.count(6), 2);
  EXPECT_EQ(Set1.size(), 3);
  EXPECT_EQ(Set2.size(), 3);
}

TEST(multiset, Merge_1) {
  s21::multiset<int> Set1{-1000, 0, 1000};
  s21::multiset<int> Set2{0, 0};
  Set1.merge(Set2);
  EXPECT_EQ(Set1.count(0), 3);
  EXPECT_EQ(Set1.size(), 5);
  EXPECT_EQ(Set2.size(), 0);
}

TEST(multiset, Insert_many_1) {
  s21::multiset<int> Set1{-1000, 0, 1000};
  Set1.insert_many(5, 6);
  EXPECT_TRUE(Set1.contains(0));
  EXPECT_TRUE(Set1.contains(6));
  EXPECT_EQ(Set1.size(), 5);
}

TEST(multiset, Insert_many_2) {
  s21::multiset<int> Set1{-1000, 0, 1000};
  Set1.insert_many(10, 11);
  EXPECT_TRUE(Set1.contains(0));
  EXPECT_EQ(Set1.size(), 5);
}

TEST(multiset, Equal_range_1) {
  s21::multiset<int> *Set =
      new s21::multiset<int>{1, 2, 3, 0, 0, 0, 3, 2, 1, 4};
  auto iter = Set->equal_range(0).first;
  auto iter2 = Set->equal_range(0).second;
  EXPECT_FALSE(iter == iter2);
  ++iter;
  ++iter;
  ++iter;
  EXPECT_TRUE(iter == iter2);
  delete Set;
}

TEST(multiset, Equal_range_2) {
  s21::multiset<int> *Set =
      new s21::multiset<int>{1, 2, 3, 0, 0, 0, 3, 2, 1, 4};
  auto iter = Set->equal_range(4).first;
  auto iter2 = Set->equal_range(4).second;
  EXPECT_FALSE(iter == iter2);
  EXPECT_TRUE(iter2 == Set->end());
  delete Set;
}

TEST(multiset, Equal_range_3) {
  s21::multiset<int> *Set =
      new s21::multiset<int>{1, 2, 3, 0, 0, 0, 3, 2, 1, 4};
  auto iter = Set->equal_range(2).first;
  auto iter2 = Set->equal_range(2).second;
  EXPECT_EQ(*iter2, 3);
  delete Set;
}
