#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

template <typename T>
using Vector = s21::s21_vector<T>;

TEST(VectorDefaultConstructor, test_1) {
  Vector<int> vector;
  std::vector<int> original;
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.data(), original.data());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorConstructor, test_1) {
  Vector<int> vector(10);
  std::vector<int> original(10);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorConstructorWithParams, test_1) {
  Vector<int> vector{1, 455, -5, 0, 3};
  std::vector<int> original{1, 455, -5, 0, 3};
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
  EXPECT_EQ(*(vector.data()), *(original.data()));
}

TEST(VectorConstructorCopy, test_1) {
  Vector<int> vector{15, 70, -1};
  std::vector<int> original{15, 70, -1};
  Vector<int> vector_copy(vector);
  std::vector<int> original_copy(original);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
  EXPECT_EQ(vector.at(0), original.at(0));
  EXPECT_EQ(vector.at(1), original.at(1));
  EXPECT_EQ(vector.at(2), original.at(2));
  EXPECT_EQ(vector_copy.size(), original_copy.size());
  EXPECT_EQ(vector_copy.capacity(), original_copy.capacity());
  EXPECT_EQ(vector_copy.empty(), original_copy.empty());
  EXPECT_EQ(vector_copy.at(0), original_copy.at(0));
  EXPECT_EQ(vector_copy.at(1), original_copy.at(1));
  EXPECT_EQ(vector_copy.at(2), original_copy.at(2));
}

TEST(VectorConstructorCopy, test_2) {
  Vector<int> vector{15, 70, -1};
  std::vector<int> original{15, 70, -1};
  Vector<int> vector_copy = vector;
  std::vector<int> original_copy = original;
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
  EXPECT_EQ(vector.at(0), original.at(0));
  EXPECT_EQ(vector.at(1), original.at(1));
  EXPECT_EQ(vector.at(2), original.at(2));
  EXPECT_EQ(vector_copy.size(), original_copy.size());
  EXPECT_EQ(vector_copy.capacity(), original_copy.capacity());
  EXPECT_EQ(vector_copy.empty(), original_copy.empty());
  EXPECT_EQ(vector_copy.at(0), original_copy.at(0));
  EXPECT_EQ(vector_copy.at(1), original_copy.at(1));
  EXPECT_EQ(vector_copy.at(2), original_copy.at(2));
}

TEST(VectorConstructorMove, test_1) {
  Vector<int> vector{15, 70, -1};
  std::vector<int> original{15, 70, -1};
  Vector<int> vector_move(std::move(vector));
  std::vector<int> original_move(std::move(original));
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
  EXPECT_EQ(vector_move.size(), original_move.size());
  EXPECT_EQ(vector_move.capacity(), original_move.capacity());
  EXPECT_EQ(vector_move.empty(), original_move.empty());
  EXPECT_EQ(vector_move.at(0), original_move.at(0));
  EXPECT_EQ(vector_move.at(1), original_move.at(1));
  EXPECT_EQ(vector_move.at(2), original_move.at(2));
}

TEST(VectorDestructor, test_1) {
  Vector<int> vector{1, 2, 3, 4, 5};
  vector.~s21_vector();
  EXPECT_EQ(0, vector.size());
  EXPECT_EQ(0, vector.capacity());
  EXPECT_EQ(0, vector.data());
}

TEST(VectorEqOperatorMove, test_1) {
  Vector<int> vector{15, 70, -1};
  std::vector<int> original{15, 70, -1};
  Vector<int> vector_move = std::move(vector);
  std::vector<int> original_move = std::move(original);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
  EXPECT_EQ(vector_move.size(), original_move.size());
  EXPECT_EQ(vector_move.capacity(), original_move.capacity());
  EXPECT_EQ(vector_move.empty(), original_move.empty());
  EXPECT_EQ(vector_move.at(0), original_move.at(0));
  EXPECT_EQ(vector_move.at(1), original_move.at(1));
  EXPECT_EQ(vector_move.at(2), original_move.at(2));
}

