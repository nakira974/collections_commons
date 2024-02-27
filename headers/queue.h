/**
 * @file queue.h
 * @brief This file contains the API for abstract Queue collections
 * @author Maxime Loukhal
 * @date 21/02/2024
 */
#ifndef COLLECTIONS_COMMONS_QUEUE_H
#define COLLECTIONS_COMMONS_QUEUE_H
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

#include "list.h"

/**
* @brief Data structure definition for a generic queue
* */
typedef LinkedList Queue;

/**
 * @brief Add an element at the end of the specified queue
 * @param queue The queue to add the first element in
 * @param value Element to be added at the end of the queue
 * @complexity O(1)
 * @return
 */
bool queue_enqueue(Queue *queue, const void* value);

/**
 * @brief Remove the first element of the specified queue
 * @param queue Queue to remove the first element in
 * @param value Reference to the first queue's element
 * @complexity O(1)
 * @return A reference to the first queue's element
 */
bool queue_dequeue(Queue * queue, void *value);

#ifdef __cplusplus

/***
* @brief Inline function that evaluates the number of elements inside the specified queue
* @return The current element count of the current list
* @complexity O(1)
*/
inline int queue_size(LinkedList *queue){
    return queue->size;
};

/**
 * @brief Inline function that peeks the first element of the queue without unstacking it
 * @param queue Queue to peek the first element in
 * @return The current first element of the queue
 * @complexity O(1)
 */
inline void * queue_peek(Queue  * queue){
    return ((queue)->head == nullptr ? nullptr : (queue)->head->value);
}

/**
 * @brief Creates a default queue structure that can be used for other operations
 * @param queue Reference to the queue to create
 * @param destroy Delegate user function for later destruction of a single element the current queue
 * @complexity O(1)
 */
inline void queue_create(Queue * queue, void( *destroy)(void *value)){
    list_create(queue, destroy);
}

/**
 * @brief Destroy the specified queue, after the call no other further operations will be permit
 * @param queue Reference of the queue to destroy false otherwise
 * @complexity O(n) where n is the number of elements in the current list
 */

inline void queue_destroy(Queue * queue){
    list_destroy(queue);
}

/**
 * @brief Inline function that returns a random element from the queue
 */
static inline LinkedElement *queue_peek_random(Queue* queue){
    return list_get_random(queue);
}
#else

/**
 * @brief Macro that evaluates the queue creation
 * @complexity O(1)
 */
#define queue_create list_create

/**
 * @brief Macro that evaluates queue destruction
 * @complexity O(n) where n is the number of elements in the current list
 */
#define queue_destroy list_destroy

/**
 * @brief Macro that evaluate peek the first element of the queue without unstacking it
 * @param queue Queue to peek the first element in
 * @return The current first element of the queue*
 * @complexity O(1)
 */
#define queue_peek(queue) ((queue)->head == NULL ? NUll : (queue)->head->value)

/***
* @brief Macro that evaluates the number of elements inside the specified queue
* @return The current element count of the current list
* @complexity O(1)
*/
#define queue_size list_size

/**
 * @brief Macro that evaluates a random element from the queue and returns it
 */
#define queue_peek_random(queue) list_get_random
#endif


#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_QUEUE_H
