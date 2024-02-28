//
// Created by maxim on 28/02/2024.
//
#include "hashmap.h"

bool hashmap_create(HashMap *map,
                    int containers,
                    int (*hash)(const void *key),
                    bool (*equals)(const void *key1, const void *key2),
                    void(*destroy)(void *value)) {
    int i;

    // Try To Allocate memory space for the linked hash table

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
    lhtbl_destroy(map->hashTable);
    memset(map, 0, sizeof(HashMap));
}

bool hashmap_containsKey(const HashMap *map, void **value) {
    LinkedElement *current_element;
    int current_container;

    // Hash the given key value
    current_container = map->hashTable->hash(*value) % map->hashTable->containers;

    // Search the value inside the current container

    for (current_element = list_first(&map->hashTable->hashtable[current_container]);
         current_element != NULL; current_element = list_next(current_element)) {
        SimpleEntry *current_entry = (SimpleEntry *) list_value(current_element);
        if (map->hashTable->equals(*value, current_entry->key)) {
            *value = list_value(current_element);
            return true;
        }
    }

    return false;
}

bool hashmap_put(HashMap *map, void *key, void *value) {
    bool result = false;

    if (hashmap_containsKey((const HashMap *) map->hashTable, key)) {
        void *old_value = value;
        if (hashmap_replace(map, key, &old_value)) {
            free(old_value);
            return true;
        }
    } else {
        int container;

        // Hash the given key with the user function
        container = map->hashTable->hash(key) % map->hashTable->containers;

        SimpleEntry *new_entry = (SimpleEntry *) malloc(sizeof(SimpleEntry));
        new_entry->key = key;
        new_entry->value = value;
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

bool hashmap_addEntry(HashMap *map, SimpleEntry *entry) {
    bool result = false;

    if (hashmap_containsKey((const HashMap *) map->hashTable, entry->key)) {
        void *old_value = entry->value;
        if (hashmap_replace(map, entry->key, &old_value)) {
            free(old_value);
            return true;
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

}