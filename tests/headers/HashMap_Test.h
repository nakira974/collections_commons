#include "gtest/gtest.h"
#include "hashmap.h"
#include "hash_utils.h"
#include "block.h"

class HashMapTest : public testing::Test {
protected:
    HashMap *map;

    void SetUp() override {
        map = (HashMap *) malloc(sizeof(HashMap));
        // Creating 16 containers, because it works using an AVR ATmega328PB 8bit addressing blocks microprocessor
        hashmap_create(map, 16, hashint, cmp_int, free);
    }

    void TearDown() override {
        hashmap_destroy(map);
    }
};

TEST_F(HashMapTest, BasicTest) {
    Chunk *chunk1,*chunk2;
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data=1;
    chunk2->data=2;

    ASSERT_TRUE(hashmap_put(map, &chunk1->data, chunk1));
    ASSERT_TRUE(hashmap_put(map, &chunk2->data, chunk2));

    Chunk *value;
    void* temp = &chunk1->data;
    ASSERT_TRUE(hashmap_get(map, &temp));
    value = (Chunk *) temp;
    ASSERT_EQ(value->data, 1);
    temp = &chunk2->data;
    ASSERT_TRUE(hashmap_remove(map, &temp));
    ASSERT_EQ((Chunk*) temp, chunk2);
    free(temp);
    temp = &chunk2->data;
    ASSERT_FALSE(hashmap_containsKey(map, &temp));

    ASSERT_EQ(hashmap_size(map), 1);
    temp = &chunk1->data;
    ASSERT_TRUE(hashmap_remove(map, &temp));
    free(temp);
    ASSERT_EQ(hashmap_size(map), 0);
}