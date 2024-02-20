//
// Created by maxim on 16/02/2024.
//
#include "simple_queue.h"


struct SimpleQueue *createQueue() {
    // Alloue de la mémoire pour la queue
    struct SimpleQueue *queue = (struct SimpleQueue *) malloc(sizeof(struct SimpleQueue));
    // Initialise le front de la queue à NULL
    queue->front = NULL;
    // Initialise le rear de la queue à NULL
    queue->rear = NULL;
    // Renvoie un pointeur vers la queue créée
    return queue;
}


void enqueue(struct SimpleQueue *queue, struct TreeNode *node) {
    // Alloue de la mémoire pour le nouveau noeud
    struct QueueNode *newNode =
            (struct QueueNode *) malloc(sizeof(struct QueueNode));
    // Affecte le noeud donné en argument au nouveau noeud
    newNode->node = node;
    // Initialise le prochain noeud du nouveau noeud à NULL
    newNode->next = NULL;

    // Si la queue est vide
    if (queue->rear == NULL) {
        // Définit le nouveau noeud comme étant le front et le rear de la queue
        queue->front = newNode;
        queue->rear = newNode;
        // Si la queue n'est pas vide
    } else {
        // Ajoute le nouveau noeud après le rear actuel de la queue
        queue->rear->next = newNode;
        // Met à jour le rear de la queue avec le nouveau noeud
        queue->rear = newNode;
    }
}


struct TreeNode *dequeue(struct SimpleQueue *queue) {
    // Si la queue est vide
    if (queue->front == NULL) {
        // Renvoie NULL
        return NULL;
    }

    // Récupère le noeud du front de la queue
    struct TreeNode *node = queue->front->node;
    // Stocke temporairement le front de la queue
    struct QueueNode *temp = queue->front;

    // Met à jour le front de la queue avec le prochain noeud
    queue->front = queue->front->next;
    // Si la queue devient vide après avoir retiré le front
    if (queue->front == NULL) {
        // Met à jour le rear de la queue à NULL
        queue->rear = NULL;
    }

    // Libère la mémoire du noeud retiré
    free(temp);
    // Renvoie le noeud retiré
    return node;
}