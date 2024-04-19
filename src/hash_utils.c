//
// Created by maxim on 28/02/2024.
//
#include "hash_utils.h"
#include <stddef.h>

int cmp_int(const void* a, const void* b) {
    int int1 = *((int*)a);
    int int2 = *((int*)b);

    if (int1 == int2) {
        return 0;
    } else if (int1 < int2) {
        return -1;
    } else {
        return 1;
    }
}

int hashref(const void *ref) {
    const double phi = (sqrt(5) - 1) / 2;
    intptr_t address = (intptr_t) ref;

    return ((int) ((int) address * phi));
}

int hashpjw(const void *key) {
    const char *string;
    int value;

    // hash the key the bit to bit operations

    value = 0;
    string = key;

    while (*string != '\0') {
        int temp;
        value = (value << 4) + (*string);
        if (temp = (value & 0xf0000000)) {
            value = value ^ (temp >> 24);
            value = value ^ temp;
        }
        string++;
    }

    return (int) (value);
}

int hashint(const void *integer) {
    int x = *((int *) integer);
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}