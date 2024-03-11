//
// Created by maxim on 8/03/2024.
//

#include "deque.h"

bool deque_enqueue(Deque *queue, const void *value) {
    // Add the element at the top of the queue
    return dlist_add(queue, dlist_first(queue), value);
}

bool deque_dequeue(Deque *queue, void *value) {
    // Remove the tail element of the queue
    return dlist_remove(queue, dlist_last(queue), value);
}
