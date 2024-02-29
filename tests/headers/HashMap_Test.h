#include "gtest/gtest.h"
#include "hashmap.h"
#include "hash_utils.h"

struct Chunk {
    int data;
};

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

    ASSERT_TRUE(hashmap_put(map, reinterpret_cast<void *>(chunk1->data), (void*)chunk1));
    ASSERT_TRUE(hashmap_put(map, reinterpret_cast<void *>(chunk2->data), (void*)chunk2));

    Chunk *value;
    void* temp = reinterpret_cast<void *>(chunk1->data);
    ASSERT_TRUE(hashmap_get(map, &temp));
    value = (Chunk *)temp;
    ASSERT_EQ(value->data, 1);
    temp = reinterpret_cast<void *>(chunk2->data);
    ASSERT_TRUE(hashmap_remove(map, &temp));
    ASSERT_FALSE(hashmap_containsKey(map, reinterpret_cast<void **>(&chunk2->data)));

    ASSERT_EQ(hashmap_size(map), 1);
    ASSERT_TRUE(hashmap_remove(map, reinterpret_cast<void **>(&chunk1->data)));
    ASSERT_EQ(hashmap_size(map), 0);
}