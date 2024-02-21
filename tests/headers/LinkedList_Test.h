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
    for (int i = 0; i < 1000000; ++i) {
        int *value = (int *) malloc(sizeof(int));
        *value = i;
        list_add(&list, NULL, value);
    }

    EXPECT_EQ(list_size(&list), 1000000);

    // Deletion test
    LinkedElement *cur = list_first(&list);
    while (!list_is_last(&list, cur)) {
        void *value;
        list_remove(&list, cur, &value);
        free(value);
        cur = list_next(cur);
    }

    EXPECT_EQ(list_size(&list), 0);
}

#endif //COLLECTIONS_COMMONS_LINKEDLIST_TEST_H
