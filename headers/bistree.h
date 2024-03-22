/**
 * @file bistree.h
 * @brief This file contains the API for binary search trees using AVL nodes
 * @author Maxime Loukhal
 * @date 08/03/2024
 */
#ifndef COLLECTIONS_COMMONS_BISTREE_H
#define COLLECTIONS_COMMONS_BISTREE_H

#ifdef __cpluscplus
#include <cstdbool>
#else
#include <stdbool.h>
#endif

#include "bitree.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Definition of balance factors for AVL trees
 */

/**
 * @brief AVL left balanced macro
 */
#define AVL_TO_L 1
/**
 * @brief AVL balanced macro
 */
#define AVL_BALANCED 0
/**
 * @brief AVL right balanced macro
 */
#define AVL_TO_R (-1)

/**
 * @brief Data structure that defines a binary search tree
 */
typedef BinaryTree BinarySearchTree;

/**
 * @brief Data structure that defines an AVL tree node
 */
typedef struct AvlNode{
    /**
     * @brief value of the given node
     */
    void *value;
    /**
     * @brief cache of the given node
     */
    int cache;
    /**
     * @brief factor of the given node
     */
    int factor;
}AvlNode;

/**
 * @brief Initializes a BinarySearchTree with its default values
 * @param compare User compare function
 * @param destroy User destroy function
 */
void bistree_create(BinarySearchTree *tree, void (*compare)(const void* key1, const void* key2), void(*destroy) (void* value));

/**
 * @brief Destroys a given BinarySearchTree
 * @param tree BinarySearchTree to be destroyed
 */
void bistree_destroy(BinarySearchTree *tree);

/**
 * @brief Tries to add a value into the given BinarySearchTree
 * @param tree Tree to add a new value
 * @param value Value to to be added in the given BinarySearchTree
 * @return 0 if the value was inserted correctly, 1 if already present, -1 otherwise
 */
int bistree_add(BinarySearchTree * tree, const void * value);

/**
 * @brief Tries to remove a value into the given BinarySearchTree
 * @param tree Tree to remove a value
 * @param value Value to to be removed in the given BinarySearchTree
 * @return true if the value was removed false otherwise
 */
bool bistree_remove(BinarySearchTree * tree, const void * value);

/**
 * @brief Determine if a given value is present or not in the given BinarySearchTree
 * @param tree BinarySearchTree to lookup in
 * @param value Double pointer on the value to check and returned reference
 * @return true if the value is present in the given BinarySearchTree, false otherwise
 */
bool bistree_containsKey(const BinarySearchTree * tree, void ** value);

#ifdef __cpluscplus
/**
 * @brief Macro that evaluates the size of the given BinarySearchTree
 * @param tree BinarySearchTree to evaluates the size
 * @return The current size of the given BinarySearchTree
 */
#define bistree_size(tree) ((tree)->size)
#else
/**
 * @brief Inline function that evaluates the size of the given BinarySearchTree
 * @param tree BinarySearchTree to evaluates the size
 * @return The current size of the given BinarySearchTree
 */
static inline int bistree_size(BinarySearchTree * tree){
    return tree->size;
}
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_BISTREE_H
