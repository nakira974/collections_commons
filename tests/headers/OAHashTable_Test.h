//
// Created by maxim on 5/03/2024.
//

#ifndef COLLECTIONS_COMMONS_OAHASHTABLE_TEST_H
#define COLLECTIONS_COMMONS_OAHASHTABLE_TEST_H
#include <gtest/gtest.h>

#include "ohtbl.h"
#include "hash_utils.h"
#include "exception.h"

class OAHashTableTest : public ::testing::Test
{
protected:
    typedef struct Page {
        int numero;
        int reference;
    } Page;

    OAHashTable *ohtbl;

    void SetUp() override {
        ;
        if((ohtbl = (OAHashTable*) malloc(sizeof (OAHashTable))) != nullptr){
            ohtbl_create(ohtbl, 10, hashref, hashref, cmp_int, free);
        }else{
            throw_exception();
        }

    }

    void TearDown() override {
        ohtbl_destroy(ohtbl);
    }
};

TEST_F(OAHashTableTest, TestLhtblPutAndGet) {
    Page* page = (Page*)malloc(sizeof(Page));
    page->numero = 1;
    page->reference = 100;

    ASSERT_TRUE(ohtbl_put(ohtbl, page));

    void* value = page;
    ASSERT_TRUE(ohtbl_contains(ohtbl, &value));
    Page* retrieved_page = (Page*)value;
    EXPECT_EQ(retrieved_page->numero, page->numero);
    EXPECT_EQ(retrieved_page->reference, page->reference);
}

TEST_F(OAHashTableTest, TestLhtblRemove) {
    Page* page = (Page*)malloc(sizeof(Page));
    page->numero = 1;
    page->reference = 100;

    ASSERT_TRUE(ohtbl_put(ohtbl, page));

    void* value = (void*) page;
    ASSERT_TRUE(ohtbl_remove(ohtbl, &value));

    Page* removed_page = (Page*)value;
    EXPECT_EQ(removed_page->numero, page->numero);
    EXPECT_EQ(removed_page->reference, page->reference);
}
#endif //COLLECTIONS_COMMONS_OAHASHTABLE_TEST_H
