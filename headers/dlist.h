//
// Created by maxim on 20/02/2024.
//

#ifndef COLLECTIONS_COMMONS_DLIST_H
#define COLLECTIONS_COMMONS_DLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Data structure definition for a simplae double linked list generic element
 */
typedef struct DLinkedElement {
    /**
     * Reference to the value of the current list element
     */
    void * value;
    /**
     * Reference of the previous element of the current list element
     */
    struct DLinkedElement *previous;
    /**
     * Reference to the next element of the current list element
     */
    struct DLinkedElement *next;
} DLinkedElement;

/**
 * Data structure definition for generic double linked list type
 */
typedef struct DLinkedList{
    /**Current size of the list*/
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
    DLinkedElement  *head;
    /**
     * Last element of the list
     */
    DLinkedElement *tail;
} DLinkedList;
/**
 * Creates a double linked list that can be used for other operations
 *
 * @param list Reference of the list to create
 * @param destroy Delegate function for later destruction of the current list
 * @complexity O(1)
 * @see void dlist_destroy(DLinkedList * list)
 */
void dlist_create(DLinkedList * list, void( * destroy)(void * value));


/**
 * Destroy the specified list, after the call no other further operations will be permit
 * @param list Reference of the list to destroy otherwise false
 * @complexity O(n) where n is the number of elements in the current list
 */
void dlist_destroy(DLinkedList * list);

/**
 * Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, otherwise false
 *
 */
bool dlist_add(DLinkedList *list, DLinkedElement * element, const void *value);

/**
 * Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, otherwise false
 *
 */
bool dlist_add_before(DLinkedList *list, DLinkedElement * element, const void *value);

/**
 * Remove from an element from the current list, then returns a pointer on the value of the deleted element
 * @param list Reference of the list to remove an element
 * @param element Element of the list to be removed
 * @param value Output pointer on the value of the deleted list element reference
 * @complexity O(1)
 * @return true if the element was correctly removed, otherwise false
 */
bool dlist_remove(DLinkedList * list, DLinkedElement * element, void **value);

/***
 * Macro that evaluates the number of elements inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
#define dlist_size(list) ((list)->size)

/***
 * Macro that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
#define dlist_first(list) ((list)->head)

/***
 * Macro that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
#define dlist_last(list) ((list)->tail)

/***
 * Macro that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, otherwise false
 * @complexity O(1)
 */
#define dlist_is_first(list, element) ((element)>previous == NULL ? true : false )

/***
 * Macro that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, otherwise false
 * @complexity O(1)
 */
#define dlist_is_last(list, element) ((element)>next == NULL ? true : false )

/***
 * Macro that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
#define dlist_value(element) ((element)->value)


/***
 * Macro that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define dlist_next(element) ((element)->next)

/***
 * Macro that evaluates the previous element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define dlist_previous(element) ((element)->previous)

#endif //COLLECTIONS_COMMONS_DLIST_H
