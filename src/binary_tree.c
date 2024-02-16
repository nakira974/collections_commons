//
// Created by maxim on 16/02/2024.
//
#include "binary_tree.h"

int **levelOrder(struct TreeNode *root, int *returnSize,
                 int **returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    struct Queue *queue = createQueue();
    enqueue(queue, root);

    // Initialisation des tableaux de résultats
    int maxLevelNodes = 1000; // Soit Node.val <= 1000
    int **result = (int **) malloc(maxLevelNodes * sizeof(int *));
    *returnColumnSizes = (int *) malloc(maxLevelNodes * sizeof(int));

    int levelIndex = 0;

    // Tant qu'il y a des éléments dans la file
    while (queue->front != NULL) {
        int currentLevelSize = queue->rear - queue->front + 1;

        // Mémoriser la taille du niveau actuel
        (*returnColumnSizes)[levelIndex] = currentLevelSize;

        // Créer un tableau pour stocker les nœuds du niveau actuel
        int *currentLevelNodes = (int *) malloc(currentLevelSize * sizeof(int));

        // Parcourir les nœuds du niveau actuel et les ajouter au tableau
        for (int i = 0; i < currentLevelSize; i++) {
            struct TreeNode *currentNode = dequeue(queue);
            currentLevelNodes[i] = currentNode->val;

            // Ajouter les enfants du nœud courant à la file du niveau suivant
            if (currentNode->left != NULL) {
                enqueue(queue, currentNode->left);
            }

            if (currentNode->right != NULL) {
                enqueue(queue, currentNode->right);
            }
        }

        // Ajouter le tableau des nœuds du niveau actuel dans le résultat
        result[levelIndex] = currentLevelNodes;

        levelIndex++;
    }

    *returnSize = levelIndex;

    return result;
}