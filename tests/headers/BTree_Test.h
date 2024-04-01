//
// Created by maxim on 31/03/2024.
//

#ifndef COLLECTIONS_COMMONS_BTREE_TEST_H
#define COLLECTIONS_COMMONS_BTREE_TEST_H

#include "gtest/gtest.h"
#include "btree.h"

class BTreeTest : public testing::Test {
protected:
    BTree *tree{};

    void SetUp() override {
        tree = (BTree *) malloc(sizeof(BTree));
        // Creating 16 containers, because it works using an AVR ATmega328PB 8bit addressing blocks microprocessor
        btree_create(tree, compareBlocks, free);
    }

    void TearDown() override {
        btree_destroy(tree);
    }
};

TEST_F(BTreeTest, BasicTest) {
    Chunk *chunk1, *chunk2;
    Block *b1, *b2, *b3, *b4;
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data = 1;
    chunk2->data = 2;
    b1 = (Block *) malloc(sizeof(Block));
    b2 = (Block *) malloc(sizeof(Block));
    b3 = (Block *) malloc(sizeof(Block));
    b4 = (Block *) malloc(sizeof(Block));
    b1->type = 1;
    b1->chunk = chunk1;
    b2->type = 1;
    b2->chunk = chunk2;
    b3->type = 2;
    b3->chunk = chunk1;
    b4->type = 2;
    b4->chunk = chunk1;
    sprintf(b1->id, "%s", "b1");
    sprintf(b2->id, "%s", "b2");
    sprintf(b3->id, "%s", "b3");
    sprintf(b4->id, "%s", "b4");

    btree_add(tree, b1);
    btree_add(tree, b2);
    btree_add(tree, b3);
    btree_add(tree, b4);

    int pos = 0;
    void* value = b4;
    ASSERT_TRUE(btree_containsKey(tree, &pos, &value));
    ASSERT_TRUE(btree_remove(tree, &value));
    free(b4);
    value = b3;
    ASSERT_TRUE(btree_remove(tree, &value));
    free(b3);
    value = b2;
    ASSERT_TRUE(btree_remove(tree, &value));
    free(b2);
    value = b1;
    ASSERT_TRUE(btree_containsKey(tree, &pos, &value));
    ASSERT_TRUE(btree_remove(tree, &value));
    free(b1);


    value = b4;
    ASSERT_FALSE(btree_containsKey(tree, &pos, &value));

    free(chunk1);
    free(chunk2);
}
#endif //COLLECTIONS_COMMONS_BTREE_TEST_H
