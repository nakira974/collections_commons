/**
 * @file array.h
 * @brief This file contains the API for arrays
 * @author Maxime Loukhal
 * @date 09/03/2024
 */
#include "list.h"
#include "dlist.h"
#include "clist.h"

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
 * @brief Convert the given array into a list
 * @param array Array to be converted to list
 * @return Converted array to list
 */
LinkedList *array_toList(void **array);

/**
 * @brief Convert the given array into a double linked list
 * @param array Array to be converted to list
 * @return Converted array to list
 */
DLinkedList *array_toDList(void **array);

/**
 * @brief Convert the given array into a circular list
 * @param array Array to be converted to list
 * @return Converted array to list
 */
CLinkedList *array_toCList(void **array);

/**
 * @brief Convert the given array into a set
 * @param array Array to be converted to set
 * @return Converted array to set
 */
struct Set* array_toSet(void **array, bool(*equals) (const void* value1, const void * value2));

#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_ARRAY_H
