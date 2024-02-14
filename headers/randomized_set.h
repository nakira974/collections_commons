//
// Created by maxim on 14/02/2024.
//

#ifndef COLLECTIONS_UTILS_RANDOMIZED_SET_H
#define COLLECTIONS_UTILS_RANDOMIZED_SET_H

#include <malloc.h>

typedef struct {
    int* nums; // tableau pour stocker les valeurs du set
    int* locs; // tableau pour stocker les emplacements des valeurs dans le tableau nums
    int size; // taille actuelle du set
    int capacity; // capacité du tableau nums
} RandomizedSet;

// Crée et retourne une nouvelle instance de RandomizedSet
RandomizedSet* randomizedSetCreate();

// Insère la valeur "val" dans le set. Retourne vraie si l'insertion a réussi, sinon faux.
bool randomizedSetInsert(RandomizedSet* obj, int val);

// Supprime la valeur "val" du set. Retourne vraie si la suppression a réussi, sinon faux.
bool randomizedSetRemove(RandomizedSet* obj, int val);

// Retourne une valeur aléatoire du set.
int randomizedSetGetRandom(RandomizedSet* obj);

// Libère la mémoire utilisée par le set.
void randomizedSetFree(RandomizedSet* obj);

#endif //COLLECTIONS_UTILS_RANDOMIZED_SET_H