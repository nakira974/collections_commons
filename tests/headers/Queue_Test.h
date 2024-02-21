//
// Created by maxim on 21/02/2024.
//

#ifndef COLLECTIONS_COMMONS_QUEUE_TEST_H
#define COLLECTIONS_COMMONS_QUEUE_TEST_H
#include <gtest/gtest.h>
#include "queue.h"

// Define a simple struct for testing
typedef struct {
    int id;
    float weight;
} Minecart;

void free_minecart(void *value) {
    if (value != nullptr) {
        free((Minecart*)value);
    }
}

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        queue_create(&queue, free_minecart);
    }

    void TearDown() override {
        queue_destroy(&queue);
    }

    Queue queue;
};

TEST_F(QueueTest, EnqueueDequeueTest) {
    Minecart *cart = (Minecart*)malloc(sizeof(Minecart));
    cart->id = 1;
    cart->weight = 100.5;

    queue_enqueue(&queue, cart);

    Minecart *dequeueCart;
    queue_dequeue(&queue, &dequeueCart);

    ASSERT_EQ(dequeueCart->id, 1);
    ASSERT_EQ(dequeueCart->weight, 100.5);
}

TEST_F(QueueTest, SizeTest) {
    ASSERT_EQ(queue_size(&queue), 0);

    Minecart *cart = (Minecart*)malloc(sizeof(Minecart));
    cart->id = 1;
    cart->weight = 100.5;

    queue_enqueue(&queue, cart);

    ASSERT_EQ(queue_size(&queue), 1);
}

TEST_F(QueueTest, PeekTest) {
    ASSERT_EQ(queue_peek(&queue), nullptr);

    Minecart *cart = (Minecart*)malloc(sizeof(Minecart));
    cart->id = 1;
    cart->weight = 100.5;

    queue_enqueue(&queue, cart);

    ASSERT_NE(queue_peek(&queue), nullptr);
}
#endif //COLLECTIONS_COMMONS_QUEUE_TEST_H
