//
// Created by maxim on 28/02/2024.
//

#include "collections_utils.h"

bool lhtbl_create(LinkedHashTable *lhtbl,
                  int containers,
                  int (*hash)(const void *key),
                  bool (*equals)(const void *key1, const void *key2),
                  void(*destroy)(void *value)) {
    if (hash == NULL || equals == NULL || destroy == NULL) return false;

    int i;

    // Allocate memory space for the linked hash table

    if ((lhtbl->hashtable = (LinkedList *) malloc(containers * sizeof(LinkedList))) == NULL) return false;

    // Creating containers
    lhtbl->containers = containers;

    for (i = 0; i < lhtbl->containers; i++)
        list_create(&lhtbl->hashtable[i], destroy);

    lhtbl->hash = hash;
    lhtbl->equals = equals;
    lhtbl->destroy = destroy;
    lhtbl->size = 0;

    return true;
}

void lhtbl_destroy(LinkedHashTable *lhtbl) {
    int i;

    for (i = 0; i < lhtbl->size; i++)
        list_destroy(&lhtbl->hashtable[i]);

    // Cleaning the memory location allocate to the internal hashtable

    free(lhtbl->hashtable);

    // Erasing the structure in case of
    memset(lhtbl, 0, sizeof(LinkedHashTable));
}

bool lhtbl_put(LinkedHashTable *lhtbl, const void *value) {
    void *temp;
    int container;
    bool result = false;

    temp = (void *) value;
    // If the value is already in the table return false
    if (lhtbl_contains(lhtbl, &temp)) return result;

    // Hash the given key with the user function
    container = lhtbl->hash(value) % lhtbl->containers;

    // Add the value inside the result container

    if ((result = list_add(&lhtbl->hashtable[container], NULL, value))) lhtbl->size++;

    return result;
}

bool lhtbl_remove(LinkedHashTable *lhtbl, void **value) {
    LinkedElement *current_element, *last_element;
    int current_container;
    current_container = lhtbl->hash(*value) % lhtbl->containers;

    // Search for the value inside the current container
    last_element = NULL;

    for (current_element = list_first(&lhtbl->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        // If the target value if equals to the current container element, then remove it
        if (lhtbl->equals(*value, list_value(current_element))) {
            // Remove the value from the current container
            if (list_remove(&lhtbl->hashtable[current_container], last_element, value)) {
                lhtbl->size--;
                return true;
                // Can't remove the data from the current container
            } else return false;
        }
        last_element = current_element;
    }

    // The given value to remove has not been found in the given linked hash table
    return false;
}

bool lhtbl_contains(const LinkedHashTable *lhtbl, void **value) {
    LinkedElement *current_element;
    int current_container;

    // Hash the given key value
    current_container = lhtbl->hash(*value) % lhtbl->containers;

    // Search the value inside the current container

    for (current_element = list_first(&lhtbl->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        if (lhtbl->equals(*value, list_value(current_element))) {
            *value = list_value(current_element);
            return true;
        }
    }

    return false;
}


void **lhtbl_toArray(LinkedHashTable *hashTable) {
    if (hashTable == NULL || hashTable->size == 0) return NULL;
    void **result;
    if ((result = (void **) malloc(hashTable->size * sizeof(void *))) == NULL) return NULL;
    int count = 0;
    LinkedElement *current_element;
    for (int i = 0; i < hashTable->size; i++) {
        if (list_size(&hashTable->hashtable[i]) > 0) {
            for (current_element = list_first(&hashTable->hashtable[i]);
                 current_element != NULL; current_element = list_next(current_element)) {
                result[count] = current_element->value;
                count++;
            }
            count = 0;
        }
    }
    return result;
}


DLinkedList *lhtbl_toList(LinkedHashTable *hashTable) {
    if (hashTable == NULL || hashTable->size == 0) return NULL;
    DLinkedList *result;
    if ((result = (DLinkedList *) malloc(sizeof(DLinkedList))) == NULL) return NULL;
    dlist_create(result, hashTable->destroy);
    LinkedElement *current_element;
    for (int i = 0; i < hashTable->size; i++) {
        if (list_size(&hashTable->hashtable[i]) > 0) {
            for (current_element = list_first(&hashTable->hashtable[i]);
                 current_element != NULL; current_element = list_next(current_element)) {
                dlist_add(result, dlist_first(result), current_element->value);
            }
        }
    }
    return result;
}