//
// Created by maxim on 20/02/2024.
//

#ifndef COLLECTIONS_COMMONS_NODE_H
#define COLLECTIONS_COMMONS_NODE_H

#include "stdlib.h"

// Structure pour représenter un nœud de la linked list
typedef struct Node {
    // Valeur du noeud
    int value;
    // Enfant du noeud
    struct Node *next;
} Node;

// Fonction qui crée un lien entre le parent et l'enfant et renvoie le parent
Node *set_link(Node *parent, Node *child);

//Create a node
Node *create_node(int value);

// Fonction pour vérifier s'il y a un prochain nœud dans la liste
bool has_next(Node *current);
#endif //COLLECTIONS_COMMONS_NODE_H
