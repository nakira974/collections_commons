//
// Created by maxim on 13/02/2024.
//
// Implémentation d'une structure de données "LinkedList"
//

#ifndef DEEP_FIRST_SEARCH_LINKED_LIST_H
#define DEEP_FIRST_SEARCH_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

// Fonction pour récupérer le prochain noeud menant à x depuis le noeud courant
Node *find_next_to(Node *current, void* x);

// Fonction pour ajouter un nouvel élément à la linked list
void push(Node **head, void * value);

//Fonction qui ajoute un noeud à la fin de la liste
void push_next(Node **head, Node **next);

// Fonction pour supprimer un noeud à un index donné de la liste
void* remove_by_index(Node **head, int n);

// Fonction pour supprimer le dernier noeud la liste liée
void * pop(Node **head);


[[deprecated("Use graph.h instead.")]]
// Fonction pour réaliser le parcours en largeur d'abord (simple_bfs) dans une liste chaînée
void simple_bfs(struct Node *startNode) __attribute__ ((deprecated));


#endif //DEEP_FIRST_SEARCH_LINKED_LIST_H
