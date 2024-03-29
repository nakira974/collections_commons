//
// Created by maxim on 29/03/2024.
//

#include <stdlib.h>
#include <string.h>
#include "avltree.h"

/**
 * @brief Private function that destroys the right element of an avl node
 * @param tree Avl tree where to removed the right child
 * @param node Node to remove the right child
 */
static void destroy_right(AvlTree  *tree, BinaryTreeNode *node);

/**
 * @brief Private function to rotate the current node to left
 * @param node Node to rotate and pointer to the rotated node
 */
static void rotate_left(BinaryTreeNode **node);

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
    }
}