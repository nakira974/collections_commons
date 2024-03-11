/**
 * @file clist.h
 * @brief This file contains the API for Circular Linked List collections
 * @author Maxime Loukhal
 * @date 20/02/2024
 */

#ifndef COLLECTIONS_COMMONS_CLIST_H
#define COLLECTIONS_COMMONS_CLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#else
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include "list.h"
#include "dlist.h"

#endif


/**
 * @brief Data structure for circular linked list element
 */
typedef struct CLinkedElement {
    /**
     * @brief Value of the current list element
     */
    void *value;
    /**
     * @brief Reference of the next value of the current list element
     */
    struct CLinkedElement *next;
} CLinkedElement;

/***
 * @brief Data structure for a circular linked list
 */

typedef struct CLinkedList {
    /**
     * @brief Current size of the list
     */
    int size;

    /**
    * @brief Match handle
    *
    * @param val1 Left value to compare
    * @param val2 Right value to compare
    * @return true if left is equals to right, false otherwise
    */
    bool (*equals)(const void *val1, const void *val2);

    /**
     * @brief Destroy handle
     * @param value Reference to value to destroy
     */
    void (*destroy)(void *value);

    /**
    * @brief First element of the list
    */
    CLinkedElement *head;
} CLinkedList;

/* ----- PUBLIC DEFINITIONS ----- */

/**
 * @brief Creates a default circular linked list structure that can be used for other operations
 *
 * @param list Reference of the list to create
 * @param destroy Delegate user function for later destruction of a single element in the current list
 * @complexity O(1)
 * @see void clist_destroy(CLinkedList * list)
 */
void clist_create(CLinkedList *list, void (*destroy)(void *value));

/**
 * @brief Destroy the specified list, after the call no other further operations will be permit
 * @param list Reference of the list to destroy false otherwise
 * @complexity O(n) where n is the number of hashtable in the current list
 */
void clist_destroy(CLinkedList *list);

/**
 * @brief Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, false otherwise
 *
 */
bool clist_add(CLinkedList *list, CLinkedElement *element, const void *value);

/**
 * @brief Remove a given element from the current list, then returns a pointer on the value of the deleted element
 * @param list Reference of the list to remove an element
 * @param element Element of the list to be removed
 * @param value Output pointer on the value of the deleted list element reference
 * @complexity O(1)
 * @return true if the element was correctly removed, false otherwise
 */
bool clist_remove(CLinkedList *list, CLinkedElement *element, void **value);

/**
 * @brief Returns a random element from the given list
 * @param list List to return a random element from
 * @param random_element Reference to a random element
 * @return true if a random element has been returned, false otherwise
 */
CLinkedElement *clist_getRandom(CLinkedList *list);

/**
 * @brief Replace a specified element from the given list with the specified value
 * @param list List where to replace the element value
 * @param element Element to replace the value
 * @param value Value to replace
 * @return true if the given element's value was replaces, false otherwise
 */
bool clist_replace(CLinkedList *list, CLinkedElement *element, void **value);

/**
 * @brief Convert the given list into an array
 * @param list List to be converted to array
 * @return Converted list to array
 */
void ** clist_toArray(CLinkedList *list);

/**
 * @brief Convert the given list into a set
 * @param list List to be converted to set
 * @return Converted list to set
 */
Set* clist_toSet(LinkedList *list, bool(*equals) (const void* value1, const void * value2));

/**
 * @brief Convert the given circular list into a list
 * @param list List to be converted to list
 * @return Converted circular list to list
 */
LinkedList *clist_toList(CLinkedList *list);

/**
 * @brief Convert the given circular list into a double linked list
 * @param list List to be converted to a double linked list
 * @return Converted circular list to double linked list
 */
DLinkedList *clist_toDList(CLinkedList *list);

/* ----- MACRO C++ COMPATIBILITY -----*/
#ifdef __cplusplus
/***
 * Inline function that evaluates the number of hashtable inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
inline int clist_size(CLinkedList *list) {
    return list->size;
} ;

/***
 * Inline function that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
inline CLinkedElement *clist_first(CLinkedList *list) {
    return list->head;
} ;

/***
 * Inline function that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, false otherwise
 * @complexity O(1)
 */
inline bool clist_isFirst(CLinkedList *list, CLinkedElement *element) {
    return (list)->head == element;
} ;

/***
 * Inline function that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
inline void *clist_value(CLinkedElement *element) {
    return ((element)->value);
} ;

/***
 * Inline function that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
inline CLinkedElement *clist_next(CLinkedElement *element) {
    return (element)->next;
}

/* ----- C MACRO  -----*/
#else
/**
 * @brief Macro that evaluates the number of hashtable inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
#define clist_size(list) ((list)->size)

/**
 * @brief Macro that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
#define clist_first(list) ((list)->head);

/**
 * @brief Macro that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, false otherwise
 * @complexity O(1)
 */
#define list_isFirst(list, element) ((element) == (list)->head ? true : false )

/**
 * @brief Macro that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
#define clist_value(element) ((element)->value);

/**
 * @brief Macro that evaluates the previous element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define clist_next(element) ((element)->next)
#endif

#ifdef __cplusplus
}
#endif


#endif //COLLECTIONS_COMMONS_CLIST_H
