//
// Created by maxim on 14/02/2024.
//


#include "randomized_set.h"

RandomizedSet* randomizedSetCreate() {
    RandomizedSet* set = malloc(sizeof(RandomizedSet));
    set->nums = malloc(10000 * sizeof(int));
    set->locs = malloc(10000 * sizeof(int));
    set->size = 0;
    set->capacity = 10000;
    return set;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    for (int i = 0; i < obj->size; i++) {
        if (obj->nums[i] == val) {
            return false;
        }
    }

    if (obj->size >= obj->capacity) {
        obj->capacity *= 2;
        obj->nums = realloc(obj->nums, obj->capacity * sizeof(int));
        obj->locs = realloc(obj->locs, obj->capacity * sizeof(int));
    }

    obj->nums[obj->size] = val;
    obj->locs[val] = obj->size;
    obj->size++;
    return true;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    if (val < obj->size && obj->nums[val] != -1) {
        obj->nums[val] = -1;
        return true;
    }
    return false;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    int index = rand() % obj->size;
    while (obj->nums[index] == -1) {
        index = rand() % obj->size;
    }
    return obj->nums[index];
}

void randomizedSetFree(RandomizedSet* obj) {
    free(obj->nums);
    free(obj->locs);
    free(obj);
}
