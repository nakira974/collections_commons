/**
 * @file sort.h
 * @brief This file contains the API for hash sets
 * @author Maxime Loukhal
 * @date 27/02/2024
 */
#ifndef COLLECTIONS_COMMONS_HASHSET_H
#define COLLECTIONS_COMMONS_HASHSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lhtbl.h"
#include "dlist.h"

/**
 * @brief Data structure to set a specific key with its associated value
 */
typedef struct HashSet {

    /**
     * @brief Internal key hashtable
     */
    LinkedHashTable *hashTable;

    /**
     * @brief HashSet elements
     */
    DLinkedList *elements;
    /**
     * @brief Hashmap current size
     */
    int size;

    /**
     * @brief Pointer to the User Keys equals function for hashset
     * @param key1 The first key to be compared
     * @param key2 The second key to be compared
     * @return true if the keys equals, false otherwise
     */
    bool (*equals)(const void *key1, const void *key2);

    /**
     * @brief Pointer to the destroy function for hashset
     * @param value The value to be destroyed
     */
    void (*destroy)(void *value);
} HashSet;

/**
 * @brief Tries to allocate a new hashset
 * @param set hashset to be created
 * @param containers The number of containers in the internal hashtable of the hashset
 * @param hash Key hash function
 * @param equals Key equals function
 * @param destroy Entry destroy function
 * @return true if the hashset was created successfully, false otherwise
 */
bool hashset_create(HashSet *set,
                    int containers,
                    int (*hash)(const void *key),
                    bool (*equals)(const void *key1, const void *key2),
                    void(*destroy)(void *value));

/**
 * @brief Destroy the given hashset and all its entries
 * @param set The hashset to be destroyed
 */
void hashset_destroy(HashSet *set);

/**
 * @brief Associates the specified value to the specified key in the given hashset if the key isn't already present
 * @param set Hashmap to add an entry in
 * @param key Key to be added with the specified value in the given hashset
 * @param value Value to be added with the specified key in the given hashset
 * @return true if the given key value pair was added, false otherwise
 */
bool hashset_add(HashSet *set, void *value);


/**
 * @brief Remove a given entry from the current hashset, then returns a pointer on the value of the deleted element
 * @param set Reference of the hashset to remove an element
 * @param value Double pointer of the key to delete, if deletion occurs returns pointer on the value of the deleted entry value
 * @return true if the element was correctly removed, false otherwise
 */
bool hashset_remove(HashSet *set, void **value);

/**
 * @brief Test if the given value is present in the hashset, if a equals occurs value will contain the pointer on the equalsed value
 * @param set Hashmap to lookup in
 * @param value Double pointer to remove the key in the given hashset, if a delete occurs returns the pointer on it
 * @return true if the data table is present in the given hashset, false otherwise
 */
bool hashset_contains(HashSet *set, void **value);

/**
 * @brief Build a HashSet resulting of the Union of left and right, left and right MUST stay accessible before result is destroy
 * @param union_result Reference HashSet resulting of the union between left and right
 * @param left Left HashSet to compare for union operation
 * @param right Right HashSet to compare for union operation
 * @return true if the union succeed, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool hashset_union(HashSet *union_result, const HashSet *left, const HashSet *right);

/**
 * @biref Build a HashSet resulting of the Intersection of left and right, left and right MUST stay accessible before result is destroy
 * @param intersection_result Reference HashSet resulting of the intersection between left and right
 * @param left Left HashSet to compare for intersection operation
 * @param right Right HashSet to compare for intersection operation
 * @return true if the intersection succeed, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool hashset_intersection(HashSet *intersection_result, const HashSet *left, const HashSet *right);

/**
 * @brief Build a HashSet resulting of the Difference of left and right, left and right MUST stay accessible before difference_result is destroy
 * @param difference_result Reference HashSet resulting of the difference between left and right
 * @param left Left HashSet to compare for difference operation
 * @param right Right HashSet to compare for difference operation
 * @return true if the difference succeed, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool hashset_difference(HashSet *difference_result, const HashSet *left, const HashSet *right);

/**
 * @brief Test if the value is in the given HashSet
 * @param set HashSet to search in
 * @param value Value to search in the set
 * @return true if the element is in the set, false otherwise
 * @complexity O(n) where n is the number of hashtable inside the given HashSet to compare with the parameter value
 */
bool hashset_isMember(const HashSet *set, const void *value);

