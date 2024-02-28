//
// Created by maxim on 24/02/2024.
//

#include "sort.h"

bool
array_is_sort(void *value, int element_count, size_t element_size, int (*compare)(const void *key1, const void *key2)) {
    char *array = value;
    void *key;
    int i, j;

    // Memory space allocation for key element
    if ((key = (char *) malloc(element_size)) == NULL) {
        free(key);
        return false;
    }

    // Insert multiple time a key element inside sorted element
    for (j = 1; j < element_count; j++) {
        memcpy(key, &array[j * element_size], element_size);
        i = j - 1;

        // Determine if the key element insert index
        while (i > 0 && compare(&array[i * element_size], key) > 0) {
            memcpy(&array[(i + 1) * element_size], &array[i * element_size], element_size);
            i--;
        }
        memcpy(&array[(i + 1) * element_size], key, element_size);
    }

    free(key);

    return true;
}