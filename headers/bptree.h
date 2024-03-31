/**
 * @file bptree.h
 * @brief This file contains the API for B+, balanced search tree
 * @author Maxime Loukhal
 * @date 30/03/2024
 */

#ifndef COLLECTIONS_COMMONS_BPTREE_H
#define COLLECTIONS_COMMONS_BPTREE_H

#include "btree.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief BPlusTree node maximum children
*/
#define BPLUSTREE_MAX_KEYS 5

/**
 * @brief Data structure that defines a B tree node
 */
typedef struct BPlusTreeNode {
    /**
     * @brief Keys of the node
     */
    void *keys[BPLUSTREE_MAX_KEYS];
    /**
     * @brief Values of the node
     */
    void *values[BPLUSTREE_MAX_KEYS];
    /**
     * @brief Child node of the current node
     */
    struct BPlusTreeNode *next;
    /**
     * @brief Parent node of the current node
     */
    struct BPlusTreeNode *last;
} BPlusTreeNode;

/**
 * @brief Data structure that defines a B+ search tree
 */
typedef BTree BPlusTree;


#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_BPTREE_H
