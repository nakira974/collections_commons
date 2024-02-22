//
// Created by maxim on 22/02/2024.
//

#ifndef COLLECTIONS_COMMONS_EVENTBUS_TEST_H
#define COLLECTIONS_COMMONS_EVENTBUS_TEST_H
#include <gtest/gtest.h>
#include <thread>
#include <csignal>

#include "event_bus.h"

static EventBus *event_bus;

class EventBusTest : public ::testing::Test {
public:
protected:
void SetUp() override {
// Initialisation du EventBus
    event_bus = new EventBus;
queue_create(event_bus,free);
}

void TearDown() override {
// Destruction du EventBus
queue_destroy(event_bus);
delete event_bus;
}

static void interruptHandler(int signal) {
    // Fonction de gestion des interruptions
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Vérification que la durée de l'interruption est inférieure à 5ms
    ASSERT_LT(duration, 5);

    // Exécution du handle des events
    event_bus_subscribe(event_bus, eventHandler);
}

static void eventHandler(const Event *event) {
    // TODO: Implémenter la logique de gestion des events

    // Exemple de catégorie d'events
    if (event->eventType == 1) {
        // Traiter les events de la catégorie 1
    } else if (event->eventType == 2) {
        // Traiter les events de la catégorie 2
    }
}


static std::chrono::high_resolution_clock::time_point start;
};

// Initialisation du point de départ pour mesurer la durée des interruptions
std::chrono::high_resolution_clock::time_point EventBusTest::start;

TEST_F(EventBusTest, TestInterrupt) {
    // Capture du point de départ
    EventBusTest::start = std::chrono::high_resolution_clock::now();

    // Définition de la fonction de gestion des interruptions
    std::signal(SIGINT, interruptHandler);

    // Exécution de la logique qui génère des interruptions (à remplacer par votre scénario de test)
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Suppression de la fonction de gestion des interruptions
    std::signal(SIGINT, SIG_DFL);
}
#endif //COLLECTIONS_COMMONS_EVENTBUS_TEST_H
