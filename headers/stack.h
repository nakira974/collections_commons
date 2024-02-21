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
#define list_destroy

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

#define stack_peek(stack)((stack)->head == NULL ? NULL : (stack)->head->value)

#define stack_size list_size

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_STACK_H
