//
// Created by maxim on 16/02/2024.
//
#include "binary_tree_node.h"

struct TreeNode* create_tree_node(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}
