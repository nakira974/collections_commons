/**
 * @file event.h
 * @brief This file contains the API for Events in interruption scenario
 * @author Maxime Loukhal
 * @date 22/02/2024
 */

#ifndef COLLECTIONS_COMMONS_EVENT_H
#define COLLECTIONS_COMMONS_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdlib>
#include <cstring>
#else
#include <stdlib.h>
#include <string.h>
#endif

#include "queue.h"

/**
 * @brief Data structure definition of an event
 */
typedef struct Event{
    int eventType;
    void* eventData;
} Event;

/**
 * @brief A subscriber add an event into the queue for witch he subscribed
 * @param events Events queue
 * @param event Event to save into the queue
 * @return true if the event was added in events, otherwise false
 */
 bool event_receive(Queue * events, const Event *event);

 /**
  * @brief Interruption handle to process subscribed events
  * @param events Events queue
  * @param on_event_received User function to process the event
  * @return true if the event was computed, otherwise false
  */
 bool event_process(Queue *events, int(* on_event_received) (Event * event));

#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_EVENT_H