/**
 * @brief Test if the left operand is a subset of the right operand
 * @param left HashSet to determine if it's a subset of right operand
 * @param right HashSet to be compared with left operand
 * @return true if the left HashSet is a subset of the right HashSet, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool hashset_isSubset(const HashSet *left, const HashSet *right);

/**
 * @brief Test if left and right HashSet operands are equal
 * @param left Left HashSet reference operand
 * @param right Right HashSet reference operand
 * @return true if left and right are equal, false otherwise
 * @complexity O(n ^ 2 ) where n is the number of hashtable inside left AND right
 */
bool hashset_equals(const HashSet *left, const HashSet *right);
#ifdef __cplusplus
/**
 * @brief Inline function that evaluates the number of hashtable inside the specified hashset
 * @return The current entry count of the current hashset
 * @complexity O(1)
 */
inline int hashset_size(HashSet *hashset) {
    return hashset->size;
} ;


/**
 * @brief Inline function that evaluates the first entry of the specified hashset
 * @return The first entry of the current hashset
 * @complexity O(1)
 */
inline DLinkedElement *hashset_first(HashSet *hashset) {
    return hashset->elements->head;
} ;

/**
 * @brief Inline function that evaluates the last entry of the specified hashset
 * @return The last entry of the current hashset
 * @complexity O(1)
 */
inline DLinkedElement *hashset_last(HashSet *hashset) {
    return hashset->elements->tail;
} ;

/**
 * @brief Inline function that evaluates if the specified entry is the first entry of the specified hashset
 * @return true if the entry is the first of the current hashset, false otherwise
 * @complexity O(1)
 */
inline bool hashset_isFirst(HashSet *hashset, DLinkedElement *entry) {
    return (hashset)->elements->head == entry;
} ;

/**
 * @brief Inline function that evaluates if the specified entry is the last entry of the specified hashset
 * @return true if the entry is the last of the current hashset, false otherwise
 * @complexity O(1)
 */
inline bool hashset_isLast(HashSet *hashset, DLinkedElement *entry) {
    return (hashset)->elements->tail == entry;
} ;

/**
 * @brief Inline function that evaluates the next entry of the current hashset entry
 * @return The reference to the next entry of the current hashset entry
 * @complexity O(1)
 */
inline DLinkedElement *hashset_next(DLinkedElement *entry) {
    if (entry == nullptr) return nullptr;
    else return (entry)->next == nullptr ? nullptr : (entry)->next;
}

/**
 * @brief Inline function that check if the given value is present in the hashset, if a equals occurs value will contain the pointer on the equalsed value
 * @param set Hashmap to lookup in
 * @param value Double pointer to remove the key in the given hashset, if a equals occurs returns the pointer on it
 * @return true if the data table is present in the given hashset, false otherwise
 */
inline bool hashset_get(HashSet *set, void **value) {
    return hashset_contains(set, value);
} ;

#else
/**
 * @brief Macro that evaluates the number of hashtable inside the specified hashset
 * @return The current entry count of the current hashset
 * @complexity O(1)
 */
#define hashset_size(hashset) ((hashset)->size)


/**
 * @brief Macro that evaluates if the specified entry is the first entry of the specified hashset
 * @return true if the entry is the first of the current hashset, false otherwise
 * @complexity O(1)
 */
#define hashset_isFirst(hashset, entry) ((entry) == (hashset)->head ? true : false )

/**
 * @brief Macro that evaluates if the specified entry is the last entry of the specified hashset
 * @return true if the entry is the last of the current hashset, false otherwise
 * @complexity O(1)
 */
#define hashset_isLast(hashset, entry) ((entry) == (hashset)->tail ? true : false )

/**
 * @brief Macro that evaluates the value of a hashset entry
 * @return The value stored inside a hashset entry
 * @complexity O(1)
 */
#define hashset_value(entry) ((entry)->value)


/**
 * @brief Macro that evaluates the next entry of the current hashset entry
 * @return The reference to the next entry of the current hashset entry
 * @complexity O(1)
 */
#define hashset_next(entry) ((entry)->next)

/**
 * @brief  Macro that evaluates if the given value is present in the hashset, if a equals occurs value will contain the pointer on the equalsed value
 * @param set Hashmap to lookup in
 * @param value Double pointer to remove the key in the given hashset, if a equals occurs returns the pointer on it
 * @return true if the data table is present in the given hashset, false otherwise
 */
#define hashset_get(set,value) hashset_contains

/**
 * @brief Macro that evaluates the first element of the given Hashset
 * @param set HashSet to evaluate the first element in
 */
#define hashset_first(set) dlist_first(set->elements)

/**
 * @brief Macro that evaluates the last element of the given Hashset
 * @param set HashSet to evaluate the first element in
 */
#define hashset_last(set) dlist_last(set->elements)
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_HASHSET_H
