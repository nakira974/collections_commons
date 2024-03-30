//
// Created by maxim on 28/02/2024.
//
#include "hashmap.h"

/**
 * @brief Private function double like double linked list add
 * @param map Map to put a new entry in
 * @param last_entry Entry to add before
 * @param new_entry Entry to be added
 * @return true if the entry was added, false otherwise
 */
static bool push(HashMap *map, SimpleEntry *entry, SimpleEntry *new_entry);

/**
* @brief Private function like double linked map remove
* @param map Hashmap to remove an entry
* @param entry Entry to be removed from the hashmap
* @param value Pointer on entry value
* @return true if the entry was removed from the hashmap, false otherwise
*/
static bool pop(HashMap *map, SimpleEntry *entry, void **value);

/**
 * Private function to compare two entries based on their compareTo method inside a hashset
 * @return true if entries are equals false otherwise
 */
static bool cmp_entry(const void *entry1, const void *entry2);

static bool push(HashMap *map, SimpleEntry *entry, SimpleEntry *new_entry) {
    // Reject null hashtable except if list is empty
    if (entry == NULL && hashmap_size(map) != 0) return false;


    if (hashmap_size(map) == 0) {
        // Empty list case
        map->head = new_entry;
        map->head->last = NULL;
        map->head->next = NULL;
        map->tail = new_entry;
    } else {
        // Non-empty list case
        new_entry->next = entry->next;
        new_entry->last = entry;
        if (entry->next == NULL) map->tail = new_entry;
        else entry->next->last = new_entry;

        entry->next = new_entry;
    }

    map->size++;
    return true;
}

static bool pop(HashMap *map, SimpleEntry *entry, void **value) {
    // Do not authorize a null entry or in an empty map
    if (hashmap_size(map) == 0 || entry == NULL) return false;

    // Remove the entry from the map
    *value = entry->value;
    if (map->equals(entry->key, map->head->key)) {
        // The map become after deletion empty case
        map->head = entry->next;
        if (map->head == NULL)
            map->tail = NULL;
        else
            entry->next->last = NULL;
    } else {
        // The map does not become empty after deletion case
        entry->last->next = entry->next;

        if (entry->next == NULL)
            map->tail = entry->last;
        else entry->next->last = entry->last;
    }

    map->destroy(entry);

    map->size--;
    return true;
}

static bool cmp_entry(const void *entry1, const void *entry2) {
    if (entry1 == NULL || entry2 == NULL) return false;
    SimpleEntry *a = ((SimpleEntry *) entry1);
    SimpleEntry *b = ((SimpleEntry *) entry2);

    if (a->compareTo(a->key, b->key)) {
        return true;
    } else {
        return false;
    }

};

bool hashmap_create(HashMap *map,
                    int containers,
                    int (*hash)(const void *key),
                    bool (*equals)(const void *key1, const void *key2),
                    void(*destroy)(void *value)) {

    // Try To Allocate memory space for the linked hash table
    if (map == NULL) return false;
    if ((map->hashTable = (LinkedHashTable *) malloc(sizeof(LinkedHashTable))) == NULL) return false;
    if (!lhtbl_create(map->hashTable, containers, hash, equals, destroy)) return false;
    // Init the map
    map->size = 0;
    map->equals = equals;
    map->destroy = destroy;
    map->tail = NULL;
    map->head = NULL;

    return true;
}

void hashmap_destroy(HashMap *map) {
    if (map == NULL) return;
    SimpleEntry *current_entry;
    void *temp;
    for (current_entry = hashmap_first(map); current_entry != NULL; current_entry = hashmap_next(current_entry)) {
        if (!hashmap_removeEntry(map, current_entry, &temp)) return;
    }
    lhtbl_destroy(map->hashTable);
    memset(map, 0, sizeof(HashMap));
}

