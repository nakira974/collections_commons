//
// Created by maxim on 5/03/2024.
//
#include "ohtbl.h"
static char vacant;

bool ohtbl_create(OAHashTable *hashTable, int postions,
                  int (*h1)(const void *key),
                  int (*h2) (const void *key),
                  int (*equals)(const void *key1, const void *key2),
                  void (*destroy)(void *value)){
    int i;
    if((hashTable->hashtable = (void**) malloc(postions * sizeof (void*))) == NULL) return false;

    hashTable->positions = postions;
    for(i =0; i< hashTable->positions;i++) hashTable->hashtable[i] = NULL;
    hashTable->vacant = &vacant;

    hashTable->h1 = h1;
    hashTable->h2 = h2;
    hashTable->equals = equals;
    hashTable->destroy = destroy;
    hashTable->size = 0;

    return true;

}

void ohtbl_destroy(OAHashTable *hashTable){
    int i;
    if(hashTable->destroy != NULL){
        for(i=0; i< hashTable->positions; i++){
            if(hashTable->hashtable[i] != NULL && hashTable->hashtable[i] != hashTable->vacant)
                hashTable->destroy(hashTable->hashtable[i]);
        }
    }

    free(hashTable->hashtable);
    memset(hashTable, 0, sizeof (OAHashTable));
}

bool ohtbl_add(OAHashTable *hashTable, const void *value){
    void *temp;
    int position, i;

    if(hashTable->size == hashTable->positions) return false;

    temp = (void*)value;
    if(ohtbl_contains(hashTable, &temp)) return false;

    // Double hashing for hash key

    for(i=0;i<hashTable->positions;i++){
        position = (hashTable->h1(value) + (i * hashTable->h2(value))) % hashTable->positions;

        if(hashTable->hashtable[position] == NULL || hashTable->hashtable[position] == hashTable->vacant){
            // Insert the value inside the hash table
            hashTable->hashtable[position] = (void*)value;
            hashTable->size++;
            return true;
        }
    }

    return false;
}

bool ohtbl_remove(OAHashTable * hashTable, void **value){
    int position, i;
    for(i = 0; i< hashTable->positions;i++){
        position = (hashTable->h1(*value) + (i * hashTable->h2(*value))) % hashTable->positions;
        // If not value has matched
        if(hashTable->hashtable[position] == NULL) return false;

        else if(hashTable->hashtable[position] == hashTable->vacant) continue;
        else if(hashTable->equals(hashTable->hashtable[position], *value)){
            // Return the deleted value
            *value = hashTable->hashtable[position];
            hashTable->hashtable[position] = hashTable->vacant;
            hashTable->size--;
            return true;
        }
    }

    return false;
}

bool ohtbl_contains(OAHashTable * hashTable, void **value){
    int position, i;

    // Double hashing the key

    for(i = 0; i < hashTable->positions;i++){
        position = (hashTable->h1(*value) + (i * hashTable->h2(*value))) % hashTable->positions;

        // If no value is present at this position return false
        if(hashTable->hashtable[position] == NULL) return false;
        else if(hashTable->equals(hashTable->hashtable[position], *value)){
            // Return the deleted value
            *value = hashTable->hashtable[position];
            return true;
        }
    }
    return false;
}