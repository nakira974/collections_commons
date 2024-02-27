/**
 * @file set.h
 * @brief This file contains the API for linked hash tables
 * @author Maxime Loukhal
 * @date 26/02/2024
 */

#ifndef COLLECTIONS_COMMONS_LHTBL_H
#define COLLECTIONS_COMMONS_LHTBL_H

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
#include <cstdlib>
#include <cstdbool>
#else
#include <stdlib.h>
#include <stdbool.h>
#endif

#include "list.h"

/**
 * @brief Data structure definition for a linked hash table
 */
typedef struct LinkedHashTable{
    /**
     * @brief Number of containers in the linked hash table
     */
    int containers;

    /**
     * @brief Pointer to the hash function for elements
     * @param key The key to be hashed
     * @return The hashed value of the key
     */
    int (*hash)(const void *key);

    /**
     * @brief Pointer to the match function for elements
     * @param key1 The first key to be compared
     * @param key2 The second key to be compared
     * @return 0 if the keys match, non-zero otherwise
     */
    int (*match)(const void* key1, const void* key2);

    /**
     * @brief Pointer to the destroy function for elements
     * @param value The value to be destroyed
     */
    void(*destroy)(void *value);

    /**
     * @brief Current element count of the hash table
     */
    int size;

    /**
     * @brief Pointer to the internal linked list for storing elements
     */
    LinkedList *elements;
} LinkedHashTable;

#ifdef __cplusplus
/***
* @brief Inline function that evaluates the number of elements inside the specified queue
* @return The current element count of the current list
* @complexity O(1)
*/
inline int lhtbl_size(LinkedHashTable *queue){
    return queue->size;
};
#else

/***
* @brief Inline function that evaluates the number of elements inside the specified queue
* @return The current element count of the current chained hash table
* @complexity O(1)
*/
#define lhtbl_size(table);
#endif

/**
 * @brief Tries to allocate a new linked hash table
 * @param lhtbl Linked hash table to create
 * @param containers The number of containers in the hash table
 * @param hash Element hash function
 * @param match Element match function
 * @param destroy Element destroy function
 * @return true if the hash table has been created successfully, false otherwise
 */
bool lhtbl_create(LinkedHashTable *lhtbl,
                    int containers,
                    int (*hash)(const void *key),
                    int (*match)(const void* key1, const void* key2),
                    void(*destroy)(void *value));

/**
 * @brief Destroy a given data table
 * @param lhtbl The data table to be destroyed
 */
void lhtbl_destroy(LinkedHashTable *lhtbl);

/**
 * @brief Associates the specified value with a new hash key
 * @param lhtbl Linked Hash Table to put a value in
 * @param value Value to be put in the given data table
 * @return true if the value has been correctly inserted, false otherwise
 */
bool lhtbl_put(LinkedHashTable *lhtbl, const void* value);

/**
 * @brief Remove a value from the data table, then if the operation has been compute value will contain the pointer on the destroyed value
 * @param lhtbl Linked Hash Table to remove a value in
 * @param value Double pointer on the value to be removed, then if it has been correctly removed the pointer on the removed value
 * @return true if the data table has been deleted from the data table, false otherwise
 */
bool lhtbl_remove(LinkedHashTable *lhtbl, void** value);

/**
 * @brief Test if the given value is present in the data table, if a match occurs value will contain the pointer on the matched value
 * @param lhtbl Linked Hash Table to lookup in
 * @param value Double pointer to lookup the value in the given data table, if a match occurs returns the pointer on it
 * @return true if the data table is present in the given data table, false otherwise
 */
bool lhtbl_lookup(LinkedHashTable *lhtbl, void** value);
#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_LHTBL_H
