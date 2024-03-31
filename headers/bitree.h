/**
 * @file bitree.h
 * @brief This file contains the API for an abstract binary tree
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
 * @brief Data structure definition for a BinaryTree node
 */
typedef struct BinaryTreeNode {
    /**
     * @brief Node's value
     */
    void *value;
    /**
     * @brief Node's left child
     */
    struct BinaryTreeNode *left;
    /**
     * @brief Node's right child
     */
    struct BinaryTreeNode *right;
} BinaryTreeNode;

/**
 * @brief Data structure definition for a BinaryTree
 */
typedef struct BinaryTree {
    /**
     * @brief Binary tree current size
     */
    int size;
    /**
     * @brief User compareBlocks handle for stored values > (-1) , = (0) or < (1)
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
     * @brief Binary tree current root node
     */
    BinaryTreeNode *root;
} BinaryTree;

/**
 * @brief Creates a given BinaryTree with default values
 * @param tree Tree to be created
 * @param destroy Destroy user handle
 */
void bitree_create(BinaryTree *tree, void(*destroy)(void *value));

/**
 * @brief Destroys and clean memory of a given BinaryTree
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
 * @brief Remove the left child of the given node in the given BinaryTree
 * @param tree Binary tree where to remove the left node's value
 * @param node Node to remove the left child
 */
void bitree_removeLeft(BinaryTree *tree, BinaryTreeNode *node);

/**
 * @brief Remove the right child of the given node in the given BinaryTree
 * @param tree Binary tree where to remove the right node's value
 * @param node Node to remove the right child
 */
void bitree_removeRight(BinaryTree *tree, BinaryTreeNode *node);

/**
 * @brief Merges the left and right binary tress into out where value will be set as root's value
 * @param out Output tree after tree merge operation
 * @param left Left BinaryTree to be merged
 * @param right Right BinaryTree to be merged
 * @param value Value to be designated as out root's node value
 */
bool bitree_merge(BinaryTree *out, BinaryTree *left, BinaryTree *right, const void *value);

/**
 * @brief Returns the current maximum depth of the given BinaryTree
 * @param tree Binary tree to get the maximum depth
 * @return The maximum depth of the given BinaryTree
 */
int bitree_maxDepth(BinaryTree *tree);

/**
 * @brief Returns the current maximum depth of the given BinaryTree
 * @param tree Binary tree to get the maximum depth
 * @return The maximum depth of the given BinaryTree
 */
int bitree_maxDepthBranch(BinaryTreeNode *branchRoot);

/**
 * @brief Determines if two nodes are in the same BinaryTree or not
 * @param compareTo Node compare function
 * @param left Left node to be compared
 * @param right Right node to be compared
 * @return true if two nodes are in the same tree, false otherwise
 */
bool
bitree_isSameTree(int (*compareTo)(const void *value1, const void *value2), BinaryTreeNode *left, BinaryTreeNode *right);

/**
 * @brief Invert the given BinaryTree
 * @param out Inverted BinaryTree
 * @param tree Binary tree to invert
 */
bool bitree_invert(BinaryTree *out, BinaryTree *tree);

/**
 * @brief Determine if two nodes are symmetric or not
 * @param compareTo Nodes value compare function, usefully used to add some other nodes comparer
 * @param left Left node to be compared
 * @param right Right node to be compared
 * @return true if given nodes are symmetric, false otherwise
 */
bool
bitree_isMirror(int (*compareTo)(const void *value1, const void *value2), BinaryTreeNode *left, BinaryTreeNode *right);

/**
 * @brief Returns a BinaryTree by level
 * @param tree Tree to return as an array of arrays
 * @param returnSize Number of levels in the BinaryTree
 * @param returnColumnSizes Number of elements per level
 * @return Array of values per level in the given BinaryTree
 */
void **bitree_levelOrder(BinaryTree *tree, int *returnSize, int **returnColumnSizes);

/**
 * @brief Construct a BinaryTree from preorder and inorder traversal.
 *
 * @param preorder An array representing the preorder traversal of the tree.
 * @param preorder_size The size of the preorder array.
 * @param inorder An array representing the inorder traversal of the tree.
 * @param inorder_size The size of the inorder array.
 * @param destroy The destroy function of the created BinaryTree
 * @param compareTo Node value compareBlocks function
 *
 * @return A pointer to the constructed BinaryTree.
 */
BinaryTree *bitree_build_from_preorder_inorder(void **preorder, int preorder_size, void **inorder, int inorder_size,
                                               void(*destroy)(void *value),
                                               int (*compareTo)(const void *value1, const void *value2));

/**
* @brief Construct a BinaryTree from inorder and postorder traversal.
*
* @param inorder An array representing the inorder traversal of the tree.
* @param inorderSize The size of the inorder array.
* @param postorder An array representing the postorder traversal of the tree.
* @param postorderSize The size of the postorder array.
* @param destroy The destroy function of the created BinaryTree
* @param compareTo Node value compareBlocks function
* @return A pointer to the root node of the constructed BinaryTree.
*/
BinaryTree *bitree_build_from_inorder_postorder(void **inorder,
                                                int inorderSize,
                                                int **postorder,
                                                int postorderSize,
                                                void(*destroy)(void *value),
                                                int (*compareTo)(const void *value1, const void *value2));

/**
 * @brief Returns the longest path length in the given branch
 * @param root Root node of the given branch to find longest path
 * @param diameter Pointer to the returned longest path length
 * @return
 */
int bitree_height(BinaryTreeNode *root, int *diameter);

/**
 * @brief Returns the longest path length in the given BinaryTree
 * @param tree BinaryTree to get the longest path on
 * @return The longest path length of the given BinaryTree
 */
int bitree_diameter(BinaryTree *tree);

/**
 * @brief Count the number of nodes in the given BinaryTree
 * @param tree BinaryTree to count nodes
 * @return Node count of the given BinaryTree
 */
int bitree_count(BinaryTree *tree);

#ifdef __cplusplus
/**
 * @brief Inline function that evaluates the size of the given BinaryTree
 * @param tree Binary tree to get the size
 * @return Current size of the given BinaryTree
 */
static inline int bitree_size(BinaryTree *tree){
    return tree->size;
}

/**
 * @brief Inline function that evaluates the root node of the given BinaryTree
 * @param tree Binary tree to get the root node
 * @return Current root node of the given BinaryTree
 */
static inline BinaryTreeNode * bitree_root(BinaryTree *tree){
    return tree->root;
}

/**
 * @brief Inline function that evaluates if a node is the root of its BinaryTree
 * @param node Node to determine if it's a root
 * @return true if the given node is the root of its BinaryTree, false otherwise
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
static inline bool bitree_isSymmetric(BinaryTree * tree) { return bitree_isMirror((tree)->compareTo, (tree)->root, (tree)->root); }
#else

/**
 * @brief Macro that evaluates if the given tree is symmetric or not
 */
#define bitree_isSymmetric(tree) (bitree_isMirror((tree)->compareTo, (tree)->root, (tree)->root))

/**
 * @brief Macro that evaluates the size of the given BinaryTree
 * @param tree Binary tree to get the size
 * @return Current size of the given BinaryTree
 */
#define bitree_size(tree) ((tree)->size)

/**
 * @brief Macro that evaluates the root node of the given BinaryTree
 * @param tree Binary tree to get the root node
 * @return Current root node of the given BinaryTree
 */
#define bitree_root(tree) ((tree)->root)

/**
 * @brief Macro that evaluates if a node is the root of its BinaryTree
 * @param node Node to determine if it's a root
 * @return true if the given node is the root of its BinaryTree, false otherwise
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
