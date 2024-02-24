/**
 * @file sort.h
 * @brief This file contains the API for page replacing using second chance algorithm
 * @author Maxime Loukhal
 * @date 24/02/2024
 */

#ifndef COLLECTIONS_COMMONS_PAGE_H
#define COLLECTIONS_COMMONS_PAGE_H
#include "clist.h"
/**
 * @brief Data structure of a Page
 */
typedef struct Page {
    /**
     * @brief Page's id
     */
    int id;
    /**
     * Page's state
     */
    bool state;
}Page;

/**
 * @brief Use the second chance algorithm to loop in a circular list of Pages until it find one to replace
 * @param current
 * @return The id of the removed page
 */
int page_replace(CLinkedElement **current);
#endif //COLLECTIONS_COMMONS_PAGE_H
