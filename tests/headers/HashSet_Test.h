//
// Created by maxim on 2/03/2024.
//

#ifndef COLLECTIONS_COMMONS_HASHSET_TEST_H
#define COLLECTIONS_COMMONS_HASHSET_TEST_H
#include "gtest/gtest.h"
#include "set.h"
#include "hashset.h"
#include "block.h"

class HashSetTest : public testing::Test {
protected:
    HashSet *set;

    void SetUp() override {
        set = (HashSet *) malloc(sizeof(HashSet));
        // Creating 16 containers, because it works using an AVR ATmega328PB 8bit addressing blocks microprocessor
        hashset_create(set, 16, hash_block, cmp_block, free);
    }

    void TearDown() override {
        hashset_destroy(set);
    }
};


TEST_F(HashSetTest, BasicTest) {
    Chunk *chunk1,*chunk2;
    Block *b1,*b2,*b3,*b4;
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data=1;
    chunk2->data=2;
    b1 = (Block*) malloc(sizeof(Block));
    b2 = (Block*) malloc(sizeof(Block));
    b3 = (Block*) malloc(sizeof(Block));
    b4 = (Block*) malloc(sizeof(Block));
    b1->type = 1;
    b1->chunk = chunk1;
    b2->type = 1;
    b2->chunk = chunk2;
    b3->type = 2;
    b3->chunk = chunk1;
    b4->type = 2;
    b4->chunk = chunk1;
    ASSERT_TRUE(hashset_add(set, b1));
    ASSERT_TRUE(hashset_add(set, b2));
    ASSERT_TRUE(hashset_add(set, b3));
    ASSERT_FALSE(hashset_add(set, b4));

    void *temp = b4;
    // True because b3 represent that literal value evaluate by cmp_block function
    ASSERT_TRUE(hashset_contains(set, &temp));
    // The returned value is b3 because b4 == b3 and b3 is the element in the set
    ASSERT_EQ((Block*) temp,b3);
    temp = b1;
    ASSERT_TRUE(hashset_contains(set, &temp));
    ASSERT_EQ((Block*) temp,b1);
    ASSERT_EQ(hashset_size(set), 3);
    free(b4);
    free(chunk1);
    free(chunk2);
}

TEST_F(HashSetTest, UnionTest){
    Chunk *chunk1,*chunk2;
    Block *b1,*b2,*b3,*b4;
    HashSet * set1, *union_result;
    set1 = (HashSet *)malloc(sizeof(HashSet));
    union_result = (HashSet *)malloc(sizeof(HashSet));
    hashset_create(set1, 16, hashref, cmp_block, free);
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data=1;
    chunk2->data=2;
    b1 = (Block*) malloc(sizeof(Block));
    b2 = (Block*) malloc(sizeof(Block));
    b3 = (Block*) malloc(sizeof(Block));
    b4 = (Block*) malloc(sizeof(Block));
    b1->type = 1;
    b1->chunk = chunk1;
    b2->type = 1;
    b2->chunk = chunk2;
    b3->type = 2;
    b3->chunk = chunk1;
    b4->type = 2;
    b4->chunk = chunk1;
    hashset_add(set, b1);
    hashset_add(set,b2);
    hashset_add(set1,b3);
    hashset_add(set1,b4);
    ASSERT_TRUE(hashset_union(union_result, set, set1));

    // 3 and not 4, Because b4 and b3 are equals one of them will be skipped
    ASSERT_EQ(hashset_size(union_result), 3);
    hashset_destroy(set1);
    free(set1);
}

