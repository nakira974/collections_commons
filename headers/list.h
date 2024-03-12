/**
 * @file list.h
 * @brief This file contains the API for simple chained Linked List collections
 * @author Maxime Loukhal
 * @date 20/02/2024
 */
#ifndef COLLECTIONS_COMMONS_LIST_H
#define COLLECTIONS_COMMONS_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdlib>
#include <cstdbool>
#else
#include <stdlib.h>
#include <stdbool.h>
#endif

/**
 * @brief Data structure definition for a simple chained linked list generic element
 */
typedef struct LinkedElement {
    /**
     * @brief Generic value of the current element
     */
    void *value;
    /**
     * @brief Next value of the current element
     */
    struct LinkedElement *next;
} LinkedElement;

/**
 * @brief Data structure definition for generic linked list type
 */
typedef struct LinkedList {
    /**
     * @brief Current size of the list
     */
    int size;

    /**
     * @brief Match handle
     * @param left Left value to compare
     * @param right Right value to compare
     * @return true if left is equals to right, false otherwise
     */
    bool (*equals)(const void *left, const void *right);

    /**
     * @brief Destroy handle
     * @param value Reference to value to destroy
     */
    void (*destroy)(void *value);

    /**
     *  @brief First element of the list
     */
    LinkedElement *head;
    /**
     * @brief Last element of the list
     */
    LinkedElement *tail;
} LinkedList;

/* ----- PUBLIC DEFINITIONS ----- */


/**
 * @brief Creates a default linked list structure that can be used for other operations
 * @param list Reference of the list to create
 * @param destroy Delegate user function for later destruction of a single element the current list
 * @complexity O(1)
 * @see void list_destroy(LinkedList * list)
 */
void list_create(LinkedList *list, void( *destroy)(void *value));

/**
 * @brief Destroy the specified list, after the call no other further operations will be permit
 * @param list Reference of the list to destroy false otherwise
 * @complexity O(n) where n is the number of hashtable in the current list
 */
void list_destroy(LinkedList *list);


/**
 * @brief Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, false otherwise
 *
 */
bool list_add(LinkedList *list, LinkedElement *element, const void *value);

/**
 * @brief Remove a given element from the current list, then returns a pointer on the value of the deleted element
 * @param list Reference of the list to remove an element
 * @param element Element of the list to be removed
 * @param value Output pointer on the value of the deleted list element reference
 * @complexity O(1)
 * @return true if the element was correctly removed, false otherwise
 */
bool list_remove(LinkedList *list, LinkedElement *element, void **value);

/**
 * @brief Returns a random element from the given list
 * @param list List to return a random element from
 * @param random_element Reference to a random element
 * @return true if a random element was returned, false otherwise
 */
LinkedElement *list_getRandom(LinkedList *list);

/**
 * @brief Replace a specified element from the given list with the specified value
 * @param list List where to replace the element value
 * @param element Element to replace the value
 * @param value Value to replace
 * @return true if the given element's value was replaces, false otherwise
 */
bool list_replace(LinkedList *list, LinkedElement *element, void **value);

/* ----- MACRO C++ COMPATIBILITY -----*/
#ifdef __cplusplus
/**
 * @brief Inline function that evaluates the number of hashtable inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
inline int list_size(LinkedList *list) {
    return list->size;
} ;


/**
 * @brief Inline function that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
inline LinkedElement *list_first(LinkedList *list) {
    return list->head;
} ;

/**
 * @brief Inline function that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
inline LinkedElement *list_last(LinkedList *list) {
    return list->tail;
} ;

/**
 * @brief Inline function that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, false otherwise
 * @complexity O(1)
 */
inline bool list_isFirst(LinkedList *list, LinkedElement *element) {
    return (list)->head == element;
} ;

/**
 * @brief Inline function that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, false otherwise
 * @complexity O(1)
 */
inline bool list_isLast(LinkedList *list, LinkedElement *element) {
    return (list)->tail == element;
} ;

/**
 * @brief Inline function that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
inline void *list_value(LinkedElement *element) {
    return ((element)->value);
} ;

/**
 * @brief Inline function that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
inline LinkedElement *list_next(LinkedElement *element) {
    if (element == nullptr) return nullptr;
    else return (element)->next == nullptr ? nullptr : (element)->next;
}

/* ----- C MACRO  -----*/
#else
/**
 * @brief Macro that evaluates the number of hashtable inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
#define list_size(list) ((list)->size)

/**
 * @brief Macro that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
#define list_first(list) ((list)->head)

/**
 * @brief Macro that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
#define list_last(list) ((list)->tail)

/**
 * @brief Macro that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, false otherwise
 * @complexity O(1)
 */
#define list_isFirst(list, element) ((element) == (list)->head ? true : false )

/**
 * @brief Macro that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, false otherwise
 * @complexity O(1)
 */
#define list_isLast(list, element) ((element) == (list)->tail ? true : false )

/**
 * @brief Macro that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
#define list_value(element) ((element)->value)


/**
 * @brief Macro that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
#define list_next(element) ((element)->next)
#endif

#ifdef __cplusplus
}
#else

#endif


#endif //COLLECTIONS_COMMONS_LIST_H
