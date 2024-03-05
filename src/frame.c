//
// Created by maxim on 24/02/2024.
//

#include "frame.h"

int frame_alloc(LinkedList *frames) {
    int frame_id, *value;
    // If no frame available
    if (list_size(frames) == 0) return -1;
    else {
        // If we can't obtain a frame
        if (!list_remove(frames, NULL, (void **) &value)) return -1;
        else {
            frame_id = *value;
            free(value);
        }
    }

    return frame_id;
}

bool frame_destroy(LinkedList *frames, int frame_id) {
    int *value;

    // Allocate memory space for the frame id
    if ((value = (int *) malloc(sizeof(int))) == NULL) {
        free(value);
        return false;
    }
    // Replacing the current frame in the available pages
    *value = frame_id;
    if (!list_add(frames, NULL, value)) return false;

    return true;
}