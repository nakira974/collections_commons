/**
 * @file sort.h
 * @brief This file contains the API for collections sorting algorithms
 * @author Maxime Loukhal
 * @date 24/02/2024
 */

#ifndef COLLECTIONS_COMMONS_SORT_H
#define COLLECTIONS_COMMONS_SORT_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#else

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#endif

/**
 * @brief Determine if a generic array is sorted or not
 * @param value Array to determine if it's sorted or not
 * @param element_count Number of hashtable inside the given array
 * @param element_size The size of the enumerable
 * @param compare User compare function
 * @return true if the generic array is sorted, false otherwise
 */
bool
array_is_sort(void *value, int element_count, size_t element_size, int (*compare)(const void *key1, const void *key2));

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


#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_SORT_H
