//
// Created by maxim on 29/02/2024.
//

#include "gtest/gtest.h"
#include "set.h"
#include "block.h"

#ifndef COLLECTIONS_COMMONS_SET_TEST_H
#define COLLECTIONS_COMMONS_SET_TEST_H


class SetTest : public testing::Test {
protected:
    Set *set;

    void SetUp() override {
        set = (Set *) malloc(sizeof(Set));
        // Creating 16 containers, because it works using an AVR ATmega328PB 8bit addressing blocks microprocessor
        set_create(set, cmp_block, free);
    }

    void TearDown() override {
        set_destroy(set);
    }
};


TEST_F(SetTest, BasicTest) {
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
    ASSERT_TRUE(set_add(set, b1));
    ASSERT_TRUE(set_add(set, b2));
    ASSERT_TRUE(set_add(set, b3));
    ASSERT_FALSE(set_add(set, b4));

    // True because b3 represent that literal value evaluate by cmp_block function
    ASSERT_TRUE(set_isMember(set, b4));
    ASSERT_TRUE(set_isMember(set, b1));
    ASSERT_EQ(set_size(set), 3);
    free(b4);
    free(chunk1);
    free(chunk2);
}

TEST_F(SetTest, UnionTest) {
    Chunk *chunk1, *chunk2;
    Block *b1, *b2, *b3, *b4;
    Set *set1, *union_result;
    set1 = (Set *) malloc(sizeof(Set));
    union_result = (Set *) malloc(sizeof(Set));
    set_create(set1, cmp_block, free);
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
    set_add(set, b1);
    set_add(set, b2);
    set_add(set1, b3);
    set_add(set1, b4);
    ASSERT_TRUE(set_union(union_result, set, set1));

    // 3 and not 4, Because b4 and b3 are equals one of them will be skipped
    ASSERT_EQ(set_size(union_result), 3);
    set_destroy(set1);
    free(set1);
}

TEST_F(SetTest, DifferenceTest) {
    Set *difference_result, *left, *right;
    Chunk *chunk1, *chunk2;
    Block *b1, *b2, *b3, *b4, *b5;
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data = 1;
    chunk2->data = 2;
    b1 = (Block *) malloc(sizeof(Block));
    b2 = (Block *) malloc(sizeof(Block));
    b3 = (Block *) malloc(sizeof(Block));
    b4 = (Block *) malloc(sizeof(Block));
    b5 = (Block *) malloc(sizeof(Block));

    b1->type = 1;
    b1->chunk = chunk1;
    b2->type = 1;
    b2->chunk = chunk2;
    b3->type = 2;
    b3->chunk = chunk1;
    b4->type = 2;
    b4->chunk = chunk1;
    b5->type = 3;
    b5->chunk = chunk2;


    difference_result = (Set *) malloc(sizeof(Set));
    left = (Set *) malloc(sizeof(Set));
    right = (Set *) malloc(sizeof(Set));

    set_create(left, cmp_block, free);
    set_create(right, cmp_block, free);


    set_add(right, b1);
    set_add(right, b2);
    set_add(right, b3);

    set_add(left, b1);
    set_add(left, b2);
    set_add(left, b4);
    set_add(left, b5);

    ASSERT_TRUE(set_difference(difference_result, left, right));

    ASSERT_FALSE(set_equals(left, right));
    // Vérifier le résultat de la différence...

    ASSERT_EQ(set_size(difference_result), 1);

    void *delete_value = b1;
    ASSERT_TRUE(set_remove(left, &delete_value));
    delete_value = b5;
    ASSERT_TRUE(set_remove(difference_result, &delete_value));

    set_destroy(difference_result);
    set_destroy(left);
    free(right);

    free(chunk1);
    free(chunk2);
}

TEST_F(SetTest, IntersectionTest) {
    Set *intersection_result, *left, *right, *sub_set;
    Chunk *chunk1, *chunk2;
    Block *b1, *b2, *b3, *b4, *b5, *b1cp, *b2cp, *b4cp;

    // Creating chunks
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data = 1;
    chunk2->data = 2;

    // Creating blocks
    b1 = (Block *) malloc(sizeof(Block));
    b2 = (Block *) malloc(sizeof(Block));
    b3 = (Block *) malloc(sizeof(Block));
    b4 = (Block *) malloc(sizeof(Block));
    b5 = (Block *) malloc(sizeof(Block));
    b1cp = (Block *) malloc(sizeof(Block));
    b2cp = (Block *) malloc(sizeof(Block));
    b4cp = (Block *) malloc(sizeof(Block));
    b1->type = 1;
    b1->chunk = chunk1;
    b2->type = 1;
    b2->chunk = chunk2;
    b3->type = 2;
    b3->chunk = chunk1;
    b4->type = 2;
    b4->chunk = chunk1;
    b5->type = 3;
    b5->chunk = chunk2;

    // Creating sets
    intersection_result = (Set *) malloc(sizeof(Set));
    left = (Set *) malloc(sizeof(Set));
    right = (Set *) malloc(sizeof(Set));
    sub_set = (Set *) malloc(sizeof(Set));
    set_create(sub_set, cmp_block, free);
    set_create(left, cmp_block, free);
    set_create(right, cmp_block, free);

    // Creating right set
    set_add(right, b1);
    set_add(right, b2);
    set_add(right, b3);

    // Creating left set
    set_add(left, b1);
    set_add(left, b2);
    set_add(left, b4);
    set_add(left, b5);

    // Create sub set, Add the copy of b1, b2 and b4 as subset, it's our expected intersection result
    memcpy(b1cp, b1, sizeof(Block));
    memcpy(b2cp, b2, sizeof(Block));
    memcpy(b4cp, b4, sizeof(Block));
    set_add(sub_set, b1cp);
    set_add(sub_set, b2cp);
    set_add(sub_set, b4cp);

    ASSERT_TRUE(set_intersection(intersection_result, left, right));

    // verifier le résultat de l'intersection des deux ensembles
    ASSERT_EQ(set_size(intersection_result), 3);
    ASSERT_TRUE(set_isSubset(intersection_result, sub_set));

    set_destroy(sub_set);
    free(sub_set);
    void *delete_value = b1;
    ASSERT_TRUE(set_remove(left, &delete_value));
    delete_value = b5;
    ASSERT_FALSE(set_remove(intersection_result, &delete_value));

    set_destroy(intersection_result);
    set_destroy(left);
    free(right);

    free(chunk1);
    free(chunk2);
}


#endif //COLLECTIONS_COMMONS_SET_TEST_H
