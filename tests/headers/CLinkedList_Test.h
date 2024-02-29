//
// Created by maxim on 21/02/2024.
//

#ifndef COLLECTIONS_COMMONS_CLINKEDLIST_TEST_H
#define COLLECTIONS_COMMONS_CLINKEDLIST_TEST_H

#include <gtest/gtest.h>
#include "clist.h"

class CLinkedList_Test : public ::testing::Test{
public:
    typedef struct Page {
        int numero;
        int reference;
    } Page;

protected:
    ClinkedList* obj;

    static void destroy(void *value);
    int replace_page(CLinkedElement **current);

    void SetUp() override {
// Code exécuté avant chaque test
        obj = (ClinkedList *)malloc(sizeof(ClinkedList));
        clist_create(obj, destroy);
    }


    void TearDown() override {
// Code exécuté après chaque test
        clist_destroy(obj);
    }


};
TEST_F(CLinkedList_Test, PageTest) {
    Page *page = new Page{1, 5};

    ASSERT_EQ(page->numero, 1);
    ASSERT_EQ(page->reference, 5);

    delete page;
}

TEST_F(CLinkedList_Test, ReplacePageTest) {
    for (int i = 10; i >= 0; --i) {
        clist_add(obj, clist_first(obj), new Page{i, i-1});
    }
    CLinkedElement *current = obj->head;
    int replacedPage = replace_page(&current);

    ASSERT_EQ(replacedPage, 1);
}

TEST_F(CLinkedList_Test, PerformanceTest) {
    // Vérifier les performances en ajoutant et supprimant un grand nombre d'éléments
    for (int i = 0; i < 100000; ++i) {
        clist_add(obj, clist_first(obj), new Page{i, i+1});
    }
    CLinkedElement *current_element;

    // Remove random element until the list is not empty
    for(current_element= clist_getRandom(obj); clist_size(obj) > 0; current_element= clist_next(current_element)){
        void *value = nullptr;
        clist_remove(obj,current_element , &value);
        delete static_cast<Page*>(value);
    }

    EXPECT_EQ(clist_size(obj), 0);
}

#endif //COLLECTIONS_COMMONS_CLINKEDLIST_TEST_H
