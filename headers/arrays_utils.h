/**
 * @file arrays_utils.h
 * @brief This file contains the API for arrays utility methods
 * @author Maxime Loukhal
 * @date 09/03/2024
 */
#include "list.h"
#include "dlist.h"
#include "clist.h"

#include "set.h"

#ifndef COLLECTIONS_COMMONS_ARRAY_H
#define COLLECTIONS_COMMONS_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Splits an array from start_index to stop_index and stores the result in out, updating out_size.
 *
 * @param out Array of arrays resulting from the split operation.
 * @param out_size Pointer to the size of the output array.
 * @param in Input array to be split.
 * @param start_index Index to start the split from (inclusive).
 * @param stop_index Index to end the split at (exclusive).
 */
void array_split(void ***out, int *out_size, void *in, int start_index, int stop_index);

/**
 * @brief Converts the given array into a list
 * @param array Array to be converted to list
 * @param destroy User destroy function
 * @return Converted array to list
 */
LinkedList *array_toList(void **array, void( *destroy)(void *value));

/**
 * @brief Converts the given array into a double linked list
 * @param array Array to be converted to list
 * @param destroy User destroy function
 * @return Converted array to list
 */
DLinkedList *array_toDList(void **array,void( *destroy)(void *value));

/**
 * @brief Converts the given array into a circular list
 * @param array Array to be converted to list
 * @param destroy User destroy function
 * @return Converted array to list
 */
CLinkedList *array_toCList(void **array, void( *destroy)(void *value));

/**
 * @brief Converts the given array into a set
 * @param array Array to be converted to set
 * @param destroy User destroy function
 * @param equals User equals function
 * @return Converted array to set
 */
Set *array_toSet(void **array,  void( *destroy)(void *value), bool(*equals)(const void *value1, const void *value2));

#ifdef __cpluscplus
/**
 * @brief Inline function that evaluates the size of an array
 * @param array Array to determine the size
 */
static inline size_t array_size(void** array){
    return sizeof(array) / sizeof(array[0]);
}
#else
/**
 * @brief Macro that evaluates the size of an array
 * @param array Array to determine the size
 */
#define array_size(array)  (sizeof(array) / sizeof((array)[0]))

#endif
#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_ARRAY_H
