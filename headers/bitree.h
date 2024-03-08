/**
 * @file bitree.h
 * @brief This file contains the API for binary trees
 * @author Maxime Loukhal
 * @date 06/03/2024
 */

#ifndef COLLECTIONS_COMMONS_BITREE_H
#define COLLECTIONS_COMMONS_BITREE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdlib>
#include <cstdbool>
#else
#include <stdlib.h>
#include <stdbool.h>
#endif

/**
 * @brief Data structure definition for a binary tree node
 */
typedef struct BinaryTreeNode{
    /**
     * @brief Node's value
     */
    void *value;
    /**
     * @brief Node's left child
     */
    struct BinaryTreeNode* left;
    /**
     * @brief Node's right child
     */
    struct BinaryTreeNode* right;
} BinaryTreeNode;

/**
 * @brief Data structure definition for a binary tree
 */
 typedef struct BinaryTree{
     /**
      * @brief Binary tree current size
      */
     int size;
     /**
      * @brief User equals handle for stored values
      * @param value1 Value 1 to be compared
      * @param value2 Value 2 to be compared
      * @return true if values are equal, false otherwise
      */
     bool (*equals) (const void* value1, const void *value2);
     /**
      * @brief User destroy method to clean node's value
      * @param value Value to be removed from the tree
      */
     void (*destroy)(void* value);
     /**
      * @brief Binary tree current root node
      */
     BinaryTreeNode* root;
 }BinaryTree;

 /**
  * @brief Creates a given binary tree with default values
  * @param tree Tree to be created
  * @param destroy Destroy user handle
  */
 void bitree_create(BinaryTree *tree, void(*destroy)(void* value));

 /**
  * @brief Destroys and clean memory of a given binary tree
  * @param tree Binary tree to be destroyed
  */
 void bitree_destroy(BinaryTree *tree);

 /**
  * @brief Try to create a new left child node of the given node in the given tree
  * @param tree Tree to add a left node
  * @param node Node to add a left child
  * @param value Value to be added
  * @return true if the left node was created, false otherwise
  */
 bool bitree_addLeft(BinaryTree *tree, BinaryTreeNode *node, const void *value);

/**
* @brief Try to create a new right child node of the given node in the given tree
* @param tree Tree to add a right node
* @param node Node to add a right child
* @param value Value to be added
* @return true if the right node was created, false otherwise
*/
bool bitree_addRight(BinaryTree *tree, BinaryTreeNode *node, const void *value);

/**
 * @brief Remove the left child of the given node in the given binary tree
 * @param tree Binary tree where to remove the left node's value
 * @param node Node to remove the left child
 */
void bitree_removeLeft(BinaryTree *tree, BinaryTreeNode *node);

/**
 * @brief Remove the right child of the given node in the given binary tree
 * @param tree Binary tree where to remove the right node's value
 * @param node Node to remove the right child
 */
void bitree_removeRight(BinaryTree *tree, BinaryTreeNode *node);

/**
 * @brief Merges the left and right binary tress into out where value will be set as root's value
 * @param out Output tree after tree merge operation
 * @param left Left binary tree to be merged
 * @param right Right binary tree to be merged
 * @param value Value to be designated as out root's node value
 */
void bitree_merge(BinaryTree *out, BinaryTree *left, BinaryTree *right, const void *value);

/**
 * @brief Returns the current maximum depth of the given binary tree
 * @param tree Binary tree to get the maximum depth
 * @return The maximum depth of the given binary tree
 */
int bitree_maxDepth(BinaryTree * tree);

/**
 * @brief Determines if two nodes are in the same binary tree or not
 * @param left Left node to be compared
 * @param right Right node to be compared
 * @return true if two nodes are in the same tree, false otherwise
 */
bool bitree_isSameTree(BinaryTreeNode* left, BinaryTreeNode* right);

/**
 * @brief Invert the given binary tree
 * @param out Inverted binary tree
 * @param tree Binary tree to invert
 */
void bitree_invert(BinaryTree *out, BinaryTree * tree);

/**
 * @brief Determine if two nodes are symmetric or not
 * @param left Left node to be compared
 * @param right Right node to be compared
 * @return true if given nodes are symmetric, false otherwise
 */
