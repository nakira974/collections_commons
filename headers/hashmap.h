/**
 * @file hashmap.h
 * @brief This file contains the API for hashmaps in C
 * @author Maxime Loukhal
 * @date 28/02/2024
 */
#ifndef COLLECTIONS_COMMONS_HASHMAP_H
#define COLLECTIONS_COMMONS_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lhtbl.h"
#include "hashset.h"

/**
 * @brief Hashmap Key-Value pair entry
 */
typedef struct SimpleEntry {
    /**
     * @brief Entry identifier
     */
    void *key;
    /**
     * @brief Identifier value
     */
    void *value;

    /**
     * @brief Pointer to the User Keys equals function for hashmap
     * @param key1 The first key to be compared
     * @param key2 The second key to be compared
     * @return true if the keys equals, false otherwise
     */
    bool (*compareTo)(const void *key1, const void *key2);

    /**
     * @brief Next entry in the hashmap
     */
    struct SimpleEntry *next;

    /**
     * @brief Next entry in the hashmap
     */
    struct SimpleEntry *last;
} SimpleEntry;

/**
 * @brief Data structure to map a specific key with its associated value
 */
typedef struct HashMap {

    /**
     * @brief Internal key hashtable
     */
    LinkedHashTable *hashTable;
    /**
     * @brief First entry in the hashmap
     */
    SimpleEntry *head;
    /**
     * @brief Last entry in the hashmap
     */
    SimpleEntry *tail;
    /**
     * @brief Hashmap current size
     */
    int size;

    /**
     * @brief Pointer to the User Keys equals function for hashmap
     * @param key1 The first key to be compared
     * @param key2 The second key to be compared
     * @return true if the keys equals, false otherwise
     */
    bool (*equals)(const void *key1, const void *key2);

    /**
     * @brief Pointer to the destroy function for hashmap
     * @param value The value to be destroyed
     */
    void (*destroy)(void *value);
} HashMap;

/**
 * @brief Tries to allocate a new hashmap
 * @param map hashmap to be created
 * @param containers The number of containers in the internal hashtable of the hashmap
 * @param hash Key hash function
 * @param equals Key equals function
 * @param destroy Entry destroy function
 * @return true if the hashmap was created successfully, false otherwise
 */
bool hashmap_create(HashMap *map,
                    int containers,
                    int (*hash)(const void *key),
                    bool (*equals)(const void *key1, const void *key2),
                    void(*destroy)(void *value));

/**
 * @brief Destroy the given hashmap and all its entries
 * @param set The hashmap to be destroyed
 */
void hashmap_destroy(HashMap *set);

/**
 * @brief Associates the specified value to the specified key in the given hashmap if the key isn't already present
 * @param map Hashmap to add an entry in
 * @param key Key to be added with the specified value in the given hashmap
 * @param value Value to be added with the specified key in the given hashmap
 * @return true if the given key value pair was added, false otherwise
 */
bool hashmap_put(HashMap *map, void *key, void *value);

/**
 * @brief Puts an entry at the end of the given hashmap
 * @param map Hashmap to add an entry in
 * @param entry Entry to be added in the given hashmap
 * @return true if the given entry was added, false otherwise
 */
bool hashmap_addEntry(HashMap *map, SimpleEntry *entry);

/**
 * @brief Compute the put operation only if the target key isn't already in the given hashmap
 * @param map Hashmap to put a value if absent in
 * @param key Key to put if absent in the given hashmap
 * @param value Value of the key to put if absent in the given hashmap
 * @return true if key value pair has been added to the given hashmap, false otherwise
 */
bool hashmap_putIfAbsent(HashMap *map, void *key, void *value);

/**
 * @brief Replace the value of a target key in a given hashmap
 * @param map Hashmap to replace a key value in
 * @param key Key to replace the value
 * @param new_value New value of the key
 * @param old_value Pointer on the old key value
 * @return true if the replace occurs
 */
bool hashmap_replace(HashMap *map, void *key, void **value);

/**
 * @brief Remove a given entry from the current hashmap, then returns a pointer on the value of the deleted element
 * @param map Reference of the hashmap to remove an element
 * @param value Double pointer of the key to delete, if deletion occurs returns pointer on the value of the deleted entry value
 * @return true if the element was correctly removed, false otherwise
 */
bool hashmap_remove(HashMap *map, void **value);

/**
 * @brief Remove a given entry from the current hashmap, then returns a pointer on the value of the deleted element
 * @param map Reference of the hashmap to remove an element
 * @param element Entry of the hashmap to be removed
 * @param value Output pointer on the value of the deleted entry value
 * @return true if the element was correctly removed, false otherwise
 */
bool hashmap_removeEntry(HashMap *map, SimpleEntry *entry, void **value);

/**
 * @brief Test if the given value is present in the hashmap, if a equals occurs value will contain the pointer on the equalsed value
 * @param map Hashmap to lookup in
 * @param value Double pointer to remove the key in the given hashmap, if a delete occurs returns the pointer on it
 * @return true if the data table is present in the given hashmap, false otherwise
 */
