//
// Created by maxim on 20/02/2024.
//
#include "node.h"

Node *set_link(Node *parent, Node *child) {
    parent->next = child;
    return parent;
}

bool has_next(Node *current) {
    return current->next != NULL;
}