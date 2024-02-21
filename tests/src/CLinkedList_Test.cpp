//
// Created by maxim on 21/02/2024.
//

#include "CLinkedList_Test.h"

int CLinkedList_Test::replace_page(CLinkedElement **current) {
    // Loop until we replace a page
    while(((Page * ) (*current)->value)->reference != 0){
        *current = clist_next(*current);
    }
    return (((Page * ) (*current)->value)->numero);
}

 void CLinkedList_Test::destroy(void *value) {
    if (value != NULL) {
        Page *page = (Page *)value;
         delete page;
    }
}
