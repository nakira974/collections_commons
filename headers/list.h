//
// Created by maxim on 20/02/2024.
//

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
 * Data structure definition for a simple chained linked list generic element
 */
typedef struct LinkedElement {
    /**
     * Generic value of the current element
     */
    void *value;
    /**
     * Next value of the current element
     */
    struct LinkedElement *next;
} LinkedElement;

/**
 * Data structure definition for generic linked list type
 */
typedef struct LinkedList {
    /**
     * Current size of the list
     */
    int size;

    /**
     * Match handle
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
     *  First element of the list
     */
    LinkedElement *head;
    /**
     * Last element of the list
     */
    LinkedElement *tail;
} LinkedList;

/* ----- PUBLIC DEFINITIONS ----- */


/**
 * Creates a default linked list structure that can be used for other operations
 *
 * @param list Reference of the list to create
 * @param destroy Delegate user function for later destruction of a single element the current list
 * @complexity O(1)
 * @see void list_destroy(LinkedList * list)
 */
void list_create(LinkedList *list, void( *destroy)(void *value));

/**
 * Destroy the specified list, after the call no other further operations will be permit
 * @param list Reference of the list to destroy otherwise false
 * @complexity O(n) where n is the number of elements in the current list
 */
void list_destroy(LinkedList *list);


/**
 * Insert a new element just after element parameter
 * @param list Reference of the list to add an element
 * @param element Reference element of the current list to add after
 * @param value A generic data to add after the element parameter
 * @complexity O(1)
 * @return true if the element was added to the current list, otherwise false
 *
 */
bool list_add(LinkedList *list, LinkedElement *element, const void *value);

/**
 * Remove from an element from the current list, then returns a pointer on the value of the deleted element
 * @param list Reference of the list to remove an element
 * @param element Element of the list to be removed
 * @param value Output pointer on the value of the deleted list element reference
 * @complexity O(1)
 * @return true if the element was correctly removed, otherwise false
 */
bool list_remove(LinkedList *list, LinkedElement *element, void **value);

/* ----- MACRO C++ COMPATIBILITY -----*/
#ifdef __cplusplus
/***
 * Inline function that evaluates the number of elements inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
inline int list_size(LinkedList *list){
    return list->size;
};


/***
 * Inline function that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
inline LinkedElement* list_first(LinkedList * list){
    return list->head;
};

/***
 * Inline function that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
inline LinkedElement * list_last(LinkedList * list){
    return list->tail;
};

/***
 * Inline function that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, otherwise false
 * @complexity O(1)
 */
inline bool list_is_first(LinkedList * list, LinkedElement  *element){
    return (list)->head == element;
};

/***
 * Inline function that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, otherwise false
 * @complexity O(1)
 */
inline bool list_is_last(LinkedList * list, LinkedElement  *element){
    return (list)->tail == element;
};

/***
 * Inline function that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
inline void *list_value(LinkedElement  *element){
    return ((element)->value);
};

/***
 * Inline function that evaluates the next element of the current list element
 * @return The reference to the next element of the current list element
 * @complexity O(1)
 */
inline LinkedElement *list_next(LinkedElement *element){
    if (element == nullptr) return nullptr;
    else return (element)->next == nullptr ? nullptr : (element)->next;
}

/* ----- C MACRO  -----*/
#else
/***
 * Macro that evaluates the number of elements inside the specified list
 * @return The current element count of the current list
 * @complexity O(1)
 */
#define list_size(list) ((list)->size)

/***
 * Macro that evaluates the first element of the specified list
 * @return The first element of the current list
 * @complexity O(1)
 */
#define list_first(list) ((list)->head)

/***
 * Macro that evaluates the last element of the specified list
 * @return The last element of the current list
 * @complexity O(1)
 */
#define list_last(list) ((list)->tail)

/***
 * Macro that evaluates if the specified element is the first element of the specified list
 * @return true if the element is the first of the current list, otherwise false
 * @complexity O(1)
 */
#define list_is_first(list, element) ((element) == (list)->head ? true : false )

/***
 * Macro that evaluates if the specified element is the last element of the specified list
 * @return true if the element is the last of the current list, otherwise false
 * @complexity O(1)
 */
#define list_is_last(list, element) ((element) == (list)->tail ? true : false )

/***
 * Macro that evaluates the value of a list element
 * @return The value stored inside a list element
 * @complexity O(1)
 */
#define list_value(element) ((element)->value)


/***
 * Macro that evaluates the next element of the current list element
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
