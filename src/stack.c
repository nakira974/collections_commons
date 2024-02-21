//
// Created by maxim on 21/02/2024.
//

#include "stack.h"

bool stack_push(Stack *stack, const void *value){
    return list_add(stack, NULL, value);
}

bool stack_pop(Stack * stack, void **value){
    return list_remove(stack, NULL, value);
}