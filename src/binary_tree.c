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
    struct Queue *queue = createQueue();
    // Ajoute la racine à la file
    enqueue(queue, root);

    // Initialisation des tableaux de résultats
    // Taille arbitraire. -1000 <= Node.val <= 1000
    int maxLevelNodes = 1000;
    // Alloue de l'espace mémoire pour le tableau de résultats et le tableau des tailles de colonnes
    int **result = (int **) malloc(maxLevelNodes * sizeof(int *));
    *returnColumnSizes = (int *) malloc(maxLevelNodes * sizeof(int));

    int levelIndex = 0; // Indice du niveau actuel

    // On instancie une autre file pour stocker les noeuds du prochain niveau
    struct Queue *nextQueue = createQueue();

    while (queue->front != NULL) {
        // Taille arbitraire pour le tableau du niveau actuel
        int *currentLevel = (int *) malloc(1000 * sizeof(int));
        int count = 0; // Compteur pour les nœuds dans chaque niveau

        // Parcourt le niveau actuel jusqu'à ce que la file soit vide
        while (queue->front != NULL) {
            // Récupère le nœud en tête de file
            struct TreeNode *currNode = dequeue(queue);
            // Ajoute la valeur du nœud au tableau du niveau actuel
            currentLevel[count++] = currNode->val;

            // Ajoute les enfants du nœud au prochain niveau s'ils existent
            if (currNode->left != NULL)
                enqueue(nextQueue, currNode->left);
            if (currNode->right != NULL)
                enqueue(nextQueue, currNode->right);
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
        free(queue);
        queue = nextQueue;
        nextQueue = createQueue();
    }

    // Libère la mémoire de la file du prochain niveau
    free(nextQueue);

    // Met à jour la taille de retour
    *returnSize = levelIndex;

    // Retourne le tableau des niveaux de l'arbre binaire
    return result;
}