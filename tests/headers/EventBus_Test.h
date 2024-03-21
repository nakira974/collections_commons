//
// Created by maxim on 22/02/2024.
//

#ifndef COLLECTIONS_COMMONS_EVENTBUS_TEST_H
#define COLLECTIONS_COMMONS_EVENTBUS_TEST_H

#include <gtest/gtest.h>
#include <csignal>
#include <thread>
#include "event.h"
#include <gtest/gtest.h>

class EventBusTest : public ::testing::Test {
public:
    static Queue *events;
protected:
    void SetUp() override {
        EventBusTest::events = (Queue *) malloc(sizeof(Queue));
        if (EventBusTest::events)
            queue_create(EventBusTest::events, free);
    }

    void TearDown() override {

        free(EventBusTest::events);
    }

    static Event create_event(int type, void *data) {
        Event e;
        e.eventType = type;
        e.eventData = data;
        return e;
    }

    static int process_event(Event *event) {
        return event->eventType;
    }

    static void event_handler(const Event *event) {
        ASSERT_EQ(event->eventType, 1);
    }

    static void interruption_handler(int signum) {
        Event e = create_event(signum, nullptr);
        event_receive(EventBusTest::events, &e);
    }
};

Queue *EventBusTest::events;

TEST_F(EventBusTest, TestEventProcess) {
    Event e1 = create_event(1, nullptr);
    event_receive(events, &e1);

    int result = event_process(events, process_event);
    ASSERT_EQ(result, true);
}

TEST_F(EventBusTest, TestInterrupt) {
    // Enregistrement du gestionnaire d'interruption_handler
    signal(SIGINT, interruption_handler);

    // Lever une interruption_handler SIGINT
    raise(SIGINT);

    // Traitement de l'événement - doit être SIGINT
    int result = event_process(events, process_event);
    ASSERT_EQ(result, true);
}

#endif //COLLECTIONS_COMMONS_EVENTBUS_TEST_H