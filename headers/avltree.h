/**
 * @file avltree.h
 * @brief This file contains the API for AVL type, binary search trees
 * @author Maxime Loukhal
 * @date 08/03/2024
 */
#ifndef COLLECTIONS_COMMONS_AVLTREE_H
#define COLLECTIONS_COMMONS_AVLTREE_H

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
 * @brief Data structure that defines an AVL binary search tree
 */
typedef BinaryTree AvlTree;

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
 * @brief Initializes a AvlTree with its default values
 * @param compare User compare function
 * @param destroy User destroy function
 */
void avltree_create(AvlTree *tree, void (*compare)(const void* key1, const void* key2), void(*destroy) (void* value));

/**
 * @brief Destroys a given AvlTree
 * @param tree AvlTree to be destroyed
 */
void avltree_destroy(AvlTree *tree);

/**
 * @brief Tries to add a value into the given AvlTree
 * @param tree Tree to add a new value
 * @param value Value to to be added in the given AvlTree
 * @return 0 if the value was inserted correctly, 1 if already present, -1 otherwise
 */
int avltree_add(AvlTree * tree, const void * value);

/**
 * @brief Tries to remove a value into the given AvlTree
 * @param tree Tree to remove a value
 * @param value Value to to be removed in the given AvlTree
 * @return true if the value was removed false otherwise
 */
bool avltree_remove(AvlTree * tree, const void * value);

/**
 * @brief Determine if a given value is present or not in the given AvlTree
 * @param tree AvlTree to lookup in
 * @param value Double pointer on the value to check and returned reference
 * @return true if the value is present in the given AvlTree, false otherwise
 */
bool avltree_containsKey(const AvlTree * tree, void ** value);

#ifdef __cpluscplus
/**
 * @brief Macro that evaluates the size of the given AvlTree
 * @param tree AvlTree to evaluates the size
 * @return The current size of the given AvlTree
 */
#define avltree_size(tree) ((tree)->size)
#else
/**
 * @brief Inline function that evaluates the size of the given AvlTree
 * @param tree AvlTree to evaluates the size
 * @return The current size of the given AvlTree
 */
static inline int avltree_size(AvlTree * tree){
    return tree->size;
}
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_AVLTREE_H
