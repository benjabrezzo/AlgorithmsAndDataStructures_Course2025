//
// Created by benja on 11/04/25.
//
#include <gtest/gtest.h>
#include <stdexcept>
#include "queue.hpp"

// Tests para Queue
TEST(QueueTest, EnqueueDequeue) {
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    EXPECT_EQ(queue.dequeue(), 10);
    EXPECT_EQ(queue.dequeue(), 20);
    EXPECT_EQ(queue.dequeue(), 30);
}

TEST(QueueTest, Front) {
    Queue<int> queue;
    queue.enqueue(10);
    EXPECT_EQ(queue.front(), 10);
    queue.enqueue(20);
    EXPECT_EQ(queue.front(), 10); // El front sigue siendo el primer elemento

    queue.dequeue();
    EXPECT_EQ(queue.front(), 20);
}

TEST(QueueTest, IsEmpty) {
    Queue<int> queue;
    EXPECT_TRUE(queue.is_empty());

    queue.enqueue(10);
    EXPECT_FALSE(queue.is_empty());

    queue.dequeue();
    EXPECT_TRUE(queue.is_empty());
}

TEST(QueueTest, DequeueEmptyQueue) {
    Queue<int> queue;
    EXPECT_THROW({
        queue.dequeue();
    }, std::runtime_error);
}

TEST(QueueTest, FrontEmptyQueue) {
    Queue<int> queue;
    EXPECT_THROW({
        queue.front();
    }, std::runtime_error);
}

TEST(QueueTest, FIFOOrder) {
    Queue<std::string> queue;
    queue.enqueue("primero");
    queue.enqueue("segundo");
    queue.enqueue("tercero");

    EXPECT_EQ(queue.dequeue(), "primero");
    EXPECT_EQ(queue.dequeue(), "segundo");
    EXPECT_EQ(queue.dequeue(), "tercero");
}

TEST(QueueTest, MixedOperations) {
    Queue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    EXPECT_EQ(queue.front(), 10);

    EXPECT_EQ(queue.dequeue(), 10);
    queue.enqueue(30);
    EXPECT_EQ(queue.front(), 20);

    queue.enqueue(40);
    EXPECT_EQ(queue.dequeue(), 20);
    EXPECT_EQ(queue.dequeue(), 30);
    EXPECT_EQ(queue.dequeue(), 40);

    EXPECT_TRUE(queue.is_empty());
}

TEST(QueueTest, Print) {
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);

    // Solo verificamos que no lance excepciones
    EXPECT_NO_THROW(queue.print());
}