bool hashmap_containsKey(HashMap *map, void **value) {
    if (value == NULL || map == NULL) return false;
    LinkedElement *current_element;
    int current_container;

    // Hash the given key value
    current_container = map->hashTable->hash(*value) % map->hashTable->containers;

    // Search the value inside the current container

    for (current_element = list_first(&map->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        SimpleEntry *current_entry = (SimpleEntry *) list_value(current_element);
        if (map->hashTable->equals(*value, current_entry->key)) {
            *value = ((SimpleEntry *) list_value(current_element))->value;
            return true;
        }
    }

    return false;
}

bool hashmap_put(HashMap *map, void *key, void *value) {
    bool result = false;

    if (hashmap_containsKey(map, &key)) {
        void *old_value = value;
        if (hashmap_replace(map, key, &old_value)) {
            map->destroy(old_value);
            return true;
        }
    } else {
        int container;

        // Hash the given key with the user function
        container = map->hashTable->hash(key) % map->hashTable->containers;

        SimpleEntry *new_entry = (SimpleEntry *) malloc(sizeof(SimpleEntry));
        new_entry->key = key;
        new_entry->value = value;
        new_entry->compareTo = map->equals;
        // Add the current key value pair to the container
        if ((result = list_add(&map->hashTable->hashtable[container], NULL, new_entry))) {
            map->hashTable->size++;
            result = push(map, hashmap_first(map), new_entry);
        }

    }
    return result;
}

bool hashmap_addEntry(HashMap *map, SimpleEntry *entry) {
    bool result = false;

    if (hashmap_containsKey(map, &entry->key)) {
        void *old_value = entry->value;
        if (hashmap_replace(map, entry->key, &old_value)) {
            map->destroy(old_value);
            result = true;
        }
    } else {
        int container;

        // Hash the given key with the user function
        container = map->hashTable->hash(entry->key) % map->hashTable->containers;

        SimpleEntry *new_entry;
        if ((new_entry = (SimpleEntry *) malloc(sizeof(SimpleEntry))) == NULL) return false;
        memcpy(new_entry, entry, sizeof(SimpleEntry));
        // Add the current key value pair to the container
        if ((result = list_add(&map->hashTable->hashtable[container], NULL, new_entry))) {
            if (hashmap_size(map) == 0) map->tail = new_entry;
            new_entry->next = map->head;
            map->head = new_entry;
            result = true;
        }
    }
    return result;
}

bool hashmap_putIfAbsent(HashMap *map, void *key, void *value) {
    if (!hashmap_containsKey(map, &key)) {
        if (hashmap_put(map, key, value)) {
            return true;
        }
    }
    return false;
}

bool hashmap_replace(HashMap *map, void *key, void **value) {
    bool result = false;
    if (!hashmap_containsKey(map, &key)) return result;
    int container;

    // Hash the given key with the user function
    container = map->hashTable->hash(key) % map->hashTable->containers;
    // Replace the current key value in the container
    SimpleEntry *current_entry;
    LinkedElement *current_element;
    for (current_element = list_first(&map->hashTable->hashtable[container])->value;
         current_element != NULL; current_element = list_next(current_element)) {
        current_entry = (SimpleEntry *) current_element->value;
        if (map->equals(current_entry->key, key)) {
            void *temp = current_entry->value;
            current_entry->value = *value;
            value = temp;
            map->destroy(temp);
            result = true;
            break;
        }
    }
    return result;
}

bool hashmap_remove(HashMap *map, void **value) {
    if (map == NULL || map->size == 0) return false;
    bool result = false;
    void *temp = *value;
    if (!hashmap_containsKey(map, &temp)) return result;

    LinkedElement *current_element, *last_element;
    int current_container;
    current_container = map->hashTable->hash(*value) % map->hashTable->containers;

    // Search for the value inside the current container
    last_element = NULL;
    for (current_element = list_first(&map->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        // If the target value if equals to the current container element, then remove it
        SimpleEntry *current_entry = (SimpleEntry *) list_value(current_element);
        if (map->hashTable->equals(*value, current_entry->key)) {
            // Remove the value from the current container
            if (list_remove(&map->hashTable->hashtable[current_container], last_element, value)) {
                map->hashTable->size--;
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
    // If a removed operation occurred inside the hashtable, then compute deletion inside the entries collection
    if (result) {
        void *key_value;
        result = pop(map, *value, &key_value);
        *value = key_value;
    }
    return result;
}

bool hashmap_removeEntry(HashMap *map, SimpleEntry *entry, void **value) {
    bool result = false;
    void *temp = entry->key;
    if (!hashmap_containsKey(map, &temp)) return result;
    result = hashmap_remove(map, temp);
    value = temp;
    return result;
}



HashSet *hashmap_keySet(HashMap *map) {
    if (map == NULL || map->size == 0) return NULL;
    HashSet *result;
    if ((result = (HashSet *) malloc(sizeof(HashSet))) == NULL) return NULL;
    if (!hashset_create(result, map->hashTable->containers, map->hashTable->hash, map->equals, map->destroy)) {
        hashset_destroy(result);
        return NULL;
    }
    SimpleEntry *current_entry;
    for (current_entry = hashmap_first(map); current_entry != NULL; current_entry = hashmap_next(current_entry)) {
        if (!hashset_add(result, current_entry->key)) {
            hashset_destroy(result);
            free(current_entry);
            return NULL;
        };
    }
    return result;
}

HashSet *hashmap_entrySet(HashMap *map) {
    if (map == NULL || map->size == 0) return NULL;
    HashSet *result;
    if ((result = (HashSet *) malloc(sizeof(HashSet))) == NULL) return NULL;
    if (!hashset_create(result, map->hashTable->containers, map->hashTable->hash, cmp_entry, map->destroy)) {
        hashset_destroy(result);
        return NULL;
    }

    SimpleEntry *current_entry;
    for (current_entry = hashmap_first(map); current_entry != NULL; current_entry = hashmap_next(current_entry)) {
        if (!hashset_add(result, current_entry)) {
            hashset_destroy(result);
            free(current_entry);
            return NULL;
        };
    }
    return result;
}

DLinkedList *hashmap_values(HashMap *map) {
    if (map == NULL || map->size == 0) return NULL;
    DLinkedList *result;
    if ((result = (DLinkedList *) malloc(sizeof(DLinkedList))) == NULL) return NULL;
    SimpleEntry *current_entry;
    for (current_entry = hashmap_first(map); current_entry != NULL; current_entry = hashmap_next(current_entry)) {
        if (!dlist_add(result, dlist_first(result), current_entry->value)) {
            dlist_destroy(result);
            free(current_entry);
            return NULL;
        };
    }
    return result;
}