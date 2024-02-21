//
// Created by maxim on 14/02/2024.
//

#ifndef COLLECTIONS_COMMONS_RANDOMIZED_SET_TEST_H
#define COLLECTIONS_COMMONS_RANDOMIZED_SET_TEST_H


#include <gtest/gtest.h>

class RandomizedSetTest : public ::testing::Test {
protected:
public:

    typedef struct {
        /**
         * Array where are stored set values
         */
        int *nums;
        /**
         * Current size of the randomized set
         */
        int size;
        /**
         * Current capacity of the set
         */
        int capacity;
    } RandomizedSet;

    void randomized_set_create(RandomizedSet *set);
    bool randomized_set_add(RandomizedSetTest::RandomizedSet  *obj, int val);
    bool randomized_set_remove(RandomizedSetTest::RandomizedSet  *obj, int val);
    int randomized_set_get_random(RandomizedSetTest::RandomizedSet  *obj);


protected:
    RandomizedSet *obj;

    void SetUp() override {
// Code exécuté avant chaque test
        obj = (RandomizedSet*)malloc(sizeof(RandomizedSet));
        randomized_set_create(obj);
    }

    void randomized_set_destroy(RandomizedSet *obj);

    void TearDown() override {
// Code exécuté après chaque test
        randomized_set_destroy(obj);
    }

};

TEST_F(RandomizedSetTest, InsertTest) {
    ASSERT_TRUE(randomized_set_add(obj, 1));
    ASSERT_TRUE(randomized_set_add(obj, 2));
}

TEST_F(RandomizedSetTest, RemoveTest) {
    randomized_set_add(obj, 1);
    randomized_set_add(obj, 2);

    ASSERT_TRUE(randomized_set_remove(obj, 1));
    ASSERT_FALSE(randomized_set_remove(obj, 3));
    ASSERT_TRUE(randomized_set_remove(obj, 2));
}

TEST_F(RandomizedSetTest, GetRandomTest) {
    randomized_set_add(obj, 1);
    randomized_set_add(obj, 2);

    int result = randomized_set_get_random(obj);
    ASSERT_TRUE(result == 1 || result == 2);

}


#endif //COLLECTIONS_COMMONS_RANDOMIZED_SET_TEST_H
