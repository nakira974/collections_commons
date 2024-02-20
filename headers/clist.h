//
// Created by maxim on 20/02/2024.
//

#ifndef COLLECTIONS_COMMONS_CLIST_H
#define COLLECTIONS_COMMONS_CLIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

/**
 * Data structure for circular linked list element
 */
typedef struct CLinkedElement {
    /**
     * Value of the current list element
     */
    void *value;
    /**
     * Reference of the next value of the current list element
     */
    struct CLinkedElement *next;
} CLinkedElement;

/***
 * Data structure for a circular linked list
 */

typedef struct ClinkedList {
    /**
     * Current size of the list
     */
    int size;

    /**
    * Match handle
    *
    * @param val1 Left value to compare
    * @param val2 Right value to compare
    * @return true if left is equals to right, otherwise false
    */
    int (*match)(const void *val1, const void *val2);

    /**
     * Destroy handle
     * @param value Reference to value to destroy
     */
    void (*destroy)(void *value);

    /**
    * First element of the list
    */
    CLinkedElement *head;
} ClinkedList;

/* ----- PUBLIC DEFINITIONS ----- */

/**
 * Creates a circular linked list that can be used for other operations
 *
 * @param list Reference of the list to create
 * @param destroy Delegate function for later destruction of the current list
 * @complexity O(1)
 * @see void clist_destroy(ClinkedList * list)
 */
void clist_create(ClinkedList *list, void (*destroy)(void *value));

/**
 * Destroy the specified list, after the call no other further operations will be permit
 * @param list Reference of the list to destroy otherwise false
 * @complexity O(n) where n is the number of elements in the current list
 */
void clist_destroy(ClinkedList *list);

/**
 * Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, otherwise false
 *
 */
bool clist_add(ClinkedList *list, CLinkedElement *element, const void *value);

/**
 * Remove from an element from the current list, then returns a pointer on the value of the deleted element
 * @param list Reference of the list to remove an element
 * @param element Element of the list to be removed
 * @param value Output pointer on the value of the deleted list element reference
 * @complexity O(1)
 * @return true if the element was correctly removed, otherwise false
 */
bool clist_remove(ClinkedList *list, CLinkedElement *element, void **value);

/***
 * Macro that evaluates the number of elements inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
#define clist_size(list) ((list)->size)

/***
 * Macro that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
#define clist_first(list) ((list)->head);

/***
 * Macro that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
#define clist_value(element) ((element)->value);

/***
 * Macro that evaluates the previous element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define clist_next(element) ((element)->next)

#endif //COLLECTIONS_COMMONS_CLIST_H
