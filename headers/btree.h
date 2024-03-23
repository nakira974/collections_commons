/**
 * @file btree.h
 * @brief This file contains the API for B type, binary search tree
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
 * @brief Data structure that defines A B binary search tree
 */
typedef BinaryTree BTree;

/**
 * @brief Data structure that defines a B tree node
 */
typedef struct BTreeNode{
    /**
     * @brief Stored keys
     */
    void* val[BTREE_MAX_NODES + 1];
    /**
     * @brief Current children count
     */
    int count;
    /**
     * @brief Node's children
     */
    struct BTreeNode *link[BTREE_MAX_NODES + 1];
} BTreeNode;

/**
 * @brief Creates a BTree with its default values
 * @param tree BTree to create
 * @param compare User compare handle
 * @param destroy
 */
void btree_create(BTree *tree, void (*compare)(const void* key1, const void* key2), void(*destroy) (void* value));

/**
 * @brief Creates a BTreeNode with its default values
 * @param tree
 * @param child
 * @param val
 * @return
 */
BTreeNode * btree_createNode(BTree  *tree ,BTreeNode *child, void *val);

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_BTREE_H
