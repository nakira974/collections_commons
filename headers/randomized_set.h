//
// Created by maxim on 14/02/2024.


#ifndef COLLECTIONS_UTILS_RANDOMIZED_SET_H
#define COLLECTIONS_UTILS_RANDOMIZED_SET_H

#include <malloc.h>
#include <stdbool.h>

/**
 * Data structure for a randomized set of integers
 */
typedef struct {
    /**
     * Array where are stored set values
     */
    int *nums;
    /**
     * Current size of the randomized set
     */
    int size;
    /**
     * Current capacity of the set
     */
    int capacity;
} RandomizedSet;


/**
 * Creates a randomized set with default values
 * @param set Randomized set to create
 */
void randomized_set_create(RandomizedSet *set);

/**
 * Insert the value into the set
 * @param obj The randomized set to insert value
 * @param val The value to be inserted
 * @return True if the value is not present, otherwise false
 */
bool randomized_set_add(RandomizedSet *obj, int val);

/**
 * Remove a value from the randomized set
 * @param obj The randomized set to remove the value
 * @param val The value to be removed
 * @return True if the value has been removed, otherwise false
 */
bool randomized_set_remove(RandomizedSet *obj, int val);

/**
 * Return a random element from the set
 * @param obj The randomized set to get value on
 * @return A random value from the randomized set
 */
int randomized_set_get_random(RandomizedSet *obj);

/**
 * Destroy the target randomized set and clean up memory
 * @param obj The randomized set to remove
 */
void randomized_set_destroy(RandomizedSet *obj);

#endif //COLLECTIONS_UTILS_RANDOMIZED_SET_H