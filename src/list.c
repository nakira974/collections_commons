//
// Created by maxim on 20/02/2024.
//

#include <memory.h>
#include "list.h"

void list_create(LinkedList * list, void( * destroy)(void * value)){
    // Init the list
    list->size = 0;
    list->destroy=destroy;
    list->head=nullptr;
    list->tail=nullptr;
}

void list_destroy(LinkedList * list){
    // Remove each elements
    void **value= nullptr;
    while (list_size(list)>0) {
        if(list_remove(list,nullptr,(void **) &value) && list->destroy !=  nullptr){
            list->destroy(value);
        }
    }

    memset(list, 0, sizeof(LinkedList));
}

bool list_add(LinkedList *list, LinkedElement* element, const void *value){
    LinkedElement * new_element = nullptr;
    // If we can't allocate to create a new element then return false
    if((new_element =(LinkedElement * ) malloc(sizeof (LinkedElement)))== nullptr){
        return false;
    }

    new_element->value = (void * )value;
    // Insert the element inside the current list
    if(element==nullptr){
        // Head insertion
        if(list_size(list) == 0) list->tail = new_element;
            new_element->next = list->head;
            list->head = new_element;

            // Else where than head insertion
        }else{
            if(element->next == nullptr){
                list->tail=new_element;
            }
            new_element->next = element->next;
            element->next = new_element;
        }
        list->size++;

        return true;
}

bool list_remove(LinkedList * list, LinkedElement * element, void **value){
    LinkedElement * last_element = nullptr;

    // return false if the list is empty
    if(list_size(list) == 0)
        return false;

    if(element == nullptr){
        *value = list->head->value;
        last_element = list->head;
        list->head = list->head->next;

        if(list_size(list) ==1) list->tail == NULL;

    }else{
        if(element->next == nullptr) return false;

        *value = element->next->value;
        last_element = element->next;
        element->next = element->next->next;
        if(element->next == nullptr) list->tail = element;
    }
    free(last_element);
    list->size--;

    return true;
}
