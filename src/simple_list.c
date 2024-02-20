//
// Created by maxim on 13/02/2024.
//

#include "../headers/simple_list.h"

Node *find_next_to(Node *current, int x) {
    // Tant qu'on peut défiler
    while (current != NULL) {
        // x est égal à noeud de même valeur le plus proche
        if (current->value == x) {
            // renvoyer le noeud en question
            return current;
        }
        // continuer à faire défiler la liste
        current = current->next;
    }
    // Si aucun nœud avec la valeur x n'est trouvé
    return NULL;
}

Node *create_node(int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}


void push(Node **head, int value) {
    Node *newNode = create_node(value);
    if (*head == NULL) {
        // Si la liste est vide, le nouveau noeud devient la tête
        *head = newNode;
    } else {
        Node *current = *head;
        // Trouver le dernier noeud de la liste
        while (has_next(current)) {
            current = current->next;
        }
        // Ajouter le nouveau noeud à la fin de la liste
        current->next = newNode;
    }
}

void push_next(Node **head, Node **next) {
    if (*head == NULL) {
        // Si la liste est vide, le nouveau noeud devient la tête
        *head = *next;
    } else {
        Node *current = *head;
        // Trouver le dernier noeud de la liste
        while (has_next(current)) {
            current = current->next;
        }
        // Ajouter le nouveau noeud à la fin de la liste
        current->next = *next;
    }
}

int remove_by_index(Node **head, int n) {
    int i = 0;
    int retval = -1;
    Node *current = *head;
    Node *temp_node = NULL;

    if (n == 0) {
        // Utilisation de la fonction pop pour supprimer la tête de liste
        return pop(head);
    }

    // Parcourir les noeuds jusqu'à l'index n-1
    for (i = 0; i < n - 1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return -1;
    }

    temp_node = current->next;
    retval = temp_node->value;
    // Saute le noeud à l'index n en réassignant les liens
    current->next = temp_node->next;
    free(temp_node);

    return retval;
}

int pop(Node **head) {
    int retval = -1;
    Node *next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->value;
    free(*head);
    // Mettre à jour la tête de liste
    *head = next_node;
    return retval;
}

void simple_bfs(struct Node *startNode) {
    // Vérification des cas de base
    if (startNode == NULL) {
        return;
    }

    // Création d'une file d'attente pour stocker les nœuds à visiter
    struct Node *queue = startNode;
    startNode->next = NULL;

    // Parcours en largeur d'abord
    while (queue != NULL) {
        // Visiter le nœud en tête de file
        struct Node *currentNode = queue;
        printf("%d ", currentNode->value);

        // Enfiler les nœuds adjacents non visités
        struct Node *adjacentNode = currentNode->next;
        while (adjacentNode != NULL) {
            struct Node *temp = adjacentNode;
            adjacentNode = adjacentNode->next;
            temp->next = NULL;

            // Ajouter le nœud à la file d'attente
            if (queue == NULL) {
                queue = temp;
            } else {
                struct Node *tail = queue;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = temp;
            }
        }

        // Passer au nœud suivant dans la file d'attente
        queue = queue->next;
    }
}