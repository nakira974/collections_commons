//
// Created by maxim on 28/02/2024.
//

#include "lhtbl.h"

bool lhtbl_create(LinkedHashTable *lhtbl,
                  int containers,
                  int (*hash)(int table_size, const void *key),
                  int (*equals)(const void* key1, const void* key2),
                  void(*destroy)(void *value)){

    int i;

    // Allocate memory space for the linked hash table

    if((lhtbl->hashtable = (LinkedList *) malloc(containers * sizeof(LinkedList))) == NULL) return false;

    // Creating containers
    lhtbl->containers = containers;

    for(i = 0; i< lhtbl->containers;i++)
        list_create(&lhtbl->hashtable[i], destroy);

    lhtbl->hash = hash;
    lhtbl->equals = equals;
    lhtbl->destroy = destroy;
    lhtbl->size = 0;

    return true;
}

void lhtbl_destroy(LinkedHashTable *lhtbl){
    int i;

    for(i=0;i<lhtbl->size;i++)
        list_destroy(&lhtbl->hashtable[i]);

    // Cleaning the memory location allocate to the internal hashtable

    free(lhtbl->hashtable);

    // Erasing the structure in case of
    memset(lhtbl, 0, sizeof(LinkedHashTable));
}

bool lhtbl_put(LinkedHashTable *lhtbl, const void* value){
    void *temp;
    int container;
    bool result = false;

    temp = (void *) value;
    // If the value is already in the table return false
    if(lhtbl_containsKey(lhtbl, &temp)) return result;

    // Hash the given key with the user function
    container = lhtbl->hash(lhtbl->size, value) % lhtbl->containers;

    // Add the value inside the result container

    if((result = list_add(&lhtbl->hashtable[container], NULL, value))) lhtbl->size++;

    return result;
}

bool lhtbl_remove(LinkedHashTable *lhtbl, void** value){
    LinkedElement *current_element,*last_element;
    int current_container;
    current_container = lhtbl->hash(lhtbl->size, *value) % lhtbl->containers;

    // Search for the value inside the current container
    last_element = NULL;

    for(current_element= list_first(&lhtbl->hashtable[current_container]); current_element != NULL; current_element = list_next(current_element)){
        // If the target value if equals to the current container element, then remove it
        if(lhtbl->equals(*value, list_value(current_element))){
            // Remove the value from the current container
            if(list_remove(&lhtbl->hashtable[current_container], last_element, value)){
                lhtbl->size--;
                return true;
                // Can't remove the data from the current container
            }else return false;
        }
        last_element = current_element;
    }

    // The given value to remove has not been found in the given linked hash table
    return false;
}

bool lhtbl_containsKey(const LinkedHashTable *lhtbl, void** value){
    LinkedElement *current_element;
    int current_container;

    // Hash the given key value
    current_container = lhtbl->hash(lhtbl->size, *value) % lhtbl->containers;

    // Search the value inside the current container

    for(current_element= list_first(&lhtbl->hashtable[current_container]); current_element != NULL; current_element= list_next(current_element) ){
        if(lhtbl->equals(*value, list_value(current_element))){
            *value = list_value(current_element);
            return true;
        }
    }

    return false;
}