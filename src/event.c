//
// Created by maxim on 22/02/2024.
//

#include "event.h"

bool event_receive(Queue *events, const Event *event) {

    Event *new_event;
    /**Allocate memory for the new event*/
    if ((new_event = (Event *) malloc(sizeof(Event))) == NULL) {
        free(new_event);
        return false;
    }
    /** Copy and add the event into the queue*/
    memcpy(new_event, event, sizeof(Event));
    if (!queue_enqueue(events, new_event)) {
        free(new_event);
        return false;
    }


    return true;
}

bool event_process(Queue *events, int(*on_event_received)(Event *current_event)) {
    Event *current_event;
    if (queue_size(events) == 0) return false;
    else {
        if (!queue_dequeue(events, (void **) &current_event))
            return false;
        else {
            on_event_received(current_event);
            free(current_event);
        }
    }
    return true;
}