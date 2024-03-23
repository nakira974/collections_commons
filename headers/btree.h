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
 * @param destroy User destroy handle
 */
void btree_create(BTree *tree, int (*compare)(const void* key1, const void* key2), void(*destroy) (void* value));

/**
 * @brief Destroys a given BTree
 * @param tree BTree to be destroyed
 */
void btree_destroy(BTree *tree);

/**
 * @brief Creates a BTreeNode with its default values
 * @param tree Tree where to create the node
 * @param child New node child
 * @param value Value to be set in the node
 * @return A new BTreeNode
 */
BTreeNode * btree_nodeCreate(BTree tree,BTreeNode *child, void *value);

/**
 * @brief Insert a child BTreeNode in a given BTreeNode at a specified position
 * @param index Index where to insert the child node
 * @param node Parent node
 * @param child Child node
 * @param value Key to be inserted
 */
void btree_nodeAdd(int index, BTreeNode *node, BTreeNode *child, void* value);

/**
 * @brief Split a node to maintain the balance of the tree
 * @param index Position to split
 * @param node Node to be split
 * @param child Child node of the new node
 * @param newNode New node where the value is deported
 * @param value Value to be insert somewhere else
 * @param pValue Pointer to the new value
 */
void btree_nodeSplit(int index, BTreeNode *node,
                     BTreeNode *child, BTreeNode **newNode, void* value, void **pValue);


/**
 * @brief Set a given value into a given node
 * @param node Node where to set a new value
 * @param child Returned child node in case of split
 * @param value Value to be inserted
 * @param pValue Pointer on the inserted value in case of split
 * @return
 */
bool btree_nodeSetValue(BTreeNode *node, BTreeNode **child , void* value, void **pValue);

/**
 * @brief Insert a given value in the given BTree
 * @param tree BTree where to insert the value
 * @param value Value to be inserted
 */
void btree_add(BTree *tree, void* value,int *pos);

/**
 * @brief Tries to remove a value into the given BTree
 * @param tree Tree to remove a value
 * @param value Value to to be removed in the given BTree
 * @return true if the value was removed false otherwise
 */
bool btree_remove(BTree * tree, const void * value);

/**
 * @brief Determine if a given value is present or not in the given BTree
 * @param tree BTree to determine if the value is in
 * @param value Value to determine if it's in the given BTree
 * @return true if the value is present in the given BTree, otherwise false
 */
bool btree_containsKey(BTree tree, void* value);

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
