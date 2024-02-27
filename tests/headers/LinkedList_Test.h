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
        list_add(&list, nullptr, value);
    }

    EXPECT_EQ(list_size(&list), 1000000);

    // Deletion test
    LinkedElement *current_element = list_first(&list);

    for(current_element= list_get_random(&list); current_element != nullptr;current_element= list_next(current_element)){
        void *value;
        list_remove(&list, current_element, &value);
        delete static_cast<int*>(value);
    }

    EXPECT_EQ(list_size(&list), 0);

    for (int i = 0; i < 1000000; ++i) {
        int *value = (int *) malloc(sizeof(int));
        *value = i;
        list_add(&list, nullptr, value);
    }

    current_element= list_first(&list);

    while (current_element != nullptr) {
        void *value;
        list_remove(&list, current_element, &value);
        free(value);
        current_element = list_next(current_element);
    }

    EXPECT_EQ(list_size(&list), 0);
}

#endif //COLLECTIONS_COMMONS_LINKEDLIST_TEST_H
