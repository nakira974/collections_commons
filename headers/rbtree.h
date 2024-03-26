/**
 * @file rbtree.h
 * @brief This file contains the API for Red-Black, binary search trees
 * @author Maxime Loukhal
 * @date 08/03/2024
 */

#ifndef COLLECTIONS_COMMONS_RBTREE_H
#define COLLECTIONS_COMMONS_RBTREE_H

#include "bitree.h"

/**
 * @brief Red Black Tree colors enum
 */
enum NodeColor {
    /**
     * @brief Red color
     */
    RED,
    /**
     * @brief Black color
     */
    BLACK
};

/**
 * @brief Type definition for a red black tree node
 */
typedef struct RedBlackTreeNode{
    /**
     * @brief value of the given node
     */
    void * value;
    /**
     * @brief color of the given node
     */
    enum NodeColor color;

    /**
     * @brief Parent node of the given node
     */
    struct RedBlackTreeNode *parent;
}RedBlackTreeNode;

/**
 * @brief Data structure that defines A red black binary search tree
 */
typedef BinaryTree RedBlackTree;

/**
 * @brief Initializes a RedBlackTree with its default values
 * @param compare User compare function
 * @param destroy User destroy function
 */
void rbtree_create(RedBlackTree *tree, int (*compare)(const void* key1, const void* key2), void(*destroy) (void* value));

/**
 * @brief Destroys a given RedBlackTree
 * @param tree RedBlackTree to be destroyed
 */
void rbtree_destroy(RedBlackTree *tree);

/**
 * @brief Tries to add a value into the given RedBlackTree
 * @param tree Tree to add a new value
 * @param value Value to to be added in the given RedBlackTree
 * @return 0 if the value was inserted correctly, 1 if already present, -1 otherwise
 */
int rbtree_add(RedBlackTree * tree, const void * value);

/**
 * @brief Tries to remove a value into the given RedBlackTree
 * @param tree Tree to remove a value
 * @param value Value to to be removed in the given RedBlackTree
 * @return true if the value was removed false otherwise
 */
bool rbtree_remove(RedBlackTree * tree, const void * value);

/**
 * @brief Determine if a given value is present or not in the given AvlTree
 * @param tree AvlTree to lookup in
 * @param value Double pointer on the value to check and returned reference
 * @return true if the value is present in the given AvlTree, false otherwise
 */
bool rbtree_containsKey(const RedBlackTree * tree, void ** value);

#ifdef __cpluscplus
/**
 * @brief Macro that evaluates the size of the given RedBlackTree
 * @param tree RedBlackTree to evaluates the size
 * @return The current size of the given AvlTree
 */
#define rbtree_size(tree) ((tree)->size)
#else
/**
 * @brief Inline function that evaluates the size of the given RedBlackTree
 * @param tree RedBlackTree to evaluates the size
 * @return The current size of the given AvlTree
 */
static inline int rbtree_size(RedBlackTree * tree){
    return tree->size;
}
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_RBTREE_H
