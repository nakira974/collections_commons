//
// Created by maxim on 25/03/2024.
//
#include "arrays_utils.h"

LinkedList *array_toList(void **array, void( *destroy)(void *value)){
    if(array == NULL) return NULL;
    LinkedList *result;
    if((result = (LinkedList*) malloc(sizeof (LinkedList))) == NULL) return NULL;
    list_create(result, destroy);
    for(size_t i = 0; i < array_size(array); i++){
        if(!list_add(result, NULL, array[i])){
            list_destroy(result);
            return NULL;
        };
    }
    return result;
}

DLinkedList *array_toDList(void **array, void( *destroy)(void *value)){
    if(array == NULL) return NULL;
    DLinkedList *result;
    if((result = (DLinkedList*) malloc(sizeof(DLinkedList))) == NULL) return NULL;
    dlist_create(result, destroy);
    for(size_t i= 0; i < array_size(array); i++){
        if(!dlist_add(result, dlist_first(result), array[i])){
            dlist_destroy(result);
            return NULL;
        }
    }
    return result;
}

CLinkedList *array_toCList(void **array, void( *destroy)(void *value)){
    if(array == NULL) return NULL;
    CLinkedList *result;
    if((result = (CLinkedList*) malloc(sizeof(CLinkedList))) == NULL) return NULL;
    clist_create(result, destroy);
    for(size_t i= 0; i < array_size(array); i++){
        if(!clist_add(result, clist_first(result), array[i])){
            clist_destroy(result);
            return NULL;
        }
    }
    return result;
}

Set *array_toSet(void **array, void( *destroy)(void *value), bool(*equals)(const void *value1, const void *value2)){
    if(array == NULL) return NULL;
    Set * result;
    if((result = (Set*) malloc(sizeof(Set))) == NULL) return NULL;
    set_create(result, equals, destroy);
    for(size_t i= 0; i < array_size(array); i++){
        if(!set_add(result, array[i])){
            continue;
        }
    }
    return result;
}