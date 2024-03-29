//
// Created by maxim on 29/03/2024.
//

#include <string.h>
#include "heap.h"

/* --- Private Macros --- */

/**
 * @brief Private macro that evaluates the index of a parent node
  * @param index Index of the target node
 */
#define heap_parent(index) ((int) (((index) -1) /2))

/**
 * @brief Private macro that evaluates the index of a left child
  * @param index Index of the target node
 */
#define heap_left(index) (((index*2 )+1))

/**
 * @brief Private macro that evaluates the index of a right child
 * @param index Index of the target node
 */
#define heap_right(index) (((index*2 )+2))

void heap_create(Heap * heap, int (*compareTo) (const void*key1, const void*key2), void (*destroy) (void *key)){
    heap->size = 0;
    heap->compareTo = compareTo;
    heap->destroy = destroy;
    heap->tree = NULL;
}

void heap_destroy(Heap * heap){
    int i;
    if(heap->destroy != NULL){
        for(i = 0; i< heap_size(heap); i++){
            heap->destroy(heap->tree[i]);
        }
    }

    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
}

bool heap_add(Heap * heap, const void * key){
    void *temp;
    int i,p;
    if((temp = ((void**) realloc(heap->tree, (heap_size(heap)+1)* sizeof (void*))))==NULL) return false;
    else heap->tree = temp;

    heap->tree[heap_size(heap)] = (void*) key;
    i = heap_size(heap);
    p = heap_parent(i);

    while(i > 0 && heap->compareTo(heap->tree[p], heap->tree[i]) < 0){
        // swp content of the current node and its parent

        temp = heap->tree[p];
        heap->tree[p] = heap->tree[i];
        heap->tree[i] = temp;

        i = p;
        p = heap_parent(i);
    }

    heap->size++;

    return true;
}

bool heap_poll(Heap * heap, void **key){
    void * save, *temp;

    int i, l, r, m;

    if(heap_size(heap) ==0) return false;

    // Extract the root of the heap
    *key = heap->tree[0];

    // Adjust memory used by the heap
    save = heap->tree[heap_size(heap)-1];
    if(heap_size(heap) -1 > 0){
        if((temp = (void**) realloc(heap->tree, heap_size(heap)-1 * sizeof (void*))) == NULL) return false;
        else heap->tree = temp;

        // Adjust the size of the heap
        heap->size--;
    }else{
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return true;
    }

    heap->tree[0] = save;

    // Piling up the tree by heaping the content to the new root
    i = 0;
    l = heap_left(i);
    r = heap_right(i);

    while(true){
        // Chose the child to swap with the current node

        l = heap_left(i);
        r = heap_right(i);

        if(l < heap_size(heap) && heap->compareTo(heap->tree[l], heap->tree[i]) > 0) m = i;

        if( r < heap_size(heap) && heap->compareTo(heap->tree[r], heap->tree[m]) > 0 ) m = r;

        if(m == i) break;
        else{
            temp = heap->tree[m];
            heap->tree[m] = heap->tree[i];
            heap->tree[i] = temp;

            i = m;
        }
    }


    return true;
}
