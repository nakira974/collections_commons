//
// Created by maxim on 20/02/2024.
//

#include "clist.h"

void clist_create(ClinkedList *list, void (*destroy)(void *value)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
}

void clist_destroy(ClinkedList *list) {
    void *value;

    while (clist_size(list) > 0) {
        if (clist_remove(list, list->head, (void **) &value) && list->destroy != NULL) {
            list->destroy(value);
        }
    }
    memset(list, 0, sizeof(ClinkedList));
}

bool clist_add(ClinkedList *list, CLinkedElement *element, const void *value) {
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

bool clist_remove(ClinkedList *list, CLinkedElement *element, void **value) {
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
