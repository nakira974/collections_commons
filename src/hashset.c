//
// Created by maxim on 28/02/2024.
//
#include "hashset.h"

/**
 * @brief Private method to add an element with a preconfigured value before a list member
 * @param list List to add a new element in
 * @param element Element from the list to add before
 * @param new_element Preconfigured element to add in the list
 * @return true if the new element was added before the list element in the given list, false otherwise
 */
bool hashset_addBefore(DLinkedList *list, DLinkedElement *element, DLinkedElement *new_element) {
    // Reject null hashtable except if list is empty
    if (element == NULL && dlist_size(list) != 0) return false;

    // Allocate a new memory space for the element
    if ((new_element = (DLinkedElement *) malloc(sizeof(DLinkedElement))) == NULL)
        return false;

    if (dlist_size(list) > 0) {
        // Empty list case
        list->head = new_element;
        list->head->previous = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    } else {
        // Non-empty list case

        // The new element is just before the target element
        new_element->next = element;
        // The new element is inserted between the target and its current previous
        new_element->previous = element->previous;

        // If we're on top of list then the new element become the head
        if (element->previous == NULL)
            list->head = new_element;
            // else before replacing the previous element we need to update the current previous element next reference to the new created element
        else element->previous->next = new_element;

        // finally replace the previous element
        element->previous = new_element;
    }

    list->size++;

    return true;
}

bool hashset_create(HashSet *set,
                    int containers,
                    int (*hash)(const void *key),
                    bool (*equals)(const void *key1, const void *key2),
                    void(*destroy)(void *value)) {

    // Try To Allocate memory space for the linked hash table
    if (set == NULL) return false;
    if ((set->hashTable = (LinkedHashTable *) malloc(sizeof(LinkedHashTable))) == NULL) return false;
    if (!lhtbl_create(set->hashTable, containers, hash, equals, destroy)) return false;
    // Init the set
    set->size = 0;
    set->equals = equals;
    set->destroy = destroy;
    if((set->elements = (DLinkedList*) malloc(sizeof (DLinkedList)))== NULL){
        // Destroy the hashtable before leaving
        lhtbl_destroy(set->hashTable);
        return false;
    }

    return true;
}

void hashset_destroy(HashSet *set) {
    if (set == NULL) return;
    dlist_destroy(set->elements);
    lhtbl_destroy(set->hashTable);
    memset(set, 0, sizeof(HashSet));
}

bool hashset_contains(HashSet *set, void **value) {
    if (value == NULL || set == NULL) return false;
    LinkedElement *current_element;
    int current_container;

    // Hash the given key value
    current_container = set->hashTable->hash(*value) % set->hashTable->containers;

    // Search the value inside the current container
    for (current_element = list_first(&set->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        // If the target value if equals to the current container element, then remove it
        DLinkedElement * current_setElement = ((DLinkedElement*)list_value(current_element));
        if (set->hashTable->equals(*value, current_setElement->value)) {
            *value = dlist_value(current_setElement);
            return true;
        }
    }

    return false;
}

bool hashset_add(HashSet *set, void *value){
    bool result = false;

    if (hashset_contains(set, &value)) {
        // The value is already in the set
        return false;
    } else {
        int container;

        // Hash the given key with the user function
        container = set->hashTable->hash(value) % set->hashTable->containers;

        DLinkedElement *new_element;
        if((new_element=(DLinkedElement *) malloc(sizeof(DLinkedElement))) == NULL) return false;
        new_element->value = value;
        // Add the current key value pair to the container
        if ((result = list_add(&set->hashTable->hashtable[container], NULL, new_element))) {
            result = hashset_addBefore(set->elements, dlist_first(set->elements), new_element);
            set->hashTable->size++;
            set->size++;
        }

    }
    return result;
}

bool hashset_remove(HashSet *set, void **value){
    if (set == NULL || set->size == 0) return false;
    bool result = false;
    void *temp = *value;
    if (!hashset_contains(set, value)) return result;

    LinkedElement *current_element, *last_element;
    int current_container;
    current_container = set->hashTable->hash(temp) % set->hashTable->containers;

    // Search for the value inside the current container
    last_element = NULL;

    for (current_element = list_first(&set->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        // If the target value if equals to the current container element, then remove it
        DLinkedElement * current_setElement = ((DLinkedElement*)list_value(current_element));
        if (set->hashTable->equals(*value, current_setElement->value)) {
            // Remove the value from the current container
            if (list_remove(&set->hashTable->hashtable[current_container], last_element, *value)) {
                dlist_remove(set->elements, current_setElement, *value);
                set->destroy(current_setElement);
                set->hashTable->size--;
                result = true;
                break;
                // Can't remove the data from the current container
            } else {
                result = false;
                break;
            }
        }
        last_element = current_element;
    }
    return result;
}