//
// Created by maxim on 21/02/2024.
//

#ifndef COLLECTIONS_COMMONS_STACK_TEST_H
#define COLLECTIONS_COMMONS_STACK_TEST_H

#include "stack.h"
#include <gtest/gtest.h>

class StackTest : public testing::Test {
protected:
    Stack stack;

    void SetUp() override {
        stack_create(&stack, free);
    }

    void TearDown() override {
        if (stack_size(&stack) > 0)
            stack_destory(&stack);
    }
};

TEST_F(StackTest, PushPopTest) {
    int value1 = 10;
    int value2 = 20;

    stack_push(&stack, &value1);
    stack_push(&stack, &value2);

    int *poppedValue1, *poppedValue2;
    stack_pop(&stack, (void **) &poppedValue1);
    stack_pop(&stack, (void **) &poppedValue2);

    EXPECT_EQ(*poppedValue1, value2);
    EXPECT_EQ(*poppedValue2, value1);
}

TEST_F(StackTest, PeekTest) {
    int value = 30;
    int *poppedValue1;
    stack_push(&stack, &value);

    int *peekedValue = (int *) stack_peek(&stack);

    EXPECT_EQ(*peekedValue, value);
    stack_pop(&stack, (void **) &poppedValue1);
}

TEST_F(StackTest, SizeTest) {
    int value1 = 5;
    int value2 = 7;

    stack_push(&stack, &value1);
    stack_push(&stack, &value2);

    EXPECT_EQ(stack_size(&stack), 2);

    int *poppedValue1, *poppedValue2;
    stack_pop(&stack, (void **) &poppedValue2);
    stack_pop(&stack, (void **) &poppedValue1);

    EXPECT_EQ(stack_size(&stack), 0);

}

#endif //COLLECTIONS_COMMONS_STACK_TEST_H
