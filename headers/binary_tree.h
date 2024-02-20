//
// Created by maxim on 16/02/2024.
//
// Implémentation d'une structure de données "BinaryTree"
//

#ifndef COLLECTIONS_COMMONS_BINARY_TREE_H
#define COLLECTIONS_COMMONS_BINARY_TREE_H

#include "binary_tree_node.h"
#include "simple_queue.h"

// Fonction pour obtenir le niveau de l'arbre binaire de manière ordonnée
int **levelOrder(struct TreeNode *root, int *returnSize,
                 int **returnColumnSizes);

#endif //COLLECTIONS_COMMONS_BINARY_TREE_H