TEST(VectorElementAccess, test_1) {
  Vector<double> vector{1.1, 455., -5.33, 0.09876, 3.7};
  std::vector<double> original{1.1, 455., -5.33, 0.09876, 3.7};
  EXPECT_DOUBLE_EQ(vector.at(0), original.at(0));
  EXPECT_DOUBLE_EQ(vector.at(1), original.at(1));
  EXPECT_DOUBLE_EQ(vector.at(2), original.at(2));
  EXPECT_DOUBLE_EQ(vector[3], original[3]);
  EXPECT_DOUBLE_EQ(vector[4], original[4]);
  EXPECT_THROW(vector.at(5), std::out_of_range);
}

TEST(VectorFrontBack, test_1) {
  Vector<double> vector{1.1, 455., -5.33, 0.09876, 3.7};
  std::vector<double> original{1.1, 455., -5.33, 0.09876, 3.7};
  EXPECT_DOUBLE_EQ(vector.front(), original.front());
  EXPECT_DOUBLE_EQ(vector.back(), original.back());
}

TEST(VectorFrontBack, test_2) {
  Vector<double> vector;
  EXPECT_THROW(vector.front(), std::out_of_range);
  EXPECT_THROW(vector.back(), std::out_of_range);
}

TEST(VectorReserve, test_1) {
  Vector<int> vector{5, 6, 7, 8, 8, 0};
  std::vector<int> original{5, 6, 7, 8, 8, 0};
  vector.reserve(50);
  original.reserve(50);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.back(), original.back());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorReserve, test_2) {
  Vector<int> vector{5, 6, 7, 8, 8, 0};
  std::vector<int> original{5, 6, 7, 8, 8, 0};
  vector.reserve(5);
  original.reserve(5);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.back(), original.back());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorMaxSize, test_1) {
  Vector<int> vector;
  std::vector<int> original;
  EXPECT_EQ(vector.max_size(), original.max_size());
}

TEST(VectorShrinkToFit, test_1) {
  Vector<int> vector{5, 6, 7, 8, 8, 0};
  std::vector<int> original{5, 6, 7, 8, 8, 0};
  vector.reserve(50);
  original.reserve(50);
  vector.shrink_to_fit();
  original.shrink_to_fit();
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
}

TEST(VectorShrinkToFit, test_2) {
  Vector<int> vector;
  std::vector<int> original;
  vector.reserve(5);
  original.reserve(5);
  vector.shrink_to_fit();
  original.shrink_to_fit();
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
}

TEST(VectorClear, test_1) {
  Vector<int> vector{5, 6, 7, 8, 8, 0};
  std::vector<int> original{5, 6, 7, 8, 8, 0};
  vector.clear();
  original.clear();
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorClear, test_2) {
  Vector<int> vector;
  std::vector<int> original;
  vector.clear();
  original.clear();
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorInsert, test_1) {
  Vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  auto it_vector = vector.insert(vector.begin() + 1, 5);
  auto it_original = original.insert(original.begin() + 1, 5);
  for (int i = 0; i < 4; ++i) EXPECT_EQ(vector.at(i), original.at(i));
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(*it_vector, *it_original);
}

TEST(VectorInsert, test_2) {
  Vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  auto it_vector = vector.insert(vector.end(), 5);
  auto it_original = original.insert(original.end(), 5);
  for (int i = 0; i < 4; ++i) EXPECT_EQ(vector.at(i), original.at(i));
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(*it_vector, *it_original);
}

TEST(VectorInsert, test_3) {
  Vector<int> vector{1, 2, 3};
  EXPECT_THROW(vector.insert(vector.end() + 1, 5), std::out_of_range);
  EXPECT_THROW(vector.insert(vector.begin() - 1, 5), std::out_of_range);
}

TEST(VectorErase, test_1) {
  Vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  EXPECT_EQ(vector.at(0), original.at(0));
  EXPECT_EQ(vector.at(1), original.at(1));
  EXPECT_THROW(vector.at(4), std::out_of_range);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
}

TEST(VectorErase, test_2) {
  Vector<int> vector{1, 2, 3};
  EXPECT_THROW(vector.erase(vector.end()), std::out_of_range);
}

TEST(VectorErase, test_3) {
  Vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  EXPECT_EQ(vector.at(0), original.at(0));
  EXPECT_EQ(vector.at(1), original.at(1));
  EXPECT_THROW(vector.at(4), std::out_of_range);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
}

