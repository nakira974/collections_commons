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
    CLinkedElement *current = obj->head;
    int replacedPage = replace_page(&current);

    ASSERT_EQ(replacedPage, 0); // Remplacer la page avec un autre numéro
}

TEST_F(CLinkedList_Test, PerformanceTest) {
    // Vérifier les performances en ajoutant et supprimant un grand nombre d'éléments
    for (int i = 0; i < 100000; ++i) {
        clist_add(obj, obj->head, new Page{i, i+1});
    }

    for (int i = 0; i < 100000; ++i) {
        void *value = nullptr;
        clist_remove(obj, obj->head, &value);
        delete static_cast<Page*>(value);
    }
}

#endif //COLLECTIONS_COMMONS_CLINKEDLIST_TEST_H
