//
// Created by maxim on 21/02/2024.
//

#ifndef COLLECTIONS_COMMONS_DLINKEDLIST_TEST_H
#define COLLECTIONS_COMMONS_DLINKEDLIST_TEST_H

#include "dlist.h"
#include <gtest/gtest.h>


class DLinkedListTest : public testing::Test {
protected:
    DLinkedList list;

    void SetUp() override {
        dlist_create(&list, free);
    }

    void TearDown() override {
        dlist_destroy(&list);
    }
};

TEST_F(DLinkedListTest, PerformanceTest) {
    // Insertion test

    for (int i = 0; i < 100000; ++i) {
        int *value = (int *) malloc(10 * sizeof(int));
        for (int j = 0; j < 10; j++)value[j] = i + j;
        dlist_add(&list, dlist_first(&list), value);
    }

    EXPECT_EQ(dlist_size(&list), 100000);

    // Deletion test
    while (dlist_size(&list) != 0) {
        void *value;
        dlist_remove(&list, dlist_getRandom(&list), &value);
        delete static_cast<int *>(value);
    }


    EXPECT_EQ(dlist_size(&list), 0);

    for (int i = 0; i < 100000; ++i) {
        int *value = (int *) malloc(10 * sizeof(int));
        for (int j = 0; j < 10; j++)value[j] = i + j;
        dlist_add(&list, dlist_first(&list), value);
    }


    while (dlist_size(&list) != 0) {
        void *value;
        dlist_remove(&list, dlist_getRandom(&list), &value);
        delete static_cast<int *>(value);
    }

    EXPECT_EQ(dlist_size(&list), 0);
}

#endif //COLLECTIONS_COMMONS_DLINKEDLIST_TEST_H
