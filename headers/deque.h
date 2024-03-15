/**
 * @file deque.h
 * @brief This file contains the API for abstract Dequeue collections
 * @author Maxime Loukhal
 * @date 01/03/2024
 */
#ifndef COLLECTIONS_COMMONS_DEQUE_H
#define COLLECTIONS_COMMONS_DEQUE_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cpluscplus
#include <cstdlib>
#include <cstdbool>
#else
#include <stdlib.h>
#include <stdbool.h>
#endif

#include "dlist.h"

/**
* @brief Data structure definition for a generic deque
* */
typedef DLinkedList Deque;

/**
 * @brief Add an element at the end of the specified deque
 * @param deque The deque to add the first element in
 * @param value Element to be added at the end of the deque
 * @complexity O(1)
 * @return
 */
bool deque_enqueue(Deque *deque, const void *value);

/**
 * @brief Remove the first element of the specified deque
 * @param deque Deque to remove the first element in
 * @param value Reference to the first deque's element
 * @complexity O(1)
 * @return A reference to the first deque's element
 */
bool deque_dequeue(Deque *deque, void *value);

#ifdef __cplusplus

/***
* @brief Inline function that evaluates the number of hashtable inside the specified deque
* @return The current element count of the current list
* @complexity O(1)
*/
static inline int deque_size(Deque *deque) {
    return deque->size;
} ;

/**
 * @brief Inline function that peeks the first element of the deque without unstacking it
 * @param deque Deque to peek the first element in
 * @return The current first element of the deque
 * @complexity O(1)
 */
static inline void *deque_peek(Deque *deque) {
    return ((deque)->head == nullptr ? nullptr : (deque)->head->value);
}

/**
 * @brief Creates a default deque structure that can be used for other operations
 * @param deque Reference to the deque to create
 * @param destroy Delegate user function for later destruction of a single element the current deque
 * @complexity O(1)
 */
static inline void deque_create(Deque *deque, void( *destroy)(void *value)) {
    dlist_create(deque, destroy);
}

/**
 * @brief Destroy the specified deque, after the call no other further operations will be permit
 * @param deque Reference of the deque to destroy false otherwise
 * @complexity O(n) where n is the number of hashtable in the current list
 */

static inline void deque_destroy(Deque *deque) {
    dlist_destroy(deque);
}

/**
 * @brief Inline function that returns a random element from the deque
 */
static inline DLinkedElement *deque_peekRandom(Deque *deque) {
    return dlist_getRandom(deque);
}
#else

/**
 * @brief Macro that evaluates the deque creation
 * @complexity O(1)
 */
#define deque_create dlist_create

/**
 * @brief Macro that evaluates deque destruction
 * @complexity O(n) where n is the number of hashtable in the current list
 */
#define deque_destroy dlist_destroy

/**
 * @brief Macro that evaluate peek the first element of the deque without unstacking it
 * @param deque Deque to peek the first element in
 * @return The current first element of the deque*
 * @complexity O(1)
 */
#define deque_peek(deque) ((deque)->head == NULL ? NUll : (deque)->head->value)

/***
* @brief Macro that evaluates the number of hashtable inside the specified deque
* @return The current element count of the current list
* @complexity O(1)
*/
#define deque_size list_size

/**
 * @brief Macro that evaluates a random element from the deque and returns it
 */
#define deque_peekRandom(deque) dlist_getRandom
#endif


#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_DEQUE_H
