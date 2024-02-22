/**
 * @file event_bus.h
 * @brief This file contains the API for EventBus queues in an interruption scenario
 * @author Maxime Loukhal
 * @date 22/02/2024
 */
#ifndef COLLECTIONS_COMMONS_EVENT_BUS_H
#define COLLECTIONS_COMMONS_EVENT_BUS_H

#ifdef __cplusplus
#include <cstdbool>
#else
#include <stdbool.h>
#endif

#include "event.h"



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def EVENT_BUS_CAPACITY
 * @brief The maximum capacity of the event bus.
 */
#define EVENT_BUS_CAPACITY 128

/**
 * @brief Type definition for EventBus as a Queue.
 */
typedef Queue EventBus;

#ifdef __cplusplus

/**
* @brief Publishes an event to the event bus.
* @param event_bus The event bus to which the event is published.
* @param event The event to be published.
*/
static inline void event_bus_publish(EventBus *event_bus, const Event *event) {
    if (event_bus->size < EVENT_BUS_CAPACITY) {
        queue_enqueue(event_bus, (const void *) event);
    }
}

/**
 * @brief Subscribes an event handler to the event bus.
 * @param event_bus The event bus to which the event handler is subscribed.
 * @param event_handler The function pointer to the event handler.
 */
static inline void event_bus_subscribe(EventBus *event_bus, void (*event_handler)(const Event *)) {
    LinkedElement *current = list_first(event_bus);
    while (current != nullptr) {
        event_handler((const Event *) list_value(current));
        current = list_next(current);
    }
}

#else
/**
 * @brief Publishes an event to the event bus.
 */
#define event_bus_publish(event_bus, event) \
    do { \
        if ((event_bus)->size < EVENT_BUS_CAPACITY) { \
            queue_enqueue(event_bus, NULL, (const void *) (event)); \
        } \
    } while (0)

/**
 * @brief Subscribes an event handler to the event bus.
 */
#define event_bus_subscribe(event_bus, event_handler) \
    do { \
        LinkedElement *current = list_first(event_bus); \
        while (current != NULL) { \
            event_handler((const Event *) list_value(current)); \
            current = list_next(current); \
        } \
    } while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif // COLLECTIONS_COMMONS_EVENT_BUS_H