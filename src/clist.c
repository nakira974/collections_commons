//
// Created by maxim on 14/02/2024.
//

#include "randomized_set.h"


void randomized_set_create(RandomizedSet *set) {
    // Alloue de la mémoire pour le tableau de nombres avec une capacité initiale de 1000.
    set->nums = (int *) malloc(1000 * sizeof(int));
    // Initialise la taille actuelle du tableau à 0.
    set->size = 0;
    // Initialise la capacité maximale du tableau à 1000.
    set->capacity = 1000;
}

bool randomized_set_add(RandomizedSet *obj, int val) {
    for (int i = 0; i < obj->size; i++) {
        // Vérifie si l'élément existe déjà dans le tableau.
        if (obj->nums[i] == val) {
            // Si l'élément existe déjà, retourne faux.
            return false;
        }
    }

    // Vérifie si le tableau est plein.
    if (obj->size == obj->capacity) {
        // Réalloue de la mémoire pour doubler la capacité du tableau.
        obj->nums = (int *) realloc(obj->nums, (2 * obj->capacity) * sizeof(int));
        // Met à jour la capacité maximale.
        obj->capacity *= 2;
    }

    // Ajoute l'élément à la fin du tableau et met à jour la taille du tableau.
    obj->nums[obj->size++] = val;
    // Retourne vrai pour indiquer que l'insertion a réussi.
    return true;
}

bool randomized_set_remove(RandomizedSet *obj, int val) {
    for (int i = 0; i < obj->size; i++) {
        // Recherche l'élément dans le tableau.
        if (obj->nums[i] == val) {
            // Remplace l'élément par le dernier élément du tableau pour maintenir la continuité.
            obj->nums[i] = obj->nums[obj->size - 1];
            // Réduit la taille du tableau.
            obj->size--;
            // Retourne vrai pour indiquer que la suppression a réussi.
            return true;
        }
    }
    // Si l'élément n'est pas trouvé, retourne faux.
    return false;
}

int randomized_set_get_random(RandomizedSet *obj) {
    // Génère un index aléatoire dans la plage des indices valides du tableau.
    int randomIndex = rand() % obj->size;
    // Retourne l'élément correspondant à l'index aléatoire.
    return obj->nums[randomIndex];
}

void randomized_set_destroy(RandomizedSet *obj) {
    // Libère la mémoire du tableau de nombres.
    free(obj->nums);
    // Libère la mémoire de la structure RandomizedSet.
    free(obj);
}