#include <gtest/gtest.h>

#include <array>

#include "../s21_containers.h"

template <typename T, std::size_t N>
using Array = s21::s21_array<T, N>;

/* ---------------------------- constructors ---------------------------- */
TEST(S21_containers_array, default_constructor) {
  Array<int, 5> arr;

  ASSERT_EQ(5, arr.size());
}

TEST(S21_containers_array, list_constructor) {
  Array<int, 5> arr = {11, 22, 33};

  ASSERT_EQ(11, arr[0]);
  ASSERT_EQ(22, arr[1]);
  ASSERT_EQ(33, arr[2]);
  ASSERT_EQ(0, arr[3]);
  ASSERT_EQ(0, arr[4]);
}

TEST(S21_containers_array, copy_constructor) {
  Array<int, 3> arr = {99, 88, 77};
  Array<int, 3> copied_arr(arr);

  ASSERT_EQ(99, copied_arr[0]);
  ASSERT_EQ(88, copied_arr[1]);
  ASSERT_EQ(77, copied_arr[2]);
}

TEST(S21_containers_array, move_constructor) {
  Array<int, 3> arr1 = {11, 22, 33};
  Array<int, 3> moved_arr(std::move(arr1));

  ASSERT_EQ(11, moved_arr[0]);
  ASSERT_EQ(22, moved_arr[1]);
  ASSERT_EQ(33, moved_arr[2]);
  ASSERT_EQ(3, moved_arr.size());
}

TEST(S21_containers_array, operator_equals) {
  Array<int, 3> arr1 = {11, 22, 33};
  Array<int, 3> moved_arr = std::move(arr1);

  ASSERT_EQ(11, moved_arr[0]);
  ASSERT_EQ(22, moved_arr[1]);
  ASSERT_EQ(33, moved_arr[2]);
  ASSERT_EQ(3, moved_arr.size());
}

/* ---------------------------- access ---------------------------------- */

TEST(S21_containers_array, at) {
  Array<int, 3> arr = {77, 88, 99};

  ASSERT_EQ(77, arr.at(0));
  ASSERT_EQ(88, arr.at(1));
  ASSERT_EQ(99, arr.at(2));
  EXPECT_THROW({ arr.at(-1); }, std::out_of_range);
  EXPECT_THROW({ arr.at(3); }, std::out_of_range);
}

TEST(S21_containers_array, access_brackets) {
  Array<int, 3> arr = {11, 22, 33};

  ASSERT_EQ(11, arr[0]);
  ASSERT_EQ(22, arr[1]);
  ASSERT_EQ(33, arr[2]);
}

TEST(S21_containers_array, front) {
  Array<int, 3> arr = {99, 88, 77};
  ASSERT_EQ(99, arr.front());

  Array<int, 0> empty_arr;
  EXPECT_THROW({ empty_arr.front(); }, std::out_of_range);
}

TEST(S21_containers_array, back) {
  Array<int, 3> arr = {33, 44, 55};
  ASSERT_EQ(55, arr.back());

  Array<int, 0> empty_arr;
  EXPECT_THROW({ empty_arr.back(); }, std::out_of_range);
}

TEST(S21_containers_array, data) {
  Array<int, 3> arr = {11, 22, 33};
  ASSERT_EQ(11, *(arr.data()));

  std::array<int, 0> empty_arr;
  ASSERT_EQ(nullptr, empty_arr.data());
}

/* --------------------------- iterators --------------------------------- */
TEST(S21_containers_array, begin) {
  Array<int, 3> arr = {77, 88, 99};
  ASSERT_EQ(77, *(arr.begin()));
}

TEST(S21_containers_array, end) {
  Array<int, 3> arr = {11, 22, 33};
  ASSERT_EQ(33, *(arr.end() - 1));
}

/* --------------------------- capacity --------------------------------- */
TEST(S21_containers_array, empty) {
  Array<int, 0> empty_arr;
  Array<int, 3> not_empty_arr = {1, 2, 3};

  ASSERT_EQ(1, empty_arr.empty());
  ASSERT_EQ(0, not_empty_arr.empty());
}

TEST(S21_containers_array, size) {
  Array<int, 0> empty_arr;
  Array<int, 3> arr1 = {1, 2, 3};
  Array<int, 5> arr2 = {11, 22, 33, 44};

  ASSERT_EQ(0, empty_arr.size());
  ASSERT_EQ(3, arr1.size());
  ASSERT_EQ(5, arr2.size());
}

TEST(S21_containers_array, max_size) {
  Array<int, 0> empty_arr;
  Array<int, 3> arr1 = {1, 2, 3};
  Array<int, 5> arr2 = {11, 22, 33, 44};

  ASSERT_EQ(0, empty_arr.max_size());
  ASSERT_EQ(3, arr1.max_size());
  ASSERT_EQ(5, arr2.max_size());
}

/* --------------------------- modifiers --------------------------------- */
TEST(S21_containers_array, swap) {
  Array<int, 3> arr1 = {11, 22, 33};
  Array<int, 3> arr2 = {77, 88, 99};

  ASSERT_EQ(11, arr1[0]);
  ASSERT_EQ(22, arr1[1]);
  ASSERT_EQ(33, arr1[2]);

  ASSERT_EQ(77, arr2[0]);
  ASSERT_EQ(88, arr2[1]);
  ASSERT_EQ(99, arr2[2]);

  arr1.swap(arr2);

  ASSERT_EQ(77, arr1[0]);
  ASSERT_EQ(88, arr1[1]);
  ASSERT_EQ(99, arr1[2]);

  ASSERT_EQ(11, arr2[0]);
  ASSERT_EQ(22, arr2[1]);
  ASSERT_EQ(33, arr2[2]);
}

TEST(S21_containers_array, fill) {
  Array<int, 5> arr1 = {0};

  arr1.fill(5);

  ASSERT_EQ(5, arr1[0]);
  ASSERT_EQ(5, arr1[1]);
  ASSERT_EQ(5, arr1[2]);
  ASSERT_EQ(5, arr1[3]);
  ASSERT_EQ(5, arr1[4]);
}