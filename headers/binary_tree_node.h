//
// Created by maxim on 16/02/2024.
//
// Implémentation d'une structure de données "TreeNode"
//

#ifndef COLLECTIONS_COMMONS_BINARY_TREE_NODE_H
#define COLLECTIONS_COMMONS_BINARY_TREE_NODE_H

#include <malloc.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


// Fonction pour créer un nouveau nœud d'arbre binaire
struct TreeNode *newNode(int val);

#endif //COLLECTIONS_COMMONS_BINARY_TREE_NODE_H
