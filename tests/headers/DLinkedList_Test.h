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
    for (int i = 0; i < 1000000; ++i) {
        int *value = (int *) malloc(sizeof(int));
        *value = i;
        dlist_add(&list, NULL, value);
    }

    EXPECT_EQ(dlist_size(&list), 1000000);

    // Deletion test
    DLinkedElement *cur = dlist_first(&list);
    while (cur != NULL) {
        void *value;
        dlist_remove(&list, cur, &value);
        free(value);
        cur = dlist_next(cur);
    }

    EXPECT_EQ(dlist_size(&list), 0);
}

#endif //COLLECTIONS_COMMONS_DLINKEDLIST_TEST_H