bool hashmap_containsKey(HashMap *map, void **value);

/**
 * @brief Returns keys from the given hashmap as a hashset
 * @param map Hashmap to return keys as set
 * @return The keys of the given hashmap as set
 */
HashSet *hashmap_keySet(HashMap *map);

/**
 * @brief Returns SimpleEntry entries from the given hashmap as a hashset
 * @param map Hashmap to return entries as set
 * @return The entries of the given hashmap as set
 */
HashSet *hashmap_entrySet(HashMap *map);

/**
 * @brief Returns the hashmap
 * @param map
 * @return
 */
DLinkedList *hashmap_values(HashMap *map);
#ifdef __cplusplus
/**
 * @brief Inline function that evaluates the number of hashtable inside the specified hashmap
 * @return The current entry count of the current hashmap
 * @complexity O(1)
 */
inline int hashmap_size(HashMap *hashmap) {
    return hashmap->size;
} ;


/**
 * @brief Inline function that evaluates the first entry of the specified hashmap
 * @return The first entry of the current hashmap
 * @complexity O(1)
 */
inline SimpleEntry *hashmap_first(HashMap *hashmap) {
    return hashmap->head;
} ;

/**
 * @brief Inline function that evaluates the last entry of the specified hashmap
 * @return The last entry of the current hashmap
 * @complexity O(1)
 */
inline SimpleEntry *hashmap_last(HashMap *hashmap) {
    return hashmap->tail;
} ;

/**
 * @brief Inline function that evaluates if the specified entry is the first entry of the specified hashmap
 * @return true if the entry is the first of the current hashmap, false otherwise
 * @complexity O(1)
 */
inline bool hashmap_isFirst(HashMap *hashmap, SimpleEntry *entry) {
    return (hashmap)->head == entry;
} ;

/**
 * @brief Inline function that evaluates if the specified entry is the last entry of the specified hashmap
 * @return true if the entry is the last of the current hashmap, false otherwise
 * @complexity O(1)
 */
inline bool hashmap_isLast(HashMap *hashmap, SimpleEntry *entry) {
    return (hashmap)->tail == entry;
} ;

/**
 * @brief Inline function that evaluates the next entry of the current hashmap entry
 * @return The reference to the next entry of the current hashmap entry
 * @complexity O(1)
 */
inline SimpleEntry *hashmap_next(SimpleEntry *entry) {
    if (entry == nullptr) return nullptr;
    else return (entry)->next == nullptr ? nullptr : (entry)->next;
}

/**
 * @brief Inline function that check if the given value is present in the hashmap, if a equals occurs value will contain the pointer on the equalsed value
 * @param map Hashmap to lookup in
 * @param value Double pointer to remove the key in the given hashmap, if a equals occurs returns the pointer on it
 * @return true if the data table is present in the given hashmap, false otherwise
 */
inline bool hashmap_get(HashMap *map, void **value) {
    return hashmap_containsKey(map, value);
} ;
#else
/**
 * @brief Macro that evaluates the number of hashtable inside the specified hashmap
 * @return The current entry count of the current hashmap
 * @complexity O(1)
 */
#define hashmap_size(hashmap) ((hashmap)->size)

/**
 * @brief Macro that evaluates the first entry of the specified hashmap
 * @return The first entry of the current hashmap
 * @complexity O(1)
 */
#define hashmap_first(hashmap) ((hashmap)->head)

/**
 * @brief Macro that evaluates the last entry of the specified hashmap
 * @return The last entry of the current hashmap
 * @complexity O(1)
 */
#define hashmap_last(hashmap) ((hashmap)->tail)

/**
 * @brief Macro that evaluates if the specified entry is the first entry of the specified hashmap
 * @return true if the entry is the first of the current hashmap, false otherwise
 * @complexity O(1)
 */
#define hashmap_isFirst(hashmap, entry) ((entry) == (hashmap)->head ? true : false )

/**
 * @brief Macro that evaluates if the specified entry is the last entry of the specified hashmap
 * @return true if the entry is the last of the current hashmap, false otherwise
 * @complexity O(1)
 */
#define hashmap_isLast(hashmap, entry) ((entry) == (hashmap)->tail ? true : false )

/**
 * @brief Macro that evaluates the value of a hashmap entry
 * @return The value stored inside a hashmap entry
 * @complexity O(1)
 */
#define hashmap_value(entry) ((entry)->value)


/**
 * @brief Macro that evaluates the next entry of the current hashmap entry
 * @return The reference to the next entry of the current hashmap entry
 * @complexity O(1)
 */
#define hashmap_next(entry) ((entry)->next)

/**
 * @brief  Macro that evaluates if the given value is present in the hashmap, if a equals occurs value will contain the pointer on the equalsed value
 * @param map Hashmap to lookup in
 * @param value Double pointer to remove the key in the given hashmap, if a equals occurs returns the pointer on it
 * @return true if the data table is present in the given hashmap, false otherwise
 */
#define hashmap_get(map,value) hashmap_containsKey
#endif

#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_HASHMAP_H
