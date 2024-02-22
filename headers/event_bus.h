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

#define EVENT_BUS_CAPACITY 100


typedef LinkedList EventBus;

#ifdef __cplusplus
static inline void event_bus_publish(EventBus *event_bus, const Event *event) {
    if (event_bus->size < EVENT_BUS_CAPACITY) {
        queue_enqueue(event_bus, (const void *) event);
    }
}

static inline void event_bus_subscribe(EventBus *event_bus, void (*event_handler)(const Event *)) {
    LinkedElement *current = list_first(event_bus);
    while (current != nullptr) {
        event_handler((const Event *) list_value(current));
        current = list_next(current);
    }
}
#else
#define event_bus_publish(event_bus, event) \
    do { \
        if ((event_bus)->size < EVENT_BUS_CAPACITY) { \
            queue_enqueue(event_bus, NULL, (const void *) (event)); \
        } \
    } while (0)

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