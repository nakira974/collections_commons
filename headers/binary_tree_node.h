//
// Created by maxim on 16/02/2024.
//
// Implémentation d'une structure de données "TreeNode"
//

#ifndef COLLECTIONS_COMMONS_BINARY_TREE_NODE_H
#define COLLECTIONS_COMMONS_BINARY_TREE_NODE_H

#include <malloc.h>

// Structure de données d'un noeud d'un "BinaryTree"
struct TreeNode {
    // Valeur du noeud
    int val;
    // Valeur fille de gauche
    struct TreeNode *left;
    // Valeur fille de droite
    struct TreeNode *right;
};


// Fonction pour créer un nouveau nœud d'arbre binaire
struct TreeNode *create_tree_node(int val);

#endif //COLLECTIONS_COMMONS_BINARY_TREE_NODE_H