TEST_F(HashSetTest, HashSetDifferenceTest) {
    HashSet *difference_result, *left, *right;
    Chunk *chunk1,*chunk2;
    Block *b1,*b2,*b3,*b4,*b5;
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data=1;
    chunk2->data=2;
    b1 = (Block*) malloc(sizeof(Block));
    b2 = (Block*) malloc(sizeof(Block));
    b3 = (Block*) malloc(sizeof(Block));
    b4 = (Block*) malloc(sizeof(Block));
    b5 = (Block*) malloc(sizeof(Block));

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


    difference_result = (HashSet *)malloc(sizeof(HashSet));
    left = (HashSet *)malloc(sizeof(HashSet));
    right = (HashSet *)malloc(sizeof(HashSet));

    hashset_create(left, 16, hashref, cmp_block, free);
    hashset_create(right, 16, hashref, cmp_block, free);


    hashset_add(right,b1);
    hashset_add(right,b2);
    hashset_add(right,b3);

    hashset_add(left, b1);
    hashset_add(left,b2);
    hashset_add(left,b4);
    hashset_add(left, b5);

    ASSERT_TRUE(hashset_difference(difference_result, left, right));

    ASSERT_FALSE(hashset_equals(left, right));
    // Vérifier le résultat de la différence...

    ASSERT_EQ(hashset_size(difference_result), 1);

    void* delete_value = b1;
    ASSERT_TRUE(hashset_remove(left, &delete_value));
    delete_value = b5;
    ASSERT_TRUE(hashset_remove(difference_result, &delete_value));

    hashset_destroy(difference_result);
    hashset_destroy(left);
    free(right);

    free(chunk1);
    free(chunk2);
}

TEST_F(HashSetTest , IntersectionTest) {
    HashSet *intersection_result, *left, *right, *sub_set;
    Chunk *chunk1,*chunk2;
    Block *b1,*b2,*b3,*b4,*b5,*b1cp,*b2cp,*b4cp;

    // Creating chunks
    chunk1 = (Chunk *) malloc(sizeof(Chunk));
    chunk2 = (Chunk *) malloc(sizeof(Chunk));
    chunk1->data=1;
    chunk2->data=2;

    // Creating blocks
    b1 = (Block*) malloc(sizeof(Block));
    b2 = (Block*) malloc(sizeof(Block));
    b3 = (Block*) malloc(sizeof(Block));
    b4 = (Block*) malloc(sizeof(Block));
    b5 = (Block*) malloc(sizeof(Block));
    b1cp = (Block*) malloc(sizeof(Block));
    b2cp = (Block*) malloc(sizeof(Block));
    b4cp = (Block*) malloc(sizeof(Block));
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
    intersection_result = (HashSet *)malloc(sizeof(HashSet));
    left = (HashSet *)malloc(sizeof(HashSet));
    right = (HashSet *)malloc(sizeof(HashSet));
    sub_set = (HashSet *)malloc(sizeof(HashSet));
    hashset_create(sub_set, 16, hashref, cmp_block, free);
    hashset_create(left, 16, hashref, cmp_block, free);
    hashset_create(right, 16, hashref, cmp_block, free);
    // Creating right set
    hashset_add(right,b1);
    hashset_add(right,b2);
    hashset_add(right,b3);

    // Creating left set
    hashset_add(left, b1);
    hashset_add(left,b2);
    hashset_add(left,b4);
    hashset_add(left, b5);

    // Create sub set, Add the copy of b1, b2 and b4 as subset, it's our expected intersection result
    memcpy(b1cp ,b1,sizeof (Block));
    memcpy(b2cp ,b2,sizeof (Block));
    memcpy(b4cp ,b4,sizeof (Block));
    hashset_add(sub_set, b1cp);
    hashset_add(sub_set,  b2cp);
    hashset_add(sub_set,  b4cp);

    ASSERT_TRUE(hashset_intersection(intersection_result, left, right));

    // verifier le résultat de l'intersection des deux ensembles
    ASSERT_EQ(hashset_size(intersection_result), 3);
    ASSERT_TRUE(hashset_isSubset(intersection_result, sub_set));

    hashset_destroy(sub_set);
    free(sub_set);
    void* delete_value = b1;
    ASSERT_TRUE(hashset_remove(left, &delete_value));
    delete_value = b5;
    ASSERT_FALSE(hashset_remove(intersection_result, &delete_value));

    hashset_destroy(intersection_result);
    hashset_destroy(left);
    free(right);

    free(chunk1);
    free(chunk2);
}
#endif //COLLECTIONS_COMMONS_HASHSET_TEST_H
