//
// Created by maxim on 16/02/2024.
//
#include "binary_tree.h"

int **levelOrder(struct TreeNode *root, int *returnSize,
                 int **returnColumnSizes) {
    if (root == NULL) {
        // Si l'arbre est vide, fixe la taille de retour à 0 et retourne NULL
        *returnSize = 0;
        return NULL;
    }

    // Crée une file pour stocker les nœuds
    Queue * queue = (Queue*) malloc(sizeof (Queue));
    queue_create(queue, free);
    // Ajoute la racine à la file
    queue_enqueue(queue, root);

    // Initialisation des tableaux de résultats
    // Taille arbitraire. -1000 <= Node.val <= 1000
    int maxLevelNodes = 1000;
    // Alloue de l'espace mémoire pour le tableau de résultats et le tableau des tailles de colonnes
    int **result = (int **) malloc(maxLevelNodes * sizeof(int *));
    *returnColumnSizes = (int *) malloc(maxLevelNodes * sizeof(int));

    int levelIndex = 0; // Indice du niveau actuel

    // On instancie une autre file pour stocker les noeuds du prochain niveau
    Queue *nextQueue = (Queue*) malloc(sizeof (Queue));

    while (list_first(queue)!= NULL) {
        // Taille arbitraire pour le tableau du niveau actuel
        int *currentLevel = (int *) malloc(1000 * sizeof(int));
        int count = 0; // Compteur pour les nœuds dans chaque niveau

        // Parcourt le niveau actuel jusqu'à ce que la file soit vide
        while (list_first(queue)!= NULL) {
            // Récupère le nœud en tête de file
            struct TreeNode *currNode;
            queue_dequeue(queue, &currNode);
            // Ajoute la valeur du nœud au tableau du niveau actuel
            currentLevel[count++] = currNode->val;

            // Ajoute les enfants du nœud au prochain niveau s'ils existent
            if (currNode->left != NULL)
                queue_enqueue(nextQueue, currNode->left);
            if (currNode->right != NULL)
                queue_enqueue(nextQueue, currNode->right);
        }

        // Ajuste la taille du tableau du niveau actuel et l'ajoute au résultat
        if (levelIndex >= maxLevelNodes) {
            // Double la taille du tableau
            maxLevelNodes *= 2;
            result = (int **) realloc(result, maxLevelNodes * sizeof(int *));
            *returnColumnSizes =
                    (int *) realloc(*returnColumnSizes, maxLevelNodes * sizeof(int));
        }
        currentLevel = (int *) realloc(currentLevel, count * sizeof(int));
        result[levelIndex] = currentLevel;
        (*returnColumnSizes)[levelIndex++] = count;

        // Passe au prochain niveau en échangeant les files
        queue_destroy(queue);
        free(queue);
        queue = nextQueue;
        queue_create(nextQueue, free);
    }

    // Libère la mémoire de la file du prochain niveau
    queue_destroy(nextQueue);
    free(nextQueue);

    // Met à jour la taille de retour
    *returnSize = levelIndex;

    // Retourne le tableau des niveaux de l'arbre binaire
    return result;
}