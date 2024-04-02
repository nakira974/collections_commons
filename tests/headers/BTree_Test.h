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
    int chunks = 2;
    int types = 9;
    Block **blocks = generateBlocks(chunks, types);
    for(int i =1; i<=chunks;i++){
        for(int j = 1; j<=types;j++){
            btree_add(tree, &blocks[i][j]);
        }
    }

    int count =0;
    for(int i =1; i<=chunks;i++){
        for(int j = 1; j<=types;j++){
            int pos = 0;
            void* value = &blocks[i][j];
            ASSERT_TRUE(btree_containsKey(tree, &pos, &value));
            ASSERT_TRUE(btree_remove(tree, &value));
            Block *block = (Block*)value;
            block = nullptr;
            count++;
        }
    }

    free(blocks);

}
#endif //COLLECTIONS_COMMONS_BTREE_TEST_H
