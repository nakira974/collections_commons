//
// Created by maxim on 14/02/2024.
//


#include "randomized_set.h"


RandomizedSet* randomizedSetCreate() {
    RandomizedSet* set = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    set->nums = (int*)malloc(1000 * sizeof(int));
    set->numsSize = 0;
    set->capacity = 1000;
    return set;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    for (int i = 0; i < obj->numsSize; i++) {
        if (obj->nums[i] == val) {
            return false;
        }
    }

    if (obj->numsSize == obj->capacity) {
        obj->nums = (int*)realloc(obj->nums, (2 * obj->capacity) * sizeof(int));
        obj->capacity *= 2;
    }

    obj->nums[obj->numsSize++] = val;
    return true;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    for (int i = 0; i < obj->numsSize; i++) {
        if (obj->nums[i] == val) {
            obj->nums[i] = obj->nums[obj->numsSize - 1];
            obj->numsSize--;
            return true;
        }
    }
    return false;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    int randomIndex = rand() % obj->numsSize;
    return obj->nums[randomIndex];
}

void randomizedSetFree(RandomizedSet* obj) {
    free(obj->nums);
    free(obj);
}