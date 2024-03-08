//
// Created by maxim on 8/03/2024.
//

#ifndef COLLECTIONS_COMMONS_SORT_TEST_H
#define COLLECTIONS_COMMONS_SORT_TEST_H
#include "gtest/gtest.h"
#include "sort.h"

typedef struct {
    int x;
    int y;
} Block;

typedef struct {
    Block **block;
} Chunk;


TEST(ArraySplitTest, SimpleStructTest) {
    Block blocks[5] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    Chunk chunk;

    void **split_blocks = (void** )malloc(5 * sizeof(void*));
    int size = 0;

    array_split(&split_blocks, &size, blocks, 1, 4);

    ASSERT_EQ(size, 3);
    ASSERT_EQ(((Block *)split_blocks[0])->x, 3);
    ASSERT_EQ(((Block *)split_blocks[1])->y, 6);
    ASSERT_EQ(((Block *)split_blocks[2])->x, 7);

    for (int i = 0; i < size; i++) {
        free(split_blocks[i]);
    }
    free(split_blocks);
}
#endif //COLLECTIONS_COMMONS_SORT_TEST_H
