//
// Created by maxim on 16/02/2024.
//
// Implémentation d'une structure de données "Queue"
//

#ifndef COLLECTIONS_COMMONS_QUEUE_H
#define COLLECTIONS_COMMONS_QUEUE_H
#include "binary_tree.h"

// Structure de la file
struct Queue {
    struct QueueNode* front; // Premier élement
    struct QueueNode* rear; // Dernier élément
};

// Structure d'une file pour stocker les nœuds
struct QueueNode {
    struct TreeNode* node; // Valeur courante
    struct QueueNode* next; // Prochain élement
};

// Fonction qui crée une queue vide et renvoie un pointeur vers cette queue
struct Queue* createQueue();

// Fonction pour ajouter un nœud à la file
void enqueue(struct Queue* queue, struct TreeNode* node);

// Fonction pour supprimer le nœud en tête de file et le renvoyer
struct TreeNode* dequeue(struct Queue* queue);
#endif //COLLECTIONS_COMMONS_QUEUE_H
