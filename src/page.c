//
// Created by maxim on 24/02/2024.
//

#include "page.h"


int page_replace(CLinkedElement **current) {
    // Second chance algorithm
    // Infinite loop until one page has been replaced

    while (((Page *) (*current)->value)->state) {
        ((Page *) (*current)->value)->state = false;
        *current = clist_next(*current);
    }

    return ((Page *) (*current)->value)->id;
}