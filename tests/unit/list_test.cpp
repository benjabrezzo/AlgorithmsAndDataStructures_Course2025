//
// Created by benja on 11/04/25.
//

#include <gtest/gtest.h>
#include "list.hpp"

// Tests para LinkedList
TEST(LinkedListTest, PushFront) {
    LinkedList<int> list;
    list.push_front(10);
    EXPECT_EQ(list.get_head()->data, 10);
    list.push_front(20);
    EXPECT_EQ(list.get_head()->data, 20);
    EXPECT_EQ(list.get_head()->next->data, 10);
}

TEST(LinkedListTest, RemoveAt) {
    LinkedList<int> list;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);

    // Remueve el primer elemento (10)
    list.remove_at(0);
    EXPECT_EQ(list.get_head()->data, 20);

    // Remueve el nuevo segundo elemento (30)
    list.remove_at(1);
    EXPECT_EQ(list.get_head()->data, 20);
    EXPECT_EQ(list.get_head()->next, nullptr);

    // Intenta remover de una posición fuera de rango
    list.remove_at(5); // No debería causar fallos
}

TEST(LinkedListTest, Take) {
    LinkedList<int> list;
    for (int i = 5; i >= 1; i--) {
        list.push_front(i);
    }
    // Lista: 1 -> 2 -> 3 -> 4 -> 5

    // Tomar 3 elementos desde la posición 1
    auto new_list = list.take(1, 3);
    EXPECT_EQ(new_list->data, 2);
    EXPECT_EQ(new_list->next->data, 3);
    EXPECT_EQ(new_list->next->next->data, 4);
    EXPECT_EQ(new_list->next->next->next, nullptr);

    // Probar take desde una posición fuera de rango
    auto null_list = list.take(10, 2);
    EXPECT_EQ(null_list, nullptr);

    // Probar take desde una lista vacía
    LinkedList<int> empty_list;
    auto empty_result = empty_list.take(0, 1);
    EXPECT_EQ(empty_result, nullptr);

    // Liberar la memoria
    auto current = new_list;
    while (current != nullptr) {
        auto temp = current;
        current = current->next;
        delete temp;
    }
}

TEST(LinkedListTest, Print) {
    LinkedList<int> list;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);

    // Solo verificamos que no lance excepciones
    EXPECT_NO_THROW(list.print());
}

// Tests para DoublyLinkedList
TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList<int> list;
    list.push_front(10);
    EXPECT_EQ(list.get_head()->data, 10);
    EXPECT_EQ(list.get_head()->prev, nullptr);
    list.push_front(20);
    EXPECT_EQ(list.get_head()->data, 20);
    EXPECT_EQ(list.get_head()->next->data, 10);
    EXPECT_EQ(list.get_head()->next->prev, list.get_head());
}

TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.get_head()->data, 10);
    list.push_back(20);
    EXPECT_EQ(list.get_head()->data, 10);
    EXPECT_EQ(list.get_head()->next->data, 20);
    EXPECT_EQ(list.get_head()->next->prev, list.get_head());

    // Prueba más extensa
    list.push_back(30);
    EXPECT_EQ(list.get_head()->next->next->data, 30);
    EXPECT_EQ(list.get_head()->next->next->prev, list.get_head()->next);
}

TEST(DoublyLinkedListTest, RemoveAt) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Remueve el elemento en el medio (20)
    list.remove_at(1);
    EXPECT_EQ(list.get_head()->data, 10);
    EXPECT_EQ(list.get_head()->next->data, 30);
    EXPECT_EQ(list.get_head()->next->prev, list.get_head());

    // Remueve el primer elemento (10)
    list.remove_at(0);
    EXPECT_EQ(list.get_head()->data, 30);
    EXPECT_EQ(list.get_head()->prev, nullptr);

    // Remueve el último elemento (30)
    list.remove_at(0);
    EXPECT_EQ(list.get_head(), nullptr);

    // Intenta remover de una lista vacía
    list.remove_at(0); // No debería causar fallos
}

TEST(DoublyLinkedListTest, CopyList) {
    DoublyLinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    DoublyLinkedList<int> list2;
    list2.copy_list(list1);

    // Verificar que los elementos se copiaron correctamente
    auto current1 = list1.get_head();
    auto current2 = list2.get_head();

    while (current1 != nullptr && current2 != nullptr) {
        EXPECT_EQ(current1->data, current2->data);
        current1 = current1->next;
        current2 = current2->next;
    }

    EXPECT_EQ(current1, nullptr);
    EXPECT_EQ(current2, nullptr);

    // Prueba copiar una lista vacía
    DoublyLinkedList<int> empty_list;
    DoublyLinkedList<int> list3;
    list3.push_back(5);
    list3.copy_list(empty_list);
    EXPECT_EQ(list3.get_head(), nullptr);
}

TEST(DoublyLinkedListTest, Print) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    // Solo verificamos que no lance excepciones
    EXPECT_NO_THROW(list.print());
}

