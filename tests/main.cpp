//
// Created by maxim on 21/02/2024.
//

#include <gtest/gtest.h>
#include "Stack_Test.h"
#include "LinkedList_Test.h"
#include "DLinkedList_Test.h"
#include "Queue_Test.h"
#include "EventBus_Test.h"
#include "Exception_Test.h"
#include "LinkedHashTable_Test.h"
#include "HashMap_Test.h"
#include "Set_Test.h"
#include "HashSet_Test.h"
#include "OAHashTable_Test.h"
#include "Deque_Test.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}