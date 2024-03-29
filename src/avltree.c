//
// Created by maxim on 29/03/2024.
//

#include <string.h>
#include "avltree.h"

/**
 * @brief Private function that destroys the right element of an avl node
 * @param tree Avl tree where to removed the right child
 * @param node Node to remove the right child
 */
static void destroy_right(AvlTree  *tree, BinaryTreeNode *node);

/**
 * @brief Private function that destroys the right element of an avl node
 * @param tree Avl tree where to removed the left child
 * @param node Node to remove the left child
 */
static void destroy_left(AvlTree  *tree, BinaryTreeNode *node);

/**
 * @brief Private function to rotate the current node to the left
 * @param node Node to rotate and pointer to the rotated node
 */
static void rotate_left(BinaryTreeNode **node);

/**
 * @brief Private function to rotate the current node to the right
 * @param node Node to rotate and pointer to the rotated node
 */
static void rotate_right(BinaryTreeNode **node);

/**
 * @brief Tries to add a value into the given tree
 * @param tree Tree to insert the value in
 * @param node Created node if operation succeed
 * @param value Value to be add in the given tree
 * @param balance Tree balance state
 * @return 0 if the value was inserted correctly, 1 if already present, -1 otherwise
 */
static int add(AvlTree *tree, BinaryTreeNode **node, const void* value, int * balance);

/**
 * @brief Private function that hides a given node in a given tree
 * @param tree Tree where to hide a given node
 * @param node Node to be hidden
 * @param value Value to be hide
 * @return true if the given node was hidden, otherwise false
 */
static bool hide(AvlTree *tree, BinaryTreeNode *node, const void* value);

/**
 * @brief Private function to determine if a value is present or not in the given tree
 * @param tree Tree to determine if the value is present or not
 * @param node Node where to start the search
 * @param value Value to search and returned reference if present
 * @return true if the given value is present, otherwise false
 */
static bool containsKey(AvlTree *tree, BinaryTreeNode *node, void **value);

static void rotate_left(BinaryTreeNode **node){
    BinaryTreeNode *left, *grand_child;

    left = bitree_left(*node);
    if(((AvlNode*) bitree_value(left))->factor == AVL_TO_L ){
        // Do a left-left rotation
        bitree_left(*node) = bitree_right(left);
        bitree_right(left) = *node;
        ((AvlNode*)bitree_value(*node))->factor = AVL_BALANCED;
        ((AvlNode*)bitree_value(left))->factor = AVL_BALANCED;
        *node = left;
    }else{
        // Do a left-right rotation
        grand_child = bitree_right(left);
        bitree_right(left) = bitree_left(grand_child);
        bitree_left(grand_child) = left;
        bitree_left(*node) = bitree_right(grand_child);
        bitree_right(grand_child) = *node;

        switch (((AvlNode*) bitree_value(grand_child))->factor) {
            case AVL_TO_L :
                ((AvlNode*) bitree_value(*node))->factor = AVL_TO_R;
                ((AvlNode*) bitree_value(left))->factor = AVL_BALANCED;
                break;
            case AVL_BALANCED:
                ((AvlNode*) bitree_value(*node))->factor = AVL_BALANCED;
                ((AvlNode*) bitree_value(left))->factor = AVL_BALANCED;
                break;
            case AVL_TO_R:
                ((AvlNode*) bitree_value(*node))->factor = AVL_BALANCED;
                ((AvlNode*) bitree_value(left))->factor = AVL_TO_L;
                break;
        }

        ((AvlNode*) bitree_value(grand_child))->factor = AVL_BALANCED;
        *node = grand_child;
    }
}


