//
// Created by benja on 11/04/25.
//
#include <gtest/gtest.h>
#include <stdexcept>
#include "stack.hpp"

// Tests para Stack
TEST(StackTest, PushPop) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);
}

TEST(StackTest, Top) {
    Stack<int> stack;
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20); // El top ahora es el último elemento insertado

    stack.pop();
    EXPECT_EQ(stack.top(), 10);
}

TEST(StackTest, IsEmpty) {
    Stack<int> stack;
    EXPECT_TRUE(stack.is_empty());

    stack.push(10);
    EXPECT_FALSE(stack.is_empty());

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, PopEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW({
        stack.pop();
    }, std::runtime_error);
}

TEST(StackTest, TopEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW({
        stack.top();
    }, std::runtime_error);
}

TEST(StackTest, LIFOOrder) {
    Stack<std::string> stack;
    stack.push("primero");
    stack.push("segundo");
    stack.push("tercero");

    EXPECT_EQ(stack.pop(), "tercero");
    EXPECT_EQ(stack.pop(), "segundo");
    EXPECT_EQ(stack.pop(), "primero");
}

TEST(StackTest, MixedOperations) {
    Stack<int> stack;

    stack.push(10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20);

    EXPECT_EQ(stack.pop(), 20);
    stack.push(30);
    EXPECT_EQ(stack.top(), 30);

    stack.push(40);
    EXPECT_EQ(stack.pop(), 40);
    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.pop(), 10);

    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, Print) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    // Solo verificamos que no lance excepciones
    EXPECT_NO_THROW(stack.print());
}

