//
// Created by maxim on 16/02/2024.
//

#ifndef COLLECTIONS_COMMONS_QUEUE_H
#define COLLECTIONS_COMMONS_QUEUE_H
#include "binary_tree.h"

// Structure de la file
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Structure d'une file pour stocker les nœuds
struct QueueNode {
    struct TreeNode* node;
    struct QueueNode* next;
};
// Fonction pour créer une nouvelle file vide
struct Queue* createQueue();

// Fonction pour ajouter un nœud à la file
void enqueue(struct Queue* queue, struct TreeNode* node);

// Fonction pour supprimer le nœud en tête de file et le renvoyer
struct TreeNode* dequeue(struct Queue* queue);
#endif //COLLECTIONS_COMMONS_QUEUE_H
