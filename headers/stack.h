/**
 * @file clist.h
 * @brief This file contains the API for Stacks collections
 * @author Maxime Loukhal
 * @date 21/02/2024
 */
#ifndef COLLECTIONS_COMMONS_STACK_H
#define COLLECTIONS_COMMONS_STACK_H

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

#include "list.h"

/**
 * @brief Transmutation of LinkedList typedef into Stack
 */
typedef LinkedList Stack;

/**
 * @brief Push a value on the top of the stack, the reference to the value MUST stay accessible while it's in the stack
 * @param stack The stack to push value on
 * @param value The value to be pushed on top of stack
 * @return true if the value has been stacked, false otherwise
 * @complexity O(1)
 */
bool stack_push(Stack *stack, const void *value);

/**
 * @brief Unstack the on-top value of the specified stack
 * @param stack The stack to unstack a value on
 * @param value The value of the element stored on top of the stack
 * @return true if an element has been unstacked, false otherwise
 * @complexity O(1)
 */
bool stack_pop(Stack *stack, void **value);

#ifdef __cplusplus

/**
 * @brief Peek the first element of the stack without unstacking it
 */
inline void *stack_peek(Stack *stack) {
    return ((stack)->head == nullptr ? nullptr : (stack)->head->value);
}

/**
 * @brief Return the current stack size
 */
inline int stack_size(Stack *stack) {
    return list_size(stack);
}

/**
 * @brief Creates a default stack structure that can be used for other operations
 * @param stack Reference to the stack to create
 * @param destroy Delegate user function for later destruction of a single element the current stack
 * @complexity O(1)
 */
inline void stack_create(Stack *stack, void( *destroy)(void *value)) {
    list_create(stack, destroy);
}

/**
 * @brief Destroy the specified stack, after the call no other further operations will be permit
 * @param stack Reference of the stack to destroy false otherwise
 * @complexity O(n) where n is the number of hashtable in the current list
 */

inline void stack_destory(Stack *stack) {
    list_destroy(stack);
}

/**
 * @brief Inline function that returns a random element from the stack
 */
static inline LinkedElement *stack_peekRandom(Stack *stack) {
    return list_getRandom(stack);
}
#else

/**
 * @brief Peek the first element of the stack without unstacking it
 */
#define stack_peek(stack)((stack)->head == NULL ? NULL : (stack)->head->value)

/**
 * @brief Return the current stack size
 */
#define stack_size list_size

/**
 * @brief Creates a default stack structure that can be used for other operations
 * @param stack Reference to the stack to create
 * @param destroy Delegate user function for later destruction of a single element the current stack
 * @complexity O(1)
 */
#define stack_create list_create

/**
 * @brief Destroy the specified stack, after the call no other further operations will be permit
 * @param stack Reference of the stack to destroy false otherwise
 * @complexity O(n) where n is the number of hashtable in the current list
 */
#define stack_destroy list_destroy

/**
 * @brief Macro that evaluates a random element from the queue and returns it
 */
#define stack_peek_random(stack) list_getRandom
#endif

#ifdef __cplusplus
}
#endif


#endif //COLLECTIONS_COMMONS_STACK_H
