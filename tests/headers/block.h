//
// Created by maxim on 2/03/2024.
//

#ifndef COLLECTIONS_COMMONS_BLOCK_H
#define COLLECTIONS_COMMONS_BLOCK_H

#include <stdbool.h>
#include "hash_utils.h"

struct Chunk {
    int data;
};

typedef struct Block {
    char id[4];
    struct Chunk *chunk;
    int type;
} Block;

int hash_block(const void *block) {
    Block *b1 = ((Block *) block);

    int id = b1->type + b1->chunk->data;
    int result = hashint(&id);
    return result;
}

bool cmp_block(const void *arg1, const void *arg2) {
    if (arg1 == nullptr || arg2 == nullptr) return false;
    Block *b1 = ((Block *) arg1);
    Block *b2 = ((Block *) arg2);
    if (cmp_int(&b1->chunk->data, &b2->chunk->data) && cmp_int(&b1->type, &b2->type)) {
        return true;
    }
    return false;
}

Block** generateBlocks(int size, int types) {
    Block** blocks = (Block**)malloc(size * sizeof(Block*));
    for (int i = 1; i <= size; i++) {
        Chunk* currentCHunk = (Chunk*)malloc(size * sizeof(Chunk));
        currentCHunk->data = i;
        blocks[i] = (Block*)malloc((types + 1) * sizeof(Block));
        for (int j = 1; j <= types; j++) {
            blocks[i][j].type = j;
            blocks[i][j].chunk =
            blocks[i][j].chunk = currentCHunk;
            sprintf(blocks[i][j].id, "b%dc%d", j+1, blocks[i][j].chunk->data);
        }
    }

    return blocks;
}

int compareBlocks(const void *key1, const void *key2) {
    Block *b1 = (Block*)key1;
    Block *b2 = (Block*)key2;
    if(b1 == NULL && b2 == NULL) return 0;
    else if(b1 == NULL && b2 != NULL) return -1;
    else if(b1 != NULL && b2 == NULL) return 1;

    if (b1->chunk->data == b2->chunk->data) {
        if (b1->type == b2->type) {
            return 0; // Les blocks sont égaux s'ils ont le même type dans le même chunk
        } else {
            return (b1->type < b2->type) ? -1 : 1; // Comparaison des types si dans le même chunk
        }
    } else {
        return -1; // Les blocks sont dans des chunks différents
    }
}

#endif //COLLECTIONS_COMMONS_BLOCK_H