static void rotate_right(BinaryTreeNode **node){
    BinaryTreeNode *right, *grand_child;

    right = bitree_right(*node);
    if(((AvlNode*) bitree_value(right))->factor == AVL_TO_R ){
        // Do a right-right rotation
        bitree_right(*node) = bitree_left(right);
        bitree_left(right) = *node;
        ((AvlNode*)bitree_value(*node))->factor = AVL_BALANCED;
        ((AvlNode*)bitree_value(right))->factor = AVL_BALANCED;
        *node = right;
    }else{
        // Do a right-right rotation
        grand_child = bitree_left(right);
        bitree_left(right) = bitree_right(grand_child);
        bitree_right(grand_child) = right;
        bitree_right(*node) = bitree_left(grand_child);
        bitree_left(grand_child) = *node;

        switch (((AvlNode*) bitree_value(grand_child))->factor) {
            case AVL_TO_L :
                ((AvlNode*) bitree_value(*node))->factor = AVL_BALANCED;
                ((AvlNode*) bitree_value(right))->factor = AVL_TO_R;
                break;
            case AVL_BALANCED:
                ((AvlNode*) bitree_value(*node))->factor = AVL_BALANCED;
                ((AvlNode*) bitree_value(right))->factor = AVL_BALANCED;
                break;
            case AVL_TO_R:
                ((AvlNode*) bitree_value(*node))->factor = AVL_TO_L;
                ((AvlNode*) bitree_value(right))->factor = AVL_BALANCED;
                break;
        }

        ((AvlNode*) bitree_value(grand_child))->factor = AVL_BALANCED;
        *node = grand_child;
    }
}

static void destroy_left(AvlTree *tree, BinaryTreeNode *node){
    BinaryTreeNode **pos;

    // Can't destroy an empty tree
    if(bitree_size(tree) == 0) return;

    // Determine where to destroy the node

    if(node == NULL) pos = &tree->root;
    else pos = &node->left;

    // Destroy nodes

    if(*pos != NULL){
        destroy_left(tree, *pos);
        destroy_right(tree, *pos);

        if(tree->destroy != NULL){
            // Cleanup the AVL node value
            tree->destroy(((AvlNode*)(*pos)->value)->value);
        }

        // Cleanup the value of the AvlNode and the node itself
        free((*pos)->value);
        free(*pos);
        *pos = NULL;

        // Adjust the size of the tree to handle the deletion
        tree->size--;
    }
}

static void destroy_right(AvlTree *tree, BinaryTreeNode *node){
    BinaryTreeNode **pos;

    if(bitree_size(tree) == 0) return;

    if(node == NULL) pos = &tree->root;
    else pos = &node->right;

    // Destroy nodes

    if(*pos != NULL){
        destroy_left(tree, *pos);
        destroy_right(tree, *pos);

        if(tree->destroy != NULL){
            // Cleanup the AvlNode value
            tree->destroy(((AvlNode*)(*pos)->value)->value);
        }

        // Cleanup the value of the AvlNode and the node itself
        free((*pos)->value);
        free(((*pos)));
        *pos = NULL;

        tree->size--;
    }
}

static int add(AvlTree *tree, BinaryTreeNode **node, const void* value, int * balance){
    AvlNode  *avl_value;
    int cmp_value, result;

    // Insert the value in the given tree

    if(bitree_isNodeEOB(*node)){
        // Empty tree insertion

        if((avl_value = (AvlNode*)malloc(sizeof (AvlNode))) == NULL) return -1;
        avl_value->factor = AVL_BALANCED;
        avl_value->hidden = false;
        avl_value->value = (void*) value;

        return bitree_addLeft(tree, *node,  avl_value);
    }else{
        // Non-empty tree insertion
        cmp_value = tree->compareTo(value, ((AvlNode*) bitree_value(*node))->value);

        if(cmp_value < 0){
            if(bitree_isNodeEOB(bitree_left(*node))){
                if((avl_value = (AvlNode*) malloc(sizeof (AvlNode))) == NULL) return -1;
                avl_value->factor = AVL_BALANCED;
                avl_value->hidden = false;
                avl_value->value = (void*) value;

                if(!bitree_addLeft(tree, *node, avl_value)) return -1;
                *balance = 0;
            }
        }else{
            if((result = add(tree, &bitree_left(*node), value, balance)) != 0) return result;
        }
    }

    // Check that the tree is still balanced
    if(!(*balance)){
        switch (((AvlNode*) bitree_value(*node))->factor ) {
            case AVL_TO_L:
                rotate_left(node);
                *balance = 1;
                break;
            case AVL_BALANCED:
                ((AvlNode*) bitree_value(*node))->factor = AVL_TO_L;
                break;

            case AVL_TO_R:
                ((AvlNode*) bitree_value(*node))->factor = AVL_BALANCED;
                *balance = 1;
                break;
        }
    }else if(cmp_value > 0){
        // Start from the right

        if(bitree_isNodeEOB(bitree_right(*node))){
            if((avl_value = (AvlNode*) malloc(sizeof(AvlNode))) == NULL) return -1;
            avl_value->factor = AVL_BALANCED;
            avl_value->hidden = false;
            avl_value->value = (void*) value;

            if(bitree_addRight(tree, *node, avl_value) != 0) return -1;
            *balance = 0;
        }else{
            if((result = add(tree, &bitree_right(*node), value, balance)) != 0) return result;
        }
    }

    // Check that the tree is still balanced

    if(!(*balance)){
        switch (((AvlNode*) bitree_value(*node))->factor) {
            case AVL_TO_L:
                ((AvlNode*)bitree_value(*node))->factor = AVL_BALANCED;
                *balance = 1;
                break;
            case AVL_BALANCED:
                ((AvlNode*)bitree_value(*node))->factor = AVL_TO_R;
                break;

            case AVL_TO_R:
                rotate_right(node);
                *balance =1;
        }
    }else{
        // Copy of the value

        // Do nothing if the value is already in the tree and not hidden
        if(!((AvlNode*) bitree_value(*node))->hidden) return -1;
        else{
            // Insert the new value and set it as visible

            if(tree->destroy != NULL){
                 // Destroy the hidden value because it must be replaced
                 tree->destroy( ((AvlNode*) bitree_value(*node))->value );
            }

            ((AvlNode*) bitree_value(*node))->value = (void*) value;
            ((AvlNode*) bitree_value(*node))->hidden = false;
            // We do not balance the tree because the struct did not change
            *balance = 1;
        }
    }

    return 0;
}

static bool hide(AvlTree *tree, BinaryTreeNode *node, const void* value){
    int cmp_value;
    bool result;

    if(bitree_isNodeEOB(node)) return -1;

    cmp_value = tree->compareTo(value, ((AvlNode*) bitree_value(node))->value);

    if(cmp_value < 0){
        // Start from the left

        result = hide(tree, bitree_left(node), value);
    }else if(cmp_value > 0){
        // Start from the right

        result = hide(tree, bitree_right(node), value);
    }else{
        ((AvlNode*) bitree_value(node))->hidden = true;
        result = false;
    }

    return result;
}

static bool containsKey(AvlTree *tree, BinaryTreeNode *node, void **value){
    int cmp_value;
    bool result;

    if(bitree_isNodeEOB(node)) return false;

    cmp_value = tree->compareTo(*value, ((AvlNode*) bitree_value(node))->value);

    if(cmp_value < 0){
        // Start from the left
        result = containsKey(tree, bitree_left(node), value);
    }else if(cmp_value > 0){
        // Start from the right
        result = containsKey(tree, bitree_right(node), value);
    }else{
        if(!((AvlNode*) bitree_value(node))->hidden){
            *value = ((AvlNode*) bitree_value(node))->value;
            result = true;
        }else{
            return false;
        }
    }

    return result;
}

void avltree_create(AvlTree *tree, int (*compare)(const void* key1, const void* key2), void(*destroy) (void* value)){
    bitree_create(tree, destroy);
    tree->compareTo = compare;
}

void avltree_destroy(AvlTree *tree){
    destroy_left(tree, NULL);
    memset(tree, 0, sizeof(AvlTree));
}

int avltree_add(AvlTree * tree, const void * value){
    int balance = 0;
    return add(tree, &bitree_root(tree), value, &balance);
}

bool avltree_remove(AvlTree * tree, const void * value){
    return hide(tree, bitree_root(tree), value);
}

bool avltree_containsKey(AvlTree * tree, void ** value){
    return containsKey(tree, bitree_root(tree), value);
}
