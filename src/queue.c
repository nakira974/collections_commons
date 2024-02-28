//
// Created by maxim on 21/02/2024.
//

#include "queue.h"

bool queue_enqueue(Queue *queue, const void *value) {
    // Add the element at the end of the queue
    return list_add(queue, list_last(queue), value);
}

bool queue_dequeue(Queue *queue, void *value) {
    // Remove the head element of the queue
    return list_remove(queue, NULL, value);
}