TEST(VectorErase, test_4) {
  Vector<int> vector{1, 2};
  std::vector<int> original{1, 2};
  EXPECT_THROW(vector.at(3), std::out_of_range);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorPushBack, test_1) {
  Vector<int> vector{1, 2};
  std::vector<int> original{1, 2};
  vector.push_back(33);
  vector.push_back(-33);
  original.push_back(33);
  original.push_back(-33);
  for (int i = 0; i < 4; ++i) EXPECT_EQ(vector.at(i), original.at(i));
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
}

TEST(VectorPopBack, test_1) {
  Vector<int> vector{1, 2};
  std::vector<int> original{1, 2};
  vector.pop_back();
  vector.pop_back();
  original.pop_back();
  original.pop_back();
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorPopBack, test_2) {
  Vector<int> vector;
  vector.pop_back();
  vector.pop_back();
  EXPECT_EQ(vector.size(), 0);
  EXPECT_EQ(vector.capacity(), 0);
  EXPECT_EQ(vector.empty(), true);
}

TEST(VectorPopBack, test_3) {
  Vector<int> vector{1, 2, 4, 8};
  std::vector<int> original{1, 2, 4, 8};
  vector.pop_back();
  vector.pop_back();
  original.pop_back();
  original.pop_back();
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector.empty(), original.empty());
}

TEST(VectorSwap, test_1) {
  Vector<int> vector;
  std::vector<int> original;
  Vector<int> vector_copy;
  std::vector<int> original_copy;
  vector_copy.swap(vector);
  original_copy.swap(original);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector_copy.size(), original_copy.size());
  EXPECT_EQ(vector_copy.capacity(), original_copy.capacity());
}

TEST(VectorSwap, test_2) {
  Vector<int> vector{15, 70, -1};
  std::vector<int> original{15, 70, -1};
  Vector<int> vector_copy;
  std::vector<int> original_copy;
  vector_copy.swap(vector);
  original_copy.swap(original);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector_copy.size(), original_copy.size());
  EXPECT_EQ(vector_copy.capacity(), original_copy.capacity());
}

TEST(VectorSwap, test_3) {
  Vector<int> vector{15, 70, -1};
  std::vector<int> original{15, 70, -1};
  Vector<int> vector_copy{2};
  std::vector<int> original_copy{2};
  vector_copy.swap(vector);
  original_copy.swap(original);
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(vector_copy.size(), original_copy.size());
  EXPECT_EQ(vector_copy.capacity(), original_copy.capacity());
}

TEST(VectorInsertManyBack, test_2) {
  Vector<int> vector;
  std::vector<int> original;
  vector.insert_many_back(1, 2, 3);
  original.insert(original.end(), {1, 2, 3});
  EXPECT_EQ(vector.size(), original.size());
  for (int i = 0; i < 3; ++i) EXPECT_EQ(vector.at(i), original.at(i));
}

TEST(VectorInsertMany, test_1) {
  Vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  vector.insert_many(vector.begin() + 1, 8, 3, 2, 4, 5);
  original.insert(original.begin() + 1, {8, 3, 2, 4, 5});
  for (size_t i = 0; i < vector.size(); ++i)
    EXPECT_EQ(vector.at(i), original.at(i));
  EXPECT_EQ(vector.size(), original.size());
}

TEST(VectorInsertMany, test_2) {
  Vector<int> vector;
  std::vector<int> original;
  vector.insert_many(vector.end(), 8, 3, 2, 4, 5);
  original.insert(original.end(), {8, 3, 2, 4, 5});
  for (size_t i = 0; i < vector.size(); ++i)
    EXPECT_EQ(vector.at(i), original.at(i));
  EXPECT_EQ(vector.size(), original.size());
}

TEST(VectorInsertMany, test_3) {
  Vector<int> vector{1, 2, 3};
  EXPECT_THROW(vector.insert_many(vector.end() + 1, 5, 6), std::out_of_range);
  EXPECT_THROW(vector.insert_many(vector.begin() - 1, 5, 6), std::out_of_range);
}
