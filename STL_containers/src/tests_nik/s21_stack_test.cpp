#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

template <typename T>
using Stack = s21_stack<T>;

TEST(StackDefaultConstructor, test_1) {
  Stack<int> stack;
  std::stack<int> original;
  ASSERT_EQ(stack.size(), original.size());
  ASSERT_EQ(stack.empty(), original.empty());
}

TEST(StackConstructorWithParams, test_1) {
  Stack<double> stack({1e-11, 4.11, 5.3, 6.6665});
  std::stack<double> original({1e-11, 4.11, 5.3, 6.6665});
  ASSERT_DOUBLE_EQ(stack.top(), original.top());
  ASSERT_EQ(stack.size(), original.size());
}

TEST(StackCopyConstructor, test_1) {
  Stack<double> stack1({1e-11, 4.11, 5.3, 6.6665});
  std::cout << stack1.size() << std::endl;
  Stack<double> stack2 = stack1;
  std::stack<double> original1({1e-11, 4.11, 5.3, 6.6665});
  std::stack<double> original2 = original1;
  ASSERT_DOUBLE_EQ(stack2.top(), original2.top());
  ASSERT_EQ(stack2.size(), original2.size());
}

TEST(StackCopyConstructor, test_2) {
  Stack<int> s21_stack = {1, 2, 3};
  Stack<int> s21_stack_move{s21_stack};
  std::stack<int> std_stack({1, 2, 3});
  std::stack<int> std_stack_move{std_stack};
  EXPECT_EQ(s21_stack_move.size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.top(), std_stack_move.top());
}

TEST(StackEqOperatorMove, test_1) {
  Stack<int> stack1({111, 4, 5, 6});
  Stack<int> stack2 = std::move(stack1);
  std::stack<int> original1({111, 4, 5, 6});
  std::stack<int> original2 = std::move(original1);
  ASSERT_EQ(stack2.top(), original2.top());
  ASSERT_EQ(stack2.size(), original2.size());
  ASSERT_EQ(stack1.empty(), original1.empty());
  ASSERT_EQ(stack1.size(), original1.size());
}

TEST(StackEqOperatorMove, test_2) {
  Stack<int> stack1({111, 4, 5, 6});
  Stack<int> stack2({1, 40});
  stack2 = std::move(stack1);
  std::stack<int> original1({111, 4, 5, 6});
  std::stack<int> original2({1, 40});
  original2 = std::move(original1);
  ASSERT_EQ(stack2.top(), original2.top());
  ASSERT_EQ(stack2.size(), original2.size());
  ASSERT_EQ(stack1.empty(), original1.empty());
  ASSERT_EQ(stack1.size(), original1.size());
}

TEST(StackEqOperatorMove, test_3) {
  Stack<int> stack1({111, 4, 5, 6});
  Stack<int> stack2({1, 40});
  stack1 = std::move(stack2);
  std::stack<int> original1({111, 4, 5, 6});
  std::stack<int> original2({1, 40});
  original1 = std::move(original2);
  ASSERT_EQ(stack1.top(), original1.top());
  ASSERT_EQ(stack1.size(), original1.size());
  ASSERT_EQ(stack2.empty(), original2.empty());
  ASSERT_EQ(stack2.size(), original2.size());
}

TEST(StackTop, test_throw1) {
  Stack<int> stack1({111, 4, 5, 6});
  Stack<int> stack2({1, 40});
  stack1 = std::move(stack2);
  EXPECT_THROW(stack2.top(), std::out_of_range);
}

TEST(StackTop, test_throw2) {
  Stack<int> stack1;
  EXPECT_THROW(stack1.top(), std::out_of_range);
}

TEST(StackEmpty, test_1) {
  Stack<int> stack2({1, 40});
  std::stack<int> original2({1, 40});
  EXPECT_EQ(stack2.empty(), original2.empty());
}

TEST(StackPush, test_1) {
  Stack<int> stack;
  stack.push(124);
  std::stack<int> original;
  original.push(124);
  ASSERT_EQ(stack.size(), original.size());
  ASSERT_EQ(stack.top(), original.top());
}

TEST(StackPush, test_2) {
  Stack<double> stack({1e-11, 4.11, 5.3, 6.6665});
  std::stack<double> original({1e-11, 4.11, 5.3, 6.6665});
  stack.push(-3.3);
  original.push(-3.3);
  ASSERT_DOUBLE_EQ(stack.top(), original.top());
  ASSERT_EQ(stack.size(), original.size());
}

TEST(StackSwap, test_1) {
  Stack<int> s21_stack({4, 5, 6, 7});
  Stack<int> s21_stack_swap({1, 2, 3});
  std::stack<int> std_stack({4, 5, 6, 7});
  std::stack<int> std_stack_swap({1, 2, 3});
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(StackSwap, test_2) {
  Stack<int> s21_stack;
  Stack<int> s21_stack_swap({1, 2, 3});
  std::stack<int> std_stack;
  std::stack<int> std_stack_swap({1, 2, 3});
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(StackInsertmany, test_1) {
  Stack<int> stack({111, 4, 5, 6});
  stack.push(0);
  stack.push(-3);
  stack.push(-33);
  stack.push(-55);
  ASSERT_EQ(stack.top(), -55);
  ASSERT_EQ(stack.size(), 8);
}

TEST(StackInsertmany, test_2) {
  Stack<int> stack({111, 4, 5, 6});
  ASSERT_EQ(stack.top(), 6);
  ASSERT_EQ(stack.size(), 4);
}

TEST(StackCombo, test1) {
  Stack<int> stack({111, 4, 5, 6});
  stack.pop();
  stack.push(0);
  ASSERT_EQ(stack.top(), 0);
  ASSERT_EQ(stack.size(), 4);
}
