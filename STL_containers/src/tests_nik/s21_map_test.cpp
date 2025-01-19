#include <gtest/gtest.h>

#include <iostream>
#include <utility>

#include "../s21_containers.h"

TEST(map, Constructor_Default) {
  s21::map<int, int> Map;
  EXPECT_EQ(Map.size(), 0);
  EXPECT_TRUE(Map.insert(std::pair<int, int>(1, 2)).second);
  EXPECT_TRUE(Map.insert(std::pair<int, int>(2, 3)).second);
  EXPECT_TRUE(Map.insert(std::pair<int, int>(3, 4)).second);
  EXPECT_TRUE(Map.insert(std::pair<int, int>(4, 7)).second);
  EXPECT_EQ(Map[4], 7);
}

TEST(map, Constructor_List_1) {
  s21::map<int, int> Map{
      std::pair<int, int>(1, 2),  std::pair<int, int>(2, 3),
      std::pair<int, int>(3, 4),  std::pair<int, int>(0, 5),
      std::pair<int, int>(4, 2),  std::pair<int, int>(5, 3),
      std::pair<int, int>(6, 4),  std::pair<int, int>(7, 5),
      std::pair<int, int>(8, 2),  std::pair<int, int>(9, 3),
      std::pair<int, int>(10, 4), std::pair<int, int>(11, 5)};
  EXPECT_EQ(Map.size(), 12);
  int ptr = 0;
  for (auto iter = Map.begin(); iter != Map.end(); iter++, ptr++) {
    EXPECT_EQ((*iter).first, ptr);
  }
}

TEST(map, Constructor_List_2) {
  s21::map<int, int> Map{};
  EXPECT_EQ(Map.size(), 0);
}

TEST(map, Constructor_Copy_1) {
  s21::map<int, int> Map0{std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                          std::pair<int, int>(3, 4)};

  s21::map<int, int> Map(Map0);
  EXPECT_EQ(Map.at(1), 2);
  EXPECT_EQ(Map.at(2), 3);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_EQ(Map.size(), 3);
}

TEST(map, Constructor_Copy_2) {
  s21::map<int, int> Map0;

  s21::map<int, int> Map(Map0);
  EXPECT_EQ(Map.size(), 0);
}

TEST(map, Constructor_Move) {
  s21::map<int, int> *Map0 = new s21::map<int, int>{std::pair<int, int>(1, 2),
                                                    std::pair<int, int>(2, 3),
                                                    std::pair<int, int>(3, 4)};

  s21::map<int, int> Map = std::move(*Map0);
  delete Map0;
  EXPECT_EQ(Map.at(1), 2);
  EXPECT_EQ(Map.at(2), 3);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_EQ(Map.size(), 3);
}

TEST(map, Constructor_Move_2) {
  s21::map<int, int> *Map0 = new s21::map<int, int>{std::pair<int, int>(1, 2),
                                                    std::pair<int, int>(2, 3),
                                                    std::pair<int, int>(3, 4)};

  s21::map<int, int> Map;
  Map = std::move(*Map0);
  delete Map0;
  EXPECT_EQ(Map.at(1), 2);
  EXPECT_EQ(Map.at(2), 3);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_EQ(Map.size(), 3);
}

TEST(map, Operator_Copy_1) {
  s21::map<int, int> Map0{std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                          std::pair<int, int>(3, 4)};

  s21::map<int, int> Map = Map0;
  EXPECT_EQ(Map.at(1), 2);
  EXPECT_EQ(Map.at(2), 3);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_EQ(Map.size(), 3);
}

TEST(map, Operator_Copy_2) {
  s21::map<int, int> Map0;

  s21::map<int, int> Map = Map0;
  EXPECT_EQ(Map.size(), 0);
}

TEST(map, Destructor_List_1) {
  s21::map<int, int> *Map = new s21::map<int, int>{
      std::pair<int, int>(1, 2),  std::pair<int, int>(2, 3),
      std::pair<int, int>(3, 4),  std::pair<int, int>(0, 5),
      std::pair<int, int>(4, 2),  std::pair<int, int>(5, 3),
      std::pair<int, int>(6, 4),  std::pair<int, int>(7, 5),
      std::pair<int, int>(8, 2),  std::pair<int, int>(9, 3),
      std::pair<int, int>(10, 4), std::pair<int, int>(11, 5)};
  ASSERT_NO_THROW(delete Map);
}

TEST(map, Access_at) {
  s21::map<int, int> Map{std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                         std::pair<int, int>(3, 4)};
  EXPECT_EQ(Map.at(1), 2);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_THROW(Map.at(4), std::out_of_range);
}

TEST(map, Access_op_eq) {
  s21::map<int, int> Map{std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                         std::pair<int, int>(3, 4)};
  EXPECT_EQ(Map[1], 2);
  EXPECT_EQ(Map[3], 4);
  EXPECT_EQ(Map.size(), 3);
}

TEST(map, Iterator_1) {
  s21::map<int, int> Map;
  EXPECT_TRUE(Map.begin() == Map.end());
  EXPECT_TRUE(++(Map.begin()) == Map.end());
}

TEST(map, Iterator_2) {
  s21::map<int, int> Map;
  EXPECT_TRUE(Map.begin() == Map.end());
  Map[1] = 1;
  EXPECT_EQ((*(Map.begin())).second, 0);
  EXPECT_EQ(Map.begin(), --(Map.end()));
}

TEST(map, Empty_1) {
  s21::map<int, int> Map;
  EXPECT_TRUE(Map.empty());
  Map[1] = 1;
  EXPECT_FALSE(Map.empty());
  Map.erase(Map.begin());
  EXPECT_TRUE(Map.empty());
}

TEST(map, Insert_or_assign_1) {
  s21::map<int, int> Map;
  EXPECT_TRUE(Map.insert(std::pair<int, int>(1, 2)).second);
  EXPECT_TRUE(Map.insert_or_assign({3, 4}).second);
  EXPECT_FALSE(Map.insert_or_assign({1, 5}).second);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_EQ(Map.at(1), 5);
}

TEST(map, Insert) {
  s21::map<int, int> Map;
  EXPECT_TRUE(Map.insert(std::pair<int, int>(1, 2)).second);
  EXPECT_TRUE(Map.insert({3, 4}).second);
  EXPECT_FALSE(Map.insert({1, 5}).second);
  EXPECT_EQ(Map.at(3), 4);
  EXPECT_EQ(Map.at(1), 2);
}

TEST(map, Insert_many_1) {
  s21::map<int, int> Map;
  Map.insert_many(std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                  std::pair<int, int>(3, 4), std::pair<int, int>(0, 5),
                  std::pair<int, int>(4, 2), std::pair<int, int>(5, 3),
                  std::pair<int, int>(6, 4), std::pair<int, int>(7, 5),
                  std::pair<int, int>(8, 2), std::pair<int, int>(9, 3),
                  std::pair<int, int>(10, 4), std::pair<int, int>(11, 5));
  EXPECT_EQ(Map.size(), 12);
  int ptr = 0;
  for (auto iter = Map.begin(); iter != Map.end(); iter++, ptr++) {
    EXPECT_EQ((*iter).first, ptr);
  }
}

TEST(map, Insert_many_2) {
  s21::map<int, int> Map;
  Map.insert_many(std::pair<int, int>(1, 2), std::pair<int, int>(2, 3));
  EXPECT_EQ(Map.size(), 2);
  int ptr = 1;
  for (auto iter = Map.begin(); iter != Map.end(); iter++, ptr++) {
    EXPECT_EQ((*iter).first, ptr);
  }
}

TEST(map, Swap_1) {
  s21::map<int, int> Map1{std::pair<int, int>(1, 2), std::pair<int, int>(2, 3)};
  s21::map<int, int> Map2{std::pair<int, int>(1, 5)};
  Map1.swap(Map2);
  EXPECT_EQ(Map1[1], 5);
  EXPECT_EQ(Map2[1], 2);
  EXPECT_EQ(Map2.at(2), 3);
}

TEST(map, Merge_1) {
  s21::map<int, int> Map1{std::pair<int, int>(1, 2)};
  s21::map<int, int> Map2{std::pair<int, int>(1, 5), std::pair<int, int>(2, 3)};
  Map1.merge(Map2);
  EXPECT_EQ(Map1[1], 2);
  EXPECT_EQ(Map1[2], 3);
}

