//
// Created by maxim on 20/02/2024.
//

#include <memory.h>
#include "list.h"

void create_list(List * list, void( * destroy)(void * value)){
    // Init the list
    list->size = 0;
    list->destroy=destroy;
    list->head=NULL;
    list->tail=NULL;
}

void destroy_list(List * list){
    // Remove each elements
    void **value= nullptr;
    while (size(list)>0) {
        if(remove(list,NULL,(void **) &value) && list->destroy !=  NULL){
            list->destroy(value);
        }
    }

    memset(list, 0, sizeof(List));
}

bool add(List *list, Node* element, const void *value){
    Node * new_element = nullptr;
    // If we can't allocate to create a new element then return false
    if((new_element =(Node * ) malloc(sizeof (Node)))== NULL){
        return false;
    }

    new_element->value = (void * )value;
    // Insert the element inside the current list
    if(element==NULL){
        // Head insertion
        if(size(list) == 0) list->tail = new_element;
            new_element->next = list->head;
            list->head = new_element;

            // Else where than head insertion
        }else{
            if(element->next == NULL){
                list->tail=new_element;
            }
            new_element->next = element->next;
            element->next = new_element;
        }
        list->size++;

        return true;
}

bool remove(List * list, Node * element, void **value){
    Node * last_element = nullptr;

    // return false if the list is empty
    if(size(list) == 0)
        return false;

    if(element == NULL){
        *value = list->head->value;
        last_element = list->head;
        list->head = list->head->next;

        if(size(list) ==1) list->tail == NULL;

    }else{
        if(element->next == NULL) return false;

        *value = element->next->value;
        last_element = element->next;
        element->next = element->next->next;
        if(element->next == NULL) list->tail = element;
    }
    free(last_element);
    list->size--;

    return true;
}
