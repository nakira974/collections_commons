//
// Created by maxim on 21/02/2024.
//

#ifndef COLLECTIONS_COMMONS_LINKEDLIST_TEST_H
#define COLLECTIONS_COMMONS_LINKEDLIST_TEST_H

#include "list.h"
#include <gtest/gtest.h>

class LinkedListTest : public testing::Test {
protected:
    LinkedList list{};

    void SetUp() override {
        list_create(&list, free);
    }

    void TearDown() override {
        list_destroy(&list);
    }
};

TEST_F(LinkedListTest, PerformanceTest) {
    // Insertion test
    for (int i = 0; i < 100000; ++i) {
        int *value = (int *) malloc(10 * sizeof(int));
        for (int j = 0; j < 10; j++)value[j] = i + j;
        list_add(&list, nullptr, value);
    }

    EXPECT_EQ(list_size(&list), 100000);

    // Deletion test

    while (list_size(&list) != 0) {
        void *value;
        list_remove(&list, nullptr, &value);
        delete static_cast<int *>(value);
    }

    EXPECT_EQ(list_size(&list), 0);
}

#endif //COLLECTIONS_COMMONS_LINKEDLIST_TEST_H
