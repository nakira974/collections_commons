/**
 * @file dlist.h
 * @brief This file contains the API for Double Chained Linked List collections
 * @author Maxime Loukhal
 * @date 20/02/2024
 */
#ifndef COLLECTIONS_COMMONS_DLIST_H
#define COLLECTIONS_COMMONS_DLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#else
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#endif


/**
 * @brief Data structure definition for a double chained linked list generic element
 */
typedef struct DLinkedElement {
    /**
     * @brief Reference to the value of the current list element
     */
    void *value;
    /**
     * @brief Reference of the previous element of the current list element
     */
    struct DLinkedElement *previous;
    /**
     * @brief Reference to the next element of the current list element
     */
    struct DLinkedElement *next;
} DLinkedElement;

/**
 * @brief Data structure definition for generic double linked list type
 */
typedef struct DLinkedList {
    /**@brief Current size of the list*/
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
    DLinkedElement *head;
    /**
     * @brief Last element of the list
     */
    DLinkedElement *tail;
} DLinkedList;

/* ----- PUBLIC DEFINITIONS ----- */



/**
 * @brief Creates a default double linked list structure that can be used for other operations
 *
 * @param list Reference of the list to create
 * @param destroy Delegate user function for later destruction of a single element in the current list
 * @complexity O(1)
 * @see void dlist_destroy(DLinkedList * list)
 */
void dlist_create(DLinkedList *list, void( *destroy)(void *value));


/**
 * @brief Destroy the specified list, after the call no other further operations will be permit
 * @param list Reference of the list to destroy false otherwise
 * @complexity O(n) where n is the number of hashtable in the current list
 */
void dlist_destroy(DLinkedList *list);

/**
 * @brief Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, false otherwise
 *
 */
bool dlist_add(DLinkedList *list, DLinkedElement *element, const void *value);

/**
 * @brief Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, false otherwise
 *
 */
bool dlist_addBefore(DLinkedList *list, DLinkedElement *element, const void *value);

/**
 * @brief Remove a given entry from the current list, then returns a pointer on the value of the deleted entry
 * @param list Reference of the list to remove an entry
 * @param entry Element of the list to be removed
 * @param value Output pointer on the value of the deleted list entry reference
 * @complexity O(1)
 * @return true if the entry was correctly removed, false otherwise
 */
bool dlist_remove(DLinkedList *list, DLinkedElement *entry, void **value);

/**
 * @brief Returns a random element from the given list
 * @param list List to return a random element from
 * @param value Reference to a random element
 * @return true if a random element has been returned, false otherwise
 */
DLinkedElement *dlist_getRandom(DLinkedList *list);

/**
 * @brief Replace a specified element from the given list with the specified value
 * @param list List where to replace the element value
 * @param element Element to replace the value
 * @param value Value to replace
 * @return true if the given element's value was replaces, false otherwise
 */
bool dlist_replace(DLinkedList *list, DLinkedElement *element, void **value);
/* ----- MACRO C++ COMPATIBILITY -----*/
#ifdef __cplusplus

/***
 * @brief Inline function that evaluates the number of hashtable inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
inline int dlist_size(DLinkedList *list) {
    return list->size;
} ;

/***
 * @brief Inline function that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
inline DLinkedElement *dlist_first(DLinkedList *list) {
    return list->head;
} ;

/***
 * @brief Inline function that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
inline DLinkedElement *dlist_last(DLinkedList *list) {
    return list->tail;
} ;

/***
 * @brief Inline function that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, false otherwise
 * @complexity O(1)
 */
inline bool dlist_isFirst(DLinkedList *list, DLinkedElement *element) {
    return (element)->previous == nullptr;
} ;

/***
 * @brief Inline function that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, false otherwise
 * @complexity O(1)
 */
inline bool dlist_isLast(DLinkedList *list, DLinkedElement *element) {
    return (element)->next == nullptr;
} ;

/***
 * @brief Inline function that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
inline void *dlist_value(DLinkedElement *element) {
    return ((element)->value);
} ;

/***
 * @brief Inline function that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
inline DLinkedElement *dlist_next(DLinkedElement *element) {
    return (element)->next;
}

/***
 * @brief Inline function that evaluates the previous element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
inline DLinkedElement *dlist_previous(DLinkedElement *element) {
    return (element)->previous;
}

/* ----- C MACRO  -----*/
#else
/***
 * @brief Macro that evaluates the number of hashtable inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
#define dlist_size(list) ((list)->size)

/***
 * @brief Macro that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
#define dlist_first(list) ((list)->head)

/***
 * @brief Macro that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
#define dlist_last(list) ((list)->tail)

/***
 * @brief Macro that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, false otherwise
 * @complexity O(1)
 */
#define dlist_isFirst(list, element) ((element)->previous == NULL ? true : false )

/***
 * @brief Macro that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, false otherwise
 * @complexity O(1)
 */
#define dlist_isLast(list, element) ((element)->next == NULL ? true : false )

/***
 * @brief Macro that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
#define dlist_value(element) ((element)->value)


/***
 * @brief Macro that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define dlist_next(element) ((element)->next)

/***
 * @brief Macro that evaluates the previous element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define dlist_previous(element) ((element)->previous)
#endif

#ifdef __cplusplus
}
#endif


#endif //COLLECTIONS_COMMONS_DLIST_H
