//
// Created by maxim on 14/02/2024.
//

#ifndef COLLECTIONS_COMMONS_RANDOMIZED_SET_TEST_H
#define COLLECTIONS_COMMONS_RANDOMIZED_SET_TEST_H


#include <gtest/gtest.h>
#include "randomized_set.h"

class RandomizedSetTest : public ::testing::Test {
protected:
void SetUp() override {
// Code exécuté avant chaque test
obj = randomizedSetCreate();
}

void TearDown() override {
// Code exécuté après chaque test
randomizedSetFree(obj);
}

RandomizedSet* obj;
};

TEST_F(RandomizedSetTest, InsertTest) {
ASSERT_TRUE(randomizedSetInsert(obj, 1));
ASSERT_TRUE(randomizedSetInsert(obj, 2));
}

TEST_F(RandomizedSetTest, RemoveTest) {
randomizedSetInsert(obj, 1);
randomizedSetInsert(obj, 2);

ASSERT_TRUE(randomizedSetRemove(obj, 1));
ASSERT_FALSE(randomizedSetRemove(obj, 3));
}

TEST_F(RandomizedSetTest, GetRandomTest) {
randomizedSetInsert(obj, 1);
randomizedSetInsert(obj, 2);

int result = randomizedSetGetRandom(obj);
ASSERT_TRUE(result == 1 || result == 2);
}


#endif //COLLECTIONS_COMMONS_RANDOMIZED_SET_TEST_H
