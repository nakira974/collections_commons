//
// Created by maxim on 13/02/2024.
//

#include "../headers/linked_list.h"

Node* find_next_to(Node* current, int x) {
    while (current !=  NULL) {
        if (current->value == x) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Si aucun nœud avec la valeur x n'est trouvé
}


Node* create_node(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

bool has_next(Node* current) {
    return current->next != NULL;
}

void push(Node** head, int value) {
    Node* newNode = create_node(value);

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (has_next(current)) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void push_next(Node** head, Node** next){
    if (*head == NULL) {
        *head = *next;
    } else {
        Node* current = *head;
        while (has_next(current)) {
            current = current->next;
        }
        current->next = *next;
    }
}


Node* set_link(Node* parent, Node* child) {
    parent->next = child;
    return parent;
}



int remove_by_index(Node ** head, int n) {
    int i = 0;
    int retval = -1;
    Node * current = *head;
    Node * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
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
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

int pop(Node ** head) {
    int retval = -1;
    Node * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->value;
    free(*head);
    *head = next_node;

    return retval;
}

void simple_bfs(struct Node* startNode) {
    // Vérification des cas de base
    if (startNode == NULL) {
        return;
    }

    // Création d'une file d'attente pour stocker les nœuds à visiter
    struct Node* queue = startNode;
    startNode->next = NULL;

    // Parcours en largeur d'abord
    while (queue != NULL) {
        // Visiter le nœud en tête de file
        struct Node* currentNode = queue;
        printf("%d ", currentNode->value);

        // Enfiler les nœuds adjacents non visités
        struct Node* adjacentNode = currentNode->next;
        while (adjacentNode != NULL) {
            struct Node* temp = adjacentNode;
            adjacentNode = adjacentNode->next;
            temp->next = NULL;

            // Ajouter le nœud à la file d'attente
            if (queue == NULL) {
                queue = temp;
            } else {
                struct Node* tail = queue;
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
