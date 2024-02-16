//
// Created by maxim on 16/02/2024.
//
#include "binary_tree.h"

// Fonction pour obtenir le niveau de l'arbre binaire de manière ordonnée
int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    struct Queue* queue = createQueue();
    enqueue(queue, root);

    // Initialisation des tableaux de résultats
    int maxLevelNodes = 1000; // Soit  -1000 <= Node.val <= 1000
    int** result = (int**)malloc(maxLevelNodes * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxLevelNodes * sizeof(int));

    int levelIndex = 0;

    // On instancie une autre file pour stocker les noeuds du prochain niveau
    struct Queue* nextQueue = createQueue();

    // Tant qu'il y a des éléments dans la file
    while (queue->front != NULL) {
        int* currentLevel =
                (int*)malloc(1000 * sizeof(int)); // taille arbitraire
        int count = 0; // Compteur des nœuds dans chaque niveau

        // On compte le niveau actuel jusqu'à ce que la file soit vide
        while (queue->front != NULL) {
            struct TreeNode* currNode = dequeue(queue);
            currentLevel[count++] = currNode->val;

            // On ajoute les enfants du prochain niveau
            if (currNode->left != NULL)
                enqueue(nextQueue, currNode->left);
            if (currNode->right != NULL)
                enqueue(nextQueue, currNode->right);
        }

        // On ajuste la taille du tableau du niveau actuel avant de l'ajouter au résultat
        currentLevel = (int*)realloc(currentLevel, count * sizeof(int));
        result[levelIndex] = currentLevel;
        (*returnColumnSizes)[levelIndex++] = count;

        // On passe au prochain niveau
        free(queue);
        queue = nextQueue;
        nextQueue = createQueue();
    }

    free(nextQueue);

    *returnSize = levelIndex;

    return result;
}