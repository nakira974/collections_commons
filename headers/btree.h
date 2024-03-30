/**
 * @file btree.h
 * @brief This file contains the API for B, balanced search tree
 * @author Maxime Loukhal
 * @date 08/03/2024
 */

#ifndef COLLECTIONS_COMMONS_BTREE_H
#define COLLECTIONS_COMMONS_BTREE_H

#include "bitree.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief BTree node maximum children
 */
#define BTREE_MAX_NODES 3
/**
 * @brief BTree node minimum children
 */
#define BTREE_MIN_NODES 2

/**
 * @brief Data structure that defines a B tree node
 */
typedef struct BTreeNode{
    /**
     * @brief Current children count
     */
    int size;

    /**
     * @brief Stored keys
     */
    void* values[BTREE_MAX_NODES + 1];

    /**
     * @brief Node's children
     */
    struct BTreeNode *children[BTREE_MAX_NODES + 1];

    /**
     * @brief Node position in the tree
     */
    bool isLeaf;
} BTreeNode;

/**
 * @brief Data structure that defines a B search tree
 */
typedef struct BTree{
    /**
    * @brief BTree current size
    */
    int size;
    /**
     * @brief User compareTo handle for stored values > (-1) , = (0) or < (1)
     * @param value1 Value 1 to be compared
     * @param value2 Value 2 to be compared
     * @return true if values are equal, false otherwise
     */
    int (*compareTo)(const void *value1, const void *value2);

    /**
     * @brief User destroy method to clean node's value
     * @param value Value to be removed from the tree
     */
    void (*destroy)(void *value);

    /**
     * @brief BTree current root node
     */
    BTreeNode *root;
} BTree;



/**
 * @brief Creates a BTree with its default values
 * @param tree BTree to create
 * @param compare User compare handle
 * @param destroy User destroy handle
 */
void btree_create(BTree *tree, int (*compare)(const void* key1, const void* key2), void(*destroy) (void* value));

/**
 * @brief Destroys a given BTree
 * @param tree BTree to be destroyed
 */
void btree_destroy(BTree *tree);

/**
 * @brief Insert a given value in the given BTree
 * @param tree BTree where to insert the value
 * @param value Value to be inserted
 */
void btree_add(BTree *tree, void* value);

/**
 * @brief Returns the longest path length in the given branch
 * @param root Root node of the given branch to find longest path
 * @return Tree's height
 */
int btree_height(BTree *root);

/**
 * @brief Returns the longest path length in the given BTree
 * @param tree Tree to get the longest path on
 * @return The longest path length of the given BTree
 */
int btree_diameter(BTree *tree);

/**
 * @brief Tries to remove a value into the given BTree
 * @param tree Tree to remove a value
 * @param value Value to be removed in the given BTree and returned array of values
 * @return true if the value was removed false otherwise
 */
bool btree_remove(BTree* tree, void** value);

/**
 * @brief Determine if a given value is present or not in the given BTree
 * @param tree BTree to determine if the value is in
 * @param pos Found node position
 * @param value Value to determine if it's in the given BTree
 * @return true if the value is present in the given BTree, otherwise false
 */
bool btree_containsKey(BTree *tree, int* pos, void** value);

/**
 * @brief Count the number of nodes in the given BTree
 * @param tree BTree to count nodes
 * @return Node count of the given BTree
 */
int btree_count(BTree *tree);

#ifdef __cpluscplus
/**
 * @brief Macro that evaluates the size of the given BTree
 * @param tree BTree to evaluates the size
 * @return The current size of the given BTree
 */
#define btree_size(tree) ((tree)->size)
#else
/**
 * @brief Inline function that evaluates the size of the given BTree
 * @param tree BTree to evaluates the size
 * @return The current size of the given BTree
 */
static inline int btree_size(BTree * tree){
    return tree->size;
}
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_BTREE_H