bool bitree_isMirror(BinaryTreeNode* left, BinaryTreeNode* right);

/**
 * @brief Returns a binary tree by level
 * @param tree Tree to return as an array of arrays
 * @param returnSize Number of levels in the binary tree
 * @param returnColumnSizes Number of elements per level
 * @return Array of values per level in the given binary tree
 */
void **bitree_levelOrder(BinaryTree *tree, int *returnSize, int **returnColumnSizes);

#ifdef __cplusplus
/**
 * @brief Inline function that evaluates the size of the given binary tree
 * @param tree Binary tree to get the size
 * @return Current size of the given binary tree
 */
static inline int bitree_size(BinaryTree *tree){
    return tree->size;
}

/**
 * @brief Inline function that evaluates the root node of the given binary tree
 * @param tree Binary tree to get the root node
 * @return Current root node of the given binary tree
 */
static inline BinaryTreeNode * bitree_root(BinaryTree *tree){
    return tree->root;
}

/**
 * @brief Inline function that evaluates if a node is the root of its binary tree
 * @param node Node to determine if it's a root
 * @return true if the given node is the root of its binary tree, false otherwise
 */
static inline bool bitree_isNodeEOB(BinaryTreeNode *node){
    return ((node)== nullptr);
}

/**
 * @brief Inline function that evaluates if a node is leaf in its tree
 * @param node Node to determine if it's a leaf
 * @return true if is the given node is a leaf, false otherwise
 */
static inline bool bitree_isNodeLeaf(BinaryTreeNode *node){
    return ((node)->left == nullptr && (node)->right == nullptr);
}

/**
 * @brief Inline function that evaluates the value of a given node
 * @param node Node to return the value
 * @return The value of the given node
 */
static inline void *bitree_value(BinaryTreeNode *node){
    return ((node)->value);
}

/**
 * @brief Inline function that evaluates the right child of a given node
 * @param node Node to return the right child
 * @return The right child of the given node
 */
static inline  BinaryTreeNode  *bitree_right(BinaryTreeNode *node){
    return ((node)->right);
}

/**
 * @brief Inline function that evaluates the left child of a given node
 * @param node Node to return the left child
 * @return The left child of the given node
 */
static inline BinaryTreeNode  *bitree_left(BinaryTreeNode *node){
    return ((node)->left);
}

/**
 * @brief Inline function that evaluates if the given tree is symmetric or not
 */
static inline bool bitree_isSymmetric(BinaryTree * tree) { return bitree_isMirror((tree)->root, (tree)->root); }
#else

/**
 * @brief Macro that evaluates if the given tree is symmetric or not
 */
#define bitree_isSymmetric(tree) (bitree_isMirror((tree)->root, (tree)->root))

/**
 * @brief Macro that evaluates the size of the given binary tree
 * @param tree Binary tree to get the size
 * @return Current size of the given binary tree
 */
#define bitree_size(tree) ((tree)->size)

/**
 * @brief Macro that evaluates the root node of the given binary tree
 * @param tree Binary tree to get the root node
 * @return Current root node of the given binary tree
 */
#define bitree_root(tree) ((tree)->root)

/**
 * @brief Macro that evaluates if a node is the root of its binary tree
 * @param node Node to determine if it's a root
 * @return true if the given node is the root of its binary tree, false otherwise
 */
#define bitree_isNodeEOB(node) ((node) == NULL)

/**
 * @brief Macro that evaluates if a node is leaf in its tree
 * @param node Node to determine if it's a leaf
 * @return true if is the given node is a leaf, false otherwise
 */
#define bitree_isNodeLeaf(node) ((node)->left == NULL (node)->right == NULL)

/**
 * @brief Macro that evaluates the value of a given node
 * @param node Node to return the value
 * @return The value of the given node
 */
#define bitree_value(node) ((node)->value)

/**
 * @brief Macro that evaluates the left child of a given node
 * @param node Node to return the left child
 * @return The left child of the given node
 */
#define bitree_left(node) ((node)->left)

/**
 * @brief Macro that evaluates the right child of a given node
 * @param node Node to return the right child
 * @return The right child of the given node
 */
#define bitree_right(node) ((node)->left)

#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_BITREE_H
