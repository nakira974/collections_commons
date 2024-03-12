//
// Created by maxim on 20/02/2024.
//

#include "collections_utils.h"

void clist_create(CLinkedList *list, void (*destroy)(void *value)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
}

void clist_destroy(CLinkedList *list) {
    void *value;

    while (clist_size(list) > 0) {
        if (clist_remove(list, list->head, (void **) &value) && list->destroy != NULL) {
            list->destroy(value);
        }
    }
    memset(list, 0, sizeof(CLinkedList));
}

bool clist_add(CLinkedList *list, CLinkedElement *element, const void *value) {
    CLinkedElement *new_element = NULL;

    // If we've such enough place in the memory then continue
    if ((new_element = (CLinkedElement *) malloc(sizeof(CLinkedElement))) == NULL) return false;
    new_element->value = (void *) value;

    if (clist_size(list) == 0) {
        // Empty-list add case
        new_element->next = new_element;
        list->head = new_element;
    } else {
        // Non-empty list case
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;

    return true;
}

bool clist_remove(CLinkedList *list, CLinkedElement *element, void **value) {
    CLinkedElement *last_element = NULL;

    if (clist_size(list) == 0) return false;

    *value = element->next->value;
    if (element->next == element) {
        // Is last element case
        last_element = element->next;
        list->head = NULL;
    } else {
        // Not the latest element of the list case
        last_element = element->next;
        element->next = element->next->next;
    }
    free(last_element);
    list->size--;
    return true;
}

CLinkedElement *clist_getRandom(CLinkedList *list) {
    CLinkedElement *random_element;
    if (clist_size(list) == 0) return NULL;
    int rd_index = rand() % clist_size(list);
    int count = 0;

    for (random_element = clist_first(list);;random_element = clist_next(random_element)) {
        if (rd_index == count) {
            break;
        }
        count++;
    }
    return random_element;
}

bool clist_replace(CLinkedList *list, CLinkedElement *element, void **value) {
    if (list == NULL || element == NULL) return false;
    int i;
    CLinkedElement *current_element = clist_first(list);
    for (i = 0; i < clist_size(list); i++) {
        if (current_element == element) {
            void **temp = current_element->value;
            current_element->value = *value;
            value = temp;
            free(temp);
            break;
        }
        current_element = clist_next(current_element);
    }

    free(current_element);
    return true;
}


void **clist_toArray(CLinkedList *list){
    if(list == NULL || list->size == 0) return NULL;
    void** result;
    if((result = (void**) malloc(list->size*sizeof (void*))) == NULL) return NULL;
    CLinkedElement *current_element;
    int count =0;
    for(current_element= clist_first(list);count < list->size-1; current_element= clist_next(current_element)){
        result[count] = current_element->value;
        count++;
    }
    free(current_element);
    return result;
}


Set *clist_toSet(CLinkedList *list, bool(*equals)(const void *value1, const void *value2)){
    if(list == NULL || list->size == 0) return NULL;
    Set *result;
    if((result = (Set*) malloc(sizeof (Set))) == NULL) return NULL;
    set_create(result, equals, list->destroy);
    CLinkedElement *current_element;
    int count = 0;
    for(current_element= clist_first(list); count < list->size-1; current_element= clist_next(current_element)){
        set_add(result, current_element->value);
    }
    free(current_element);
    return result;
}


LinkedList *clist_toList(CLinkedList *list){
    if(list == NULL || list->size == 0) return NULL;
    LinkedList *result;
    if((result = (LinkedList*) malloc(sizeof (LinkedList))) == NULL) return NULL;
    list_create(result, list->destroy);
    CLinkedElement *current_element;
    int count =0;
    for(current_element= clist_first(list); count < list->size-1; current_element= clist_next(current_element)){
        list_add(result,NULL, current_element->value);
        count++;
    }
    free(current_element);
    return result;
}


DLinkedList *clist_toDList(CLinkedList *list){
    if(list == NULL || list->size == 0) return NULL;
    DLinkedList *result;
    if((result = (DLinkedList*) malloc(sizeof (DLinkedList))) == NULL) return NULL;
    dlist_create(result, list->destroy);
    CLinkedElement *current_element;
    int count = 0;
    for(current_element= clist_first(list); count < list->size-1; current_element= clist_next(current_element)){
        dlist_add(result,dlist_first(result), current_element->value);
        count++;
    }
    free(current_element);
    return result;
}
