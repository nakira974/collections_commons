//
// Created by maxim on 20/02/2024.
//

#include <memory.h>
#include "list.h"
#include "set.h"
#include "dlist.h"
#include "clist.h"

void list_create(LinkedList *list, void( *destroy)(void *value)) {
    // Init the list
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(LinkedList *list) {
    // Remove each hashtable
    void **value = NULL;
    while (list_size(list) > 0) {
        if (list_remove(list, NULL, (void **) &value) && list->destroy != NULL) {
            if (list->destroy != NULL && value != NULL) {
                list->destroy(value);
            }
        }
    }

    memset(list, 0, sizeof(LinkedList));
}

bool list_add(LinkedList *list, LinkedElement *element, const void *value) {
    LinkedElement *new_element = NULL;
    // If we can't allocate to create a new element then return false
    if ((new_element = (LinkedElement *) malloc(sizeof(LinkedElement))) == NULL) {
        return false;
    }

    new_element->value = (void *) value;
    // Insert the element inside the current list
    if (element == NULL) {
        // Head insertion
        if (list_size(list) == 0) list->tail = new_element;
        new_element->next = list->head;
        list->head = new_element;

        // Else where than head insertion
    } else {
        if (element->next == NULL) {
            list->tail = new_element;
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;

    return true;
}

bool list_remove(LinkedList *list, LinkedElement *element, void **value) {
    LinkedElement *last_element = NULL;

    // return false if the list is empty
    if (list_size(list) == 0)
        return false;

    if (element == NULL) {
        *value = list->head->value;
        last_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1) list->tail = NULL;

    } else {
        if (element->next == NULL) return false;

        *value = element->next->value;
        last_element = element->next;
        element->next = element->next->next;
        if (element->next == NULL) list->tail = element;
    }
    free(last_element);
    list->size--;

    return true;
}

LinkedElement *list_getRandom(LinkedList *list) {
    LinkedElement *random_element;
    if (list_size(list) == 0) return NULL;
    // Génère un index aléatoire dans la plage des indices valides du tableau.
    int rd_index = rand() % list_size(list);

    int count = 0;

    for (random_element = list_first(list); random_element != NULL; random_element = list_next(random_element)) {
        if (rd_index == count) {
            break;
        }
        count++;
    }
    return random_element;
}


bool list_replace(LinkedList *list, LinkedElement *element, void **value) {
    if (list == NULL || element == NULL) return false;
    LinkedElement *current_element;
    for (current_element = list_first(list); current_element != NULL; current_element = list_next(current_element)) {
        if (current_element == element) {
            void **temp = current_element->value;
            current_element->value = *value;
            value = temp;
            free(temp);
            break;
        }
    }

    free(current_element);
    return true;
}

void** list_toArray(LinkedList *list){
    if(list == NULL || list->size == 0) return NULL;
    void** result;
    if((result = (void**) malloc(list->size*sizeof (void*))) == NULL) return NULL;
    LinkedElement *current_element;
    int count =0;
    for(current_element= list_first(list); current_element!=NULL; current_element= list_next(current_element)){
        result[count] = current_element->value;
        count++;
    }
    free(current_element);
    return result;
}

struct Set* list_toSet(LinkedList *list, bool(*equals) (const void* value1, const void * value2)){
    if(list == NULL || list->size == 0) return NULL;
    struct Set *result;
    if((result = (struct Set*) malloc(sizeof (Set))) == NULL) return NULL;
    set_create((Set *) result, equals, list->destroy);
    LinkedElement *current_element;
    for(current_element= list_first(list); current_element!=NULL; current_element= list_next(current_element)){
        set_add((Set*) result, current_element->value);
    }
    free(current_element);
    return result;
}

struct DLinkedList *list_toDList(LinkedList *list){
    if(list == NULL || list->size == 0) return NULL;
    struct DLinkedList *result;
    if((result = (struct DLinkedList*) malloc(sizeof (DLinkedList))) == NULL) return NULL;
    dlist_create((DLinkedList *) result, list->destroy);
    LinkedElement *current_element;
    for(current_element= list_first(list); current_element!=NULL; current_element= list_next(current_element)){
        dlist_add((DLinkedList*) result,dlist_first((DLinkedList*) result), current_element->value);
    }
    free(current_element);
    return result;
}