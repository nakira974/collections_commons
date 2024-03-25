//
// Created by maxim on 24/02/2024.
//

#include "sort.h"
#include "arrays_utils.h"

bool array_is_sort(void *value, int element_count, size_t element_size, int (*compare)(const void *key1, const void *key2)) {
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

void array_split(void ***out, int *out_size, void *in, int start_index, int stop_index) {
    void **out_ptr = *out;
    char *in_ptr = (char *) in;

    int size = stop_index - start_index;
    for (int i = 0; i < size; i++) {
        // Allocate space for a void* element
        if ((out_ptr[*out_size] = malloc(sizeof(void *))) == NULL) {
            free(in_ptr);
            return;
        };
        (*out_size)++;
        out_ptr[*out_size - 1] = in_ptr + start_index + i;
    }
}
