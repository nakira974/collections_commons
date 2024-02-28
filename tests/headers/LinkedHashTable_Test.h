/**
 * @file sort.h
 * @brief This file contains the API for page frames management
 * @author Maxime Loukhal
 * @date 24/02/2024
 */
#ifndef COLLECTIONS_COMMONS_LINKEDHASHTABLE_TEST_H
#define COLLECTIONS_COMMONS_LINKEDHASHTABLE_TEST_H
#include <gtest/gtest.h>
#include "hashset.h"
#include "hash_utils.h"


class LinkedHashTableTest : public ::testing::Test
{
protected:
    typedef struct Page {
        int numero;
        int reference;
    } Page;

    LinkedHashTable *lhtbl;

    static void destroy(void *value);

    void SetUp() override {
       ;
        if(( lhtbl = (LinkedHashTable*) malloc(sizeof (LinkedHashTable))) != nullptr){
            lhtbl_create(lhtbl, 10, hashref, cmp_int, destroy);
        }else{
            throw_exception();
        }

    }

    void TearDown() override {
        lhtbl_destroy(lhtbl);
    }
};

void LinkedHashTableTest::destroy(void *value) {
    free(value);
}

TEST_F(LinkedHashTableTest, TestHashRefFunction) {
    int hash_val = hashref((void*)12345);
    EXPECT_TRUE(hash_val != 0);
}

TEST_F(LinkedHashTableTest, TestLhtblPutAndGet) {
    Page* page = (Page*)malloc(sizeof(Page));
    page->numero = 1;
    page->reference = 100;

    ASSERT_TRUE(lhtbl_put(lhtbl, page));

    void* value = page;
    ASSERT_TRUE(lhtbl_containsKey(lhtbl, &value));
    Page* retrieved_page = (Page*)value;
    EXPECT_EQ(retrieved_page->numero, page->numero);
    EXPECT_EQ(retrieved_page->reference, page->reference);
}

TEST_F(LinkedHashTableTest, TestLhtblRemove) {
    Page* page = (Page*)malloc(sizeof(Page));
    page->numero = 1;
    page->reference = 100;

    ASSERT_TRUE(lhtbl_put(lhtbl, page));

    void* value = (void*) page;
    ASSERT_TRUE(lhtbl_remove(lhtbl, &value));

    Page* removed_page = (Page*)value;
    EXPECT_EQ(removed_page->numero, page->numero);
    EXPECT_EQ(removed_page->reference, page->reference);
}
#endif //COLLECTIONS_COMMONS_LINKEDHASHTABLE_TEST_H
