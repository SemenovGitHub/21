#include <gtest/gtest.h>

#include "s21_list_test.cpp"
#include "s21_map_test.cpp"
#include "s21_multiset_test.cpp"
#include "s21_queue_test.cpp"
#include "s21_set_test.cpp"
#include "s21_stack_test.cpp"
#include "s21_vector_test.cpp"
#include "test_array.cpp"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}