/**
 * @file heap.h
 * @brief This file contains the API for binary heaps tree
 * @author Maxime Loukhal
 * @date 29/03/2024
 */
#ifndef COLLECTIONS_COMMONS_HEAP_H
#define COLLECTIONS_COMMONS_HEAP_H

#ifdef __cplusplus
#include <cstdlib>
#include <cstdbool>
#else

#include <stdlib.h>
#include <stdbool.h>

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data structure that defines a heap binary tree
 */
typedef struct Heap{
    /**
     * @brief Heap current size
     */
    int size;
    /**
     * @brief Compares to user function
     * @param key1 Left key to be compared
     * @param key2 Right key to be compared
     * @return 0 if keys are equal, -1 if key1 inferior key2, 1 if key1 superior to key2
     */
    int (*compareTo) (const void*key1, const void*key2);
    /**
     * @brief User destroy function
     * @param key Value to be destroyed
     */
    void (*destroy) (void *key);

    /**
     * @brief Internal flat array binary tree implementation
     */
    void **tree;
} Heap;

/**
 * @brief Initializes a Heap with its default values
 * @param heap Heap to initialized with its default values
 * @param compareTo User compare function
 * @param destroy User destroy function
 */
void heap_create(Heap * heap, int (*compareTo) (const void*key1, const void*key2), void (*destroy) (void *key));

/**
 * @brief Destroys a given Heap
 * @param heap Heap to be destroyed
 */
void heap_destroy(Heap * heap);

/**
 * @brief Adds a value into a given Heap
 * @param heap Heap where to add the value
 * @param value Value to be added
 * @return true if the value was added, otherwise false
 */
bool heap_add(Heap * heap, const void * key);

/**
 * @brief Tries to get the given value in the given Heap
 * @param heap Heap to get the value in
 * @param key Value to get
 * @return true if the value was found, otherwise false
 */
bool heap_poll(Heap * heap, void **key);

#ifdef __cpluscplus

/**
 * @brief Macro that evaluates the current size of a given Heap
 */
#define heap_size(heap) ((heap)->size)

#else

/**
 * @brief Inline function that evaluates the current size of a given Heap
 */
static inline int heap_size(Heap *heap){
    return heap->size;
}
#endif


#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_HEAP_H
