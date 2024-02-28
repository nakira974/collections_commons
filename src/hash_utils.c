//
// Created by maxim on 28/02/2024.
//
#include "hash_utils.h"
bool cmp_int(const void *a, const void *b){
    if(a ==NULL || b == NULL ) return false;
    int* intA = (int*)a;
    int* intB = (int*)b;

    if (*intA == *intB) {
        return true;
    } else {
        return false;
    }
}

int hashref(const void *ref) {
    const double phi = (sqrt(5) - 1) / 2;
    intptr_t address = (intptr_t) ref;

    return ((int)( (int) address * phi));
}

int hashpjw(const void* key){
    const char * string;
    int value;

    // hash the key the bit to bit operations

    value = 0;
    string = key;

    while(*string != '\0'){
        int temp;
        value = (value<<4) + (*string);
        if(temp=(value & 0xf0000000)){
            value = value ^(temp >> 24);
            value = value ^temp;
        }
        string++;
    }

    return (int) (value);
}
