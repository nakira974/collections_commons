/**
 * @file collections_utils.h
 * @brief This file contains the API for collections utility methods
 * @author Maxime Loukhal
 * @date 12/03/2024
 */

#ifndef COLLECTIONS_COMMONS_COLLECTIONS_UTILS_H
#define COLLECTIONS_COMMONS_COLLECTIONS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "dlist.h"
#include "clist.h"
#include "set.h"
#include "arrays_utils.h"
#include "queue.h"
#include "deque.h"
#include "ohtbl.h"
#include "stack.h"
#include "hashset.h"
#include "hashmap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Convert the given list into an array
 * @param list List to be converted to array
 * @return Converted list to array
 */
void **list_toArray(LinkedList *list);

/**
 * @brief Convert the given list into a set
 * @param list List to be converted to set
 * @return Converted list to set
 */
Set *list_toSet(LinkedList *list, bool(*equals)(const void *value1, const void *value2));


/**
 * @brief Convert the given list into a double linked list
 * @param list List to be converted to a double linked list
 * @return Converted list to double linked list
 */
DLinkedList *list_toDList(LinkedList *list);

/**
 * @brief Convert the given list into a circular list
 * @param list List to be converted to a circular list
 * @return Converted list to circular list
 */
CLinkedList *list_toCList(LinkedList *list);

/**
 * @brief Convert the given list into an array
 * @param list List to be converted to array
 * @return Converted list to array
 */
void **clist_toArray(CLinkedList *list);

/**
 * @brief Convert the given list into a set
 * @param list List to be converted to set
 * @return Converted list to set
 */
Set *clist_toSet(CLinkedList *list, bool(*equals)(const void *value1, const void *value2));

/**
 * @brief Convert the given circular list into a list
 * @param list List to be converted to list
 * @return Converted circular list to list
 */
LinkedList *clist_toList(CLinkedList *list);

/**
 * @brief Convert the given circular list into a double linked list
 * @param list List to be converted to a double linked list
 * @return Converted circular list to double linked list
 */
DLinkedList *clist_toDList(CLinkedList *list);

/**
 * @brief Convert the given list into an array
 * @param list List to be converted to array
 * @return Converted list to array
 */
void **dlist_toArray(DLinkedList *list);

/**
 * @brief Convert the given list into a set
 * @param list List to be converted to set
 * @return Converted list to set
 */
Set *dlist_toSet(DLinkedList *list, bool(*equals)(const void *value1, const void *value2));

/**
 * @brief Convert the double linked list into a list
 * @param list List to be converted to list
 * @return Converted double linked list to list
 */
LinkedList *dlist_toList(DLinkedList *list);

/**
 * @brief Convert the double linked list into a circular list
 * @param list List to be converted to a circular list
 * @return Converted double linked list to circular list
 */
CLinkedList *dlist_toCList(DLinkedList *list);

/**
 * @brief Convert the given hash table into an array
 * @param hashTable Hash table to be converted to array
 * @return Converted hash table to array
 */
void **ohtbl_toArray(OAHashTable *hashTable);

/**
 * @brief Convert the hash table into a list
 * @param hashTable Hash table to be converted to list
 * @return Converted hash table to list
 */
DLinkedList *ohtbl_toList(OAHashTable *hashTable);

/**
 * @brief Convert the given hash table into an array
 * @param hashTable Hash table to be converted to array
 * @return Converted hash table to array
 */
void **lhtbl_toArray(LinkedHashTable *hashTable);

/**
 * @brief Convert the hash table into a list
 * @param hashTable Hash table to be converted to list
 * @return Converted hash table to list
 */
DLinkedList *lhtbl_toList(LinkedHashTable *hashTable);

#ifdef __cplusplus

/**
 * @brief Inline function that evaluates the current queue into an array
 * @param queue Queue to be converted to array
 * @return Converted queue to array
 */
static inline void **queue_toArray(Queue *queue) {
    return list_toArray(queue);
}

/**
 * @brief Inline function that evaluates the current deque into an array
 * @param queue Deque to be converted to array
 * @return Converted deque to array
 */
static inline void **deque_toArray(Deque *queue) {
    return dlist_toArray(queue);
}

/**
 * @brief Inline function that evaluates the current set into an array
 * @param stack Set to be converted to array
 * @return Converted set to array
 */
static inline void **set_toArray(Set *set) {
    return list_toArray(set);
}

/**
 * @brief Inline function that evaluates the current stack into an array
 * @param stack Stack to be converted to array
 * @return Converted list to array
 */
static inline void **stack_toArray(Stack *stack) {
    return list_toArray(stack);
}

/**
 * @brief Inline function that evaluates the current hashset into an array
 * @param set Hashset to be converted to array
 * @return Converted hashset to array
 */
static inline void **hashset_toArray(HashSet *set) {
    return dlist_toArray(set->elements);
}

/**
 * @brief Inline function that evaluates the current queue into an double linked list
 * @param queue Queue to be converted to array
 * @return Converted queue to array
 */
static inline CLinkedList queue_toList(Queue queue){
    return list_toCList(queue);
}

/**
 * @brief Inline function that evaluates the current deque into a circular linked list
 * @param deque Deque to be converted to array
 * @return Converted queue to array
 */
static inline CLinkedList deque_toList(Deque deque){
    return dlist_toCList(deque);
}

/**
 * @brief Inline function that evaluates the current set into a circular linked list
 * @param stack Set to be converted to a circular linked list
 * @return Converted set to a circular linked list
 */
static inline CLinkedList set_toList(Set queue){
    return list_toCList(set);
}

/**
 * @brief Inline function that evaluates the current stack into a circular linked list
 * @param stack Stack to be converted to a circular linked list
 * @return Converted stack to a circular linked list
 */
static inline CLinkedList stack_toList(Stack stack){
    return list_toCList(stack);
}

/**
 * @brief Inline function that evaluates the current hashset into a circular linked list
 * @param set Hashset to be converted to a circular linked list
 * @return Converted hashset to a circular linked list
 */
static inline CLinkedList hashset_toList(HashSet set){
    return dlist_toCList(set);
}

#else
/**
 * @brief Macro that evaluates the current queue into an array
 * @param queue Queue to be converted to array
 * @return Converted queue to array
 */
#define queue_toArray(queue) list_toArray

/**
 * @brief Macro that evaluates the current queue into an double linked list
 * @param queue Queue to be converted to array
 * @return Converted queue to array
 */
#define queue_toList(queue) list_toCList

/**
 * @brief Macro that evaluates the current deque into an array
 * @param deque Queue to be converted to array
 * @return Converted deque to array
 */
#define deque_toArray(deque) dlist_toArray

/**
 * @brief Macro that evaluates the current deque into a circular linked list
 * @param deque Deque to be converted to array
 * @return Converted queue to array
 */
#define deque_toList(deque) dlist_toCList

/**
 * @brief Macro that evaluates the current set into an array
 * @param stack Set to be converted to array
 * @return Converted set to array
 */
#define set_toArray(set) list_toArray

/**
 * @brief Macro that evaluates the current set into a circular linked list
 * @param stack Set to be converted to a circular linked list
 * @return Converted set to a circular linked list
 */
#define set_toList(set) list_toCList

/**
 * @brief Macro that evaluates the current stack into an array
 * @param stack Stack to be converted to array
 * @return Converted stack to array
 */
#define stack_toArray(stack) list_toArray

/**
 * @brief Macro that evaluates the current stack into a circular linked list
 * @param stack Stack to be converted to a circular linked list
 * @return Converted stack to a circular linked list
 */
#define stack_toList(stack) list_toCList

/**
 * @brief Macro that evaluates the current hashset into an array
 * @param set Hashset to be converted to array
 * @return Converted hashset to array
 */
#define hashset_toArray(set) dlist_toArray((set)->elements)

/**
 * @brief Macro that evaluates the current hashset into a circular linked list
 * @param set Hashset to be converted to a circular linked list
 * @return Converted hashset to a circular linked list
 */
#define hashset_toList(set) dlist_toCList((set)->elements)
#endif


#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_COLLECTIONS_UTILS_H
