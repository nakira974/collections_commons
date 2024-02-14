//
// Created by maxim on 13/02/2024.
//

#ifndef DEEP_FIRST_SEARCH_LINKED_LIST_H
#define DEEP_FIRST_SEARCH_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure pour représenter un nœud de la linked list
typedef struct Node {
    int value;
    struct Node* next;
} Node;

//Fonction pour récupérer le prochain noeud menant à x depuis le noeud courant
Node* find_next_to(Node* current, int x);

//Create a node
Node* create_node(int value);

// Fonction pour ajouter un nouvel élément à la linked list
void push(Node** head, int value);

//Ajoute un noeud à la fin de la liste
void push_next(Node** head, Node** next);

// Fonction pour vérifier s'il y a un prochain nœud dans la liste
bool has_next(Node* current);

//Create a link from parent to child then return the parent
Node* set_link(Node* parent, Node* child);

//Fonction pour supprimer un noeud à un index donné de la liste
int remove_by_index(Node ** head, int n);

// Fonction pour supprimer le dernier noeud la liste liée
int pop(Node ** head);

// Fonction pour réaliser le parcours en largeur d'abord (simple_bfs) dans une liste chaînée
void simple_bfs(struct Node* startNode);
#endif //DEEP_FIRST_SEARCH_LINKED_LIST_H
