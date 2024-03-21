//
// Created by maxim on 8/03/2024.
//

#ifndef COLLECTIONS_COMMONS_DEQUE_TEST_H
#define COLLECTIONS_COMMONS_DEQUE_TEST_H

#include <gtest/gtest.h>
#include "deque.h"

class DequeTest : public ::testing::Test {
protected:
    // Define a simple struct for testing
    typedef struct {
        int id;
        float weight;
    } Minecart;

    static void free_minecart(void *value) {
        if (value != nullptr) {
            free((Minecart *) value);
        }
    }

    void SetUp() override {
        deque_create(&deque, free_minecart);
    }

    void TearDown() override {
        deque_destroy(&deque);
    }

    Deque deque;
};

TEST_F(DequeTest, EnqueueDequeueTest) {
    Minecart *cart = (Minecart *) malloc(sizeof(Minecart));
    cart->id = 1;
    cart->weight = 100.5;

    deque_enqueue(&deque, cart);

    Minecart *dequeueCart = NULL;
    deque_dequeue(&deque, &dequeueCart);

    ASSERT_EQ(dequeueCart->id, 1);
    ASSERT_EQ(dequeueCart->weight, 100.5);
}

TEST_F(DequeTest, SizeTest) {
    ASSERT_EQ(deque_size(&deque), 0);

    Minecart *cart = (Minecart *) malloc(sizeof(Minecart));
    cart->id = 1;
    cart->weight = 100.5;

    deque_enqueue(&deque, cart);

    ASSERT_EQ(deque_size(&deque), 1);
}

TEST_F(DequeTest, PeekTest) {
    ASSERT_EQ(deque_peek(&deque), nullptr);

    Minecart *cart = (Minecart *) malloc(sizeof(Minecart));
    cart->id = 1;
    cart->weight = 100.5;

    deque_enqueue(&deque, cart);

    ASSERT_NE(deque_peek(&deque), nullptr);
}

#endif //COLLECTIONS_COMMONS_DEQUE_TEST_H
