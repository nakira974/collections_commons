/**
 * @file  ohtbl.h
 * @brief This file contains the API for open addressing hash tables
 * @author Maxime Loukhal
 * @date 05/03/2024
 */
#ifndef COLLECTIONS_COMMONS_OHTBL_H
#define COLLECTIONS_COMMONS_OHTBL_H

#ifdef __cplusplus
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#else
 #include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "dlist.h"

#endif

#ifdef __cplusplus
 extern "C" {
#endif
/**
 * @brief Data structure for an Open Addressing Hash Table
 */
typedef struct OAHashTable{
    /**
     * @brief Number of positions inside the hash table
     */
    int positions;
    /**
     * @brief Vacant position inside the hash table
     */
    void *vacant;

    int (*h1)(const void *key);
    int (*h2) (const void *key);
    bool (*equals)(const void *key1, const void *key2);
    void (*destroy)(void *value);
    int size;
    void **hashtable;
} OAHashTable;

/**
 * @brief Create a new Open Addressing hash table
 * @param hashTable Hash table to be created
 * @param postions Number of positions inside the hash table
 * @param h1 Hash function n°1
 * @param h2 Hash function n°2
 * @param equals Values equals function
 * @param destroy Values destroy function
 * @return true if the hash table was created, false otherwise
 */
bool ohtbl_create(OAHashTable *hashTable, int postions,
                  int (*h1)(const void *key),
                  int (*h2) (const void *key),
                  bool (*equals)(const void *key1, const void *key2),
                  void (*destroy)(void *value));

/**
 * @brief Destroy the given Open Addressing hash table
 * @param hashTable Hash table to be destroyed
 */
void ohtbl_destroy(OAHashTable *hashTable);

/**
 * @brief Try to add an element into the Open Addressing hash table
 * @param hashTable Hash table to try to add an element in
 * @param value Value to be added
 * @return true if the value was inserted, false otherwise
 */
bool ohtbl_put(OAHashTable *hashTable, const void *value);

/**
 * @brief Remove an element from the given Open Addressing hash table
 * @param hashTable Hash table to remove an element in
 * @param value Pointer to the element to be destroyed and returned value
 * @return true if the element was removed from the given Open Addressing hash table, false otherwise
 */
bool ohtbl_remove(OAHashTable * hashTable, void **value);

/**
 * @brief Determine if an element is present or not in the given hash table
 * @param hashTable Hash table to determine if an element is present in
 * @param value The value to determine if it's present or not in the given hash table
 * @return true if the element is present in the given hash table, false otherwise
 */
bool ohtbl_contains(OAHashTable * hashTable, void **value);

/**
 * @brief Convert the given hash table into an array
 * @param hashTable Hash table to be converted to array
 * @return Converted hash table to array
 */
void** ohtbl_toArray(OAHashTable *hashTable);

/**
 * @brief Convert the hash table into a list
 * @param hashTable Hash table to be converted to list
 * @return Converted hash table to list
 */
DLinkedList *ohtbl_toList(OAHashTable *hashTable);

#ifdef __cplusplus
/***
* @brief Inline function that evaluates the number of elements inside the specified hash table
* @return The current element count of the current hash table
*/
static inline int ohtbl_size(OAHashTable *hashTable){
    return hashTable->size;
}
#else
 /***
* @brief Macro that evaluates the number of elements inside the specified hash table
* @return The current element count of the current hash table
*/
#define ohtbl_size(hashTable) ((hashTable)->size)
#endif
#ifdef __cplusplus
 }
#endif
#endif //COLLECTIONS_COMMONS_OHTBL_H
