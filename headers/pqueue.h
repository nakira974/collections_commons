/**
 * @file pqueue.h
 * @brief This file contains the API for priority queues
 * @author Maxime Loukhal
 * @date 29/03/2024
 */

#ifndef COLLECTIONS_COMMONS_PQUEUE_H
#define COLLECTIONS_COMMONS_PQUEUE_H

#include "heap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data structure that defines a priority queue
 */
typedef Heap PriorityQueue;

#ifdef __cpluscplus

/**
 * @brief Inline function that initializes a PriorityQueue with its default values
 * @param pqueue PriorityQueue to initialized with its default values
 * @param compareTo User compare function
 * @param destroy User destroy function
 */
static inline void pqueue_create(PriorityQueue * pqueue, int (*compareTo) (const void*key1, const void*key2), void (*destroy) (void *key)){
    heap_create(pqueue, compareBlocks, destroy);
}

/**
 * @brief Inline function that destroys a given PriorityQueue
 * @param pqueue PriorityQueue to be destroyed
 */
static inline void pqueue_destroy(PriorityQueue *pqueue){
    heap_destroy(pqueue);
}

/**
 * @brief Inline function that adds a value into a given PriorityQueue
 * @param heap PriorityQueue where to add the value
 * @param value Value to be added
 * @return true if the value was added, otherwise false
 */
static inline bool pqueue_add(PriorityQueue * pqueue,  const void * key){
    return heap_add(pqueue, key);
}

/**
 * @brief Inline function that tries to get the given value in the given PriorityQueue
 * @param heap PriorityQueue to get the value in
 * @param key Value to get
 * @return true if the value was found, otherwise false
 */
static inline bool pqueue_poll(PriorityQueue *pqueue, void **key){
    return heap_poll(pqueue, key);
}

/**
 * @brief Inline function that peeks the highest priority element
 * @param pqueue PriorityQueue to peek element in
 */
static inline void * pqueue_peek(PriorityQueue *pqueue){
    return pqueue->tree == NULL ? NULL : pqueue->tree[0];
}
#else

/**
 * @brief Macro that initializes a PriorityQueue with its default values
 * @param pqueue PriorityQueue to initialized with its default values
 * @param compareTo User compare function
 * @param destroy User destroy function
 */
#define pqueue_create heap_create

/**
 * @brief Macro that destroys a given PriorityQueue
 * @param pqueue PriorityQueue to be destroyed
 */
#define pqueue_destroy heap_destroy

/**
 * @brief Macro that adds a value into a given PriorityQueue
 * @param heap PriorityQueue where to add the value
 * @param value Value to be added
 * @return true if the value was added, otherwise false
 */
#define pqueue_add heap_add

/**
 * @brief Macro that tries to get the given value in the given PriorityQueue
 * @param heap PriorityQueue to get the value in
 * @param key Value to get
 * @return true if the value was found, otherwise false
 */
#define pqueue_poll heap_poll

/**
 * @brief Macro that peeks the highest priority element
 * @param pqueue PriorityQueue to peek element in
 */
#define pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])
#endif

#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_PQUEUE_H
