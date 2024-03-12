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
    if (dlist_size(list) == 0) {
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

bool hashset_create(HashSet *hashset,
                    int containers,
                    int (*hash)(const void *key),
                    bool (*equals)(const void *key1, const void *key2),
                    void(*destroy)(void *value)) {

    // Try To Allocate memory space for the linked hash table
    if (hashset == NULL) return false;
    if ((hashset->hashTable = (LinkedHashTable *) malloc(sizeof(LinkedHashTable))) == NULL) return false;
    if (!lhtbl_create(hashset->hashTable, containers, hash, equals, destroy)) return false;
    // Init the hashset
    hashset->size = 0;
    hashset->equals = equals;
    hashset->destroy = destroy;
    if ((hashset->elements = (DLinkedList *) malloc(sizeof(DLinkedList))) == NULL) {
        // Destroy the hashtable before leaving
        lhtbl_destroy(hashset->hashTable);
        return false;
    } else dlist_create(hashset->elements, free);


    return true;
}

void hashset_destroy(HashSet *hashset) {
    if (hashset == NULL) return;
    dlist_destroy(hashset->elements);
    list_destroy(hashset->hashTable->hashtable);
    hashset->hashTable->size = 0;
    lhtbl_destroy(hashset->hashTable);
    memset(hashset, 0, sizeof(HashSet));
}

bool hashset_contains(const HashSet *hashset, void **value) {
    if (value == NULL || hashset == NULL) return false;
    LinkedElement *current_element;
    int current_container;

    // Hash the given key value
    current_container = hashset->hashTable->hash(*value) % hashset->hashTable->containers;

    // Search the value inside the current container
    for (current_element = list_first(&hashset->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        // If the target value if equals to the current container element, then remove it
        DLinkedElement *current_setElement = ((DLinkedElement *) list_value(current_element));
        if (hashset->hashTable->equals(*value, current_setElement->value)) {
            *value = dlist_value(current_setElement);
            return true;
        }
    }

    return false;
}

bool hashset_add(HashSet *hashset, void *value) {
    bool result = false;

    if (hashset_contains(hashset, &value)) {
        // The value is already in the hashset
        return false;
    } else {
        int container;

        // Hash the given key with the user function
        container = hashset->hashTable->hash(value) % hashset->hashTable->containers;

        DLinkedElement *new_element;
        if ((new_element = (DLinkedElement *) malloc(sizeof(DLinkedElement))) == NULL) return false;
        new_element->value = value;
        new_element->next = NULL;
        new_element->previous = NULL;
        // Add the current key value pair to the container
        if ((result = list_add(&hashset->hashTable->hashtable[container], NULL, new_element))) {
            result = hashset_addBefore(hashset->elements, dlist_first(hashset->elements), new_element);
            if (result) {
                hashset->hashTable->size++;
                hashset->size++;
            }
        }

    }
    return result;
}

bool hashset_remove(HashSet *hashset, void **value) {
    if (hashset == NULL || hashset->size == 0) return false;
    bool result = false;
    void *temp = *value;
    if (!hashset_contains(hashset, value)) return result;

    LinkedElement *current_element, *last_element;
    int current_container;
    current_container = hashset->hashTable->hash(temp) % hashset->hashTable->containers;

    // Search for the value inside the current container
    last_element = NULL;

    for (current_element = list_first(&hashset->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        // If the target value if equals to the current container element, then remove it
        DLinkedElement *current_setElement = ((DLinkedElement *) list_value(current_element));
        if (hashset->hashTable->equals(*value, current_setElement->value)) {
            // Remove the value from the current container
            if (list_remove(&hashset->hashTable->hashtable[current_container], last_element, value)) {
                dlist_remove(hashset->elements, *value, value);
                hashset->hashTable->size--;
                hashset->size--;
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

bool hashset_union(HashSet *union_result, const HashSet *left, const HashSet *right) {
    DLinkedElement *current_element;
    void *value;

    // Create the union hashset
    hashset_create(union_result, left->hashTable->containers, left->hashTable->hash, left->equals, left->destroy);

    // Insertion of left hashset elements
    for (current_element = hashset_first(left);
         current_element != NULL; current_element = hashset_next(current_element)) {
        value = dlist_value(current_element);

        if (!hashset_add(union_result, value)) {
            hashset_destroy(union_result);
            return false;
        }
    }

    // Insertion of right hashset elements
    for (current_element = hashset_first(right);
         current_element != NULL; current_element = hashset_next(current_element)) {
        void *currentRef = &((DLinkedElement *) list_value(current_element))->value;
        if (hashset_contains(left, &currentRef)) continue;
        else {
            value = list_value(current_element);
            if (!hashset_add(union_result, value)) {
                hashset_destroy(union_result);
                return false;
            }
        }
    }
    return true;
}

bool hashset_intersection(HashSet *intersection_result, const HashSet *left, const HashSet *right) {
    DLinkedElement *current_element;
    void *value;

    // Create the intersection HashSet

    hashset_create(intersection_result, left->hashTable->containers, left->hashTable->hash, left->equals,
                   left->destroy);

    // intersection of elements in left and right hashset

    for (current_element = hashset_first(left);
         current_element != NULL; current_element = hashset_next(current_element)) {
        // If the current left element is in the right HashSet
        value = dlist_value(current_element);
        if (hashset_contains(right, &value)) {
            if (!hashset_add(intersection_result, value)) {
                hashset_destroy(intersection_result);
                return false;
            }
        }
    }
    return true;
}

bool hashset_difference(HashSet *difference_result, const HashSet *left, const HashSet *right) {
    DLinkedElement *current_element;
    void *value;

    // Creation of the difference HashSet
    hashset_create(difference_result, left->hashTable->containers, left->hashTable->hash, left->equals, left->destroy);

    // Insert elements of left non present in right
    for (current_element = hashset_first(left);
         current_element != NULL; current_element = hashset_next(current_element)) {
        // If the current left value is not in the right hashset
        value = dlist_value(current_element);
        if (!hashset_contains(right, &value)) {
            if (!hashset_add(difference_result, value)) {
                hashset_destroy(difference_result);
                return false;
            }
        }
    }
    return true;
}

bool hashset_isSubset(const HashSet *left, const HashSet *right) {
    DLinkedElement *current_element;

    // Quick test to eliminate some usual cases
    if (hashset_size(left) > hashset_size(right)) return false;
    // Determine if left is a subset of right
    for (current_element = hashset_first(left);
         current_element != NULL; current_element = hashset_next(current_element)) {
        // Validate one by one left elements in right hashset independently of their order
        void *value = dlist_value(current_element);
        if (!hashset_contains(right, &value)) return false;
    }
    return true;
}

bool hashset_equals(const HashSet *left, const HashSet *right) {
    DLinkedElement *current_element;
    // Quick test to eliminate usual cases

    if (hashset_size(left) != hashset_size(right)) return false;

    // Determine if left and right sets are equal
    for (current_element = hashset_first(left);
         current_element != NULL; current_element = hashset_next(current_element)) {
        // If there is one element of left not present in right, sets are not equal
        if (!hashset_contains(right, dlist_value(current_element))) return false;
    }

    return true;
}