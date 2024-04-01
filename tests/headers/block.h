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
    char id[2];
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

#endif //COLLECTIONS_COMMONS_BLOCK_H
