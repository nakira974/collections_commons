//
// Created by maxim on 14/02/2024.
//

#include "randomized_set.h"


RandomizedSet *randomizedSetCreate() {
    RandomizedSet *set = (RandomizedSet *) malloc(
            sizeof(RandomizedSet)); // Alloue de la mémoire pour la structure RandomizedSet.
    set->nums = (int *) malloc(
            1000 * sizeof(int)); // Alloue de la mémoire pour le tableau de nombres avec une capacité initiale de 1000.
    set->numsSize = 0; // Initialise la taille actuelle du tableau à 0.
    set->capacity = 1000; // Initialise la capacité maximale du tableau à 1000.
    return set;
}

bool randomizedSetInsert(RandomizedSet *obj, int val) {
    for (int i = 0; i < obj->numsSize; i++) {
        if (obj->nums[i] == val) { // Vérifie si l'élément existe déjà dans le tableau.
            return false; // Si l'élément existe déjà, retourne faux.
        }
    }

    if (obj->numsSize == obj->capacity) { // Vérifie si le tableau est plein.
        obj->nums = (int *) realloc(obj->nums, (2 * obj->capacity) *
                                               sizeof(int)); // Réalloue de la mémoire pour doubler la capacité du tableau.
        obj->capacity *= 2; // Met à jour la capacité maximale.
    }

    obj->nums[obj->numsSize++] = val; // Ajoute l'élément à la fin du tableau et met à jour la taille du tableau.
    return true; // Retourne vrai pour indiquer que l'insertion a réussi.
}

bool randomizedSetRemove(RandomizedSet *obj, int val) {
    for (int i = 0; i < obj->numsSize; i++) {
        if (obj->nums[i] == val) { // Recherche l'élément dans le tableau.
            obj->nums[i] = obj->nums[obj->numsSize -
                                     1]; // Remplace l'élément par le dernier élément du tableau pour maintenir la continuité.
            obj->numsSize--; // Réduit la taille du tableau.
            return true; // Retourne vrai pour indiquer que la suppression a réussi.
        }
    }
    return false; // Si l'élément n'est pas trouvé, retourne faux.
}

int randomizedSetGetRandom(RandomizedSet *obj) {
    int randomIndex = rand() % obj->numsSize; // Génère un index aléatoire dans la plage des indices valides du tableau.
    return obj->nums[randomIndex]; // Retourne l'élément correspondant à l'index aléatoire.
}

void randomizedSetFree(RandomizedSet *obj) {
    free(obj->nums); // Libère la mémoire du tableau de nombres.
    free(obj); // Libère la mémoire de la structure RandomizedSet.
}