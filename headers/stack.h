//
// Created by maxim on 21/02/2024.
//

#ifndef COLLECTIONS_COMMONS_STACK_H
#define COLLECTIONS_COMMONS_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

/**
 * Transmutation of LinkedList typedef into Stack
 */
typedef LinkedList Stack;

/**
 * Push a value on the top of the stack, the reference to the value MUST stay accessible while it's in the stack
 * @param stack The stack to push value on
 * @param value The value to be pushed on top of stack
 * @return true if the value has been stacked, otherwise false
 * @complexity O(1)
 */
bool stack_push(Stack *stack, const void *value);

/**
 * Unstack the on-top value of the specified stack
 * @param stack The stack to unstack a value on
 * @param value The value of the element stored on top of the stack
 * @return true if an element has been unstacked, otherwise false
 * @complexity O(1)
 */
bool stack_pop(Stack *stack, void **value);

#ifdef __cplusplus

/**
 * Peek the first element of the stack without unstacking it
 */
inline void * stack_peek(Stack  * stack){
    return ((stack)->head == nullptr ? nullptr : (stack)->head->value);
}

/**
 * Return the current stack size
 */
inline int stack_size(Stack *stack){
    return list_size(stack);
}

/**
 * Creates a default stack structure that can be used for other operations
 * @param stack Reference to the stack to create
 * @param destroy Delegate user function for later destruction of a single element the current stack
 * @complexity O(1)
 */
inline void stack_create(Stack * stack,  void( *destroy)(void *value)){
    list_create(stack,destroy);
}

/**
 * Destroy the specified stack, after the call no other further operations will be permit
 * @param stack Reference of the stack to destroy otherwise false
 * @complexity O(n) where n is the number of elements in the current list
 */

inline void stack_destory(Stack * stack){
    list_destroy(stack);
}
#else

/**
 * Peek the first element of the stack without unstacking it
 */
#define stack_peek(stack)((stack)->head == NULL ? NULL : (stack)->head->value)

/**
 * Return the current stack size
 */
#define stack_size list_size

/**
 * Creates a default stack structure that can be used for other operations
 * @param stack Reference to the stack to create
 * @param destroy Delegate user function for later destruction of a single element the current stack
 * @complexity O(1)
 */
#define stack_create list_create

/**
 * Destroy the specified stack, after the call no other further operations will be permit
 * @param stack Reference of the stack to destroy otherwise false
 * @complexity O(n) where n is the number of elements in the current list
 */
#define stack_destroy list_destroy
#endif

#ifdef __cplusplus
}
#endif


#endif //COLLECTIONS_COMMONS_STACK_H