TEST(map, Contains_1) {
  s21::map<int, int> Map1{std::pair<int, int>(1, 2)};
  EXPECT_TRUE(Map1.contains(1));
  EXPECT_FALSE(Map1.contains(2));
}

TEST(map, Erase_1) {
  s21::map<int, int> *Map = new s21::map<int, int>{
      std::pair<int, int>(1, 2),  std::pair<int, int>(2, 3),
      std::pair<int, int>(3, 4),  std::pair<int, int>(0, 5),
      std::pair<int, int>(4, 2),  std::pair<int, int>(5, 3),
      std::pair<int, int>(6, 4),  std::pair<int, int>(7, 5),
      std::pair<int, int>(8, 2),  std::pair<int, int>(9, 3),
      std::pair<int, int>(10, 4), std::pair<int, int>(11, 5)};
  for (int i = 0; i < 12; i++) {
    Map->erase(Map->begin());
    EXPECT_EQ(Map->size(), 11 - i);
  }
  EXPECT_TRUE(Map->empty());
  delete Map;
}

TEST(map, Erase_2) {
  s21::map<int, int> *Map = new s21::map<int, int>{
      std::pair<int, int>(1, 2),  std::pair<int, int>(2, 3),
      std::pair<int, int>(3, 4),  std::pair<int, int>(0, 5),
      std::pair<int, int>(4, 2),  std::pair<int, int>(5, 3),
      std::pair<int, int>(6, 4),  std::pair<int, int>(7, 5),
      std::pair<int, int>(8, 2),  std::pair<int, int>(9, 3),
      std::pair<int, int>(10, 4), std::pair<int, int>(11, 5)};
  auto iter = --(Map->end());
  for (int i = 0; i < 12; i++) {
    Map->erase(iter--);
    EXPECT_EQ(Map->size(), 11 - i);
  }
  EXPECT_TRUE(Map->empty());
  delete Map;
}

TEST(map, Max_size_1) {
  s21::map<int, int> Map;
  EXPECT_TRUE(Map.max_size() > 2E+06);
}

// TEST(map, Find_1) {
//   s21::map<int, int> Map{std::pair<int, int>(1, 2), std::pair<int, int>(2,
//   3),
//                          std::pair<int, int>(3, 4)};
//   auto it = Map.find(2);
//   EXPECT_EQ(it->first, 2);
//   EXPECT_EQ(it->second, 3);
//   it = Map.find(4);
//   EXPECT_EQ(it, Map.end());
// }

TEST(map, Clear_1) {
  s21::map<int, int> Map{std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                         std::pair<int, int>(3, 4)};
  Map.clear();
  EXPECT_TRUE(Map.empty());
  EXPECT_EQ(Map.size(), 0);
}

TEST(map, Erase_Specific_Case_1) {
  s21::map<int, int> Map;
  Map.insert(std::pair<int, int>(10, 10));
  Map.insert(std::pair<int, int>(20, 20));
  Map.insert(std::pair<int, int>(30, 30));
  Map.insert(std::pair<int, int>(40, 40));
  Map.insert(std::pair<int, int>(50, 50));
  Map.insert(std::pair<int, int>(60, 60));
  Map.insert(std::pair<int, int>(70, 70));
  Map.insert(std::pair<int, int>(80, 80));
  Map.insert(std::pair<int, int>(90, 90));
  Map.insert(std::pair<int, int>(100, 100));

  // Удаление узла, который приведет к выполнению условия
  // if (w->right_child) w->right_child->color = COLOR_BLACK;
  Map.erase(Map.find(50));
}

TEST(map, Erase_Specific_Case_2) {
  s21::map<int, int> Map;
  Map.insert(std::pair<int, int>(10, 10));
  Map.insert(std::pair<int, int>(20, 20));
  Map.insert(std::pair<int, int>(30, 30));
  Map.insert(std::pair<int, int>(40, 40));
  Map.insert(std::pair<int, int>(50, 50));
  Map.insert(std::pair<int, int>(60, 60));
  Map.insert(std::pair<int, int>(70, 70));
  Map.insert(std::pair<int, int>(80, 80));
  Map.insert(std::pair<int, int>(90, 90));
  Map.insert(std::pair<int, int>(100, 100));

  // Удаление узла, который приведет к выполнению условия
  // if (!w->right_child || w->right_child->color == COLOR_BLACK)
  Map.erase(Map.find(60));
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
