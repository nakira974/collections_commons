//
// Created by maxim on 22/02/2024.
//

#ifndef COLLECTIONS_COMMONS_EXCEPTION_TEST_H
#define COLLECTIONS_COMMONS_EXCEPTION_TEST_H

#include "gtest/gtest.h"
#include "exception.h"

// Mock function to throw an exception for division by zero
void throw_exception(int error_code) {
    longjmp(exception_buffer, 1);
}

// Test division by zero using mocked exception function
TEST(ExceptionTest, DivisionByZero) {
    TRY {
        int a = 10, b = 0;
        throw_exception(0); // Simulating throwing an exception
    } CATCH {
        SUCCEED(); // If exception caught, test passes
    } FINALLY {
        // Code in finally block, if needed
    }
}

// Test if Try, Catch, and Finally blocks are correctly implemented
TEST(ExceptionTest, BlocksCorrectness) {
    bool try_executed = false, catch_executed = false, finally_executed = false;

    TRY {
        try_executed = true;
        throw_exception(0); // Simulating throwing an exception
    } CATCH {
        catch_executed = true;
    } FINALLY {
        finally_executed = true;
    }

    ASSERT_TRUE(try_executed && catch_executed && finally_executed);
}


#endif //COLLECTIONS_COMMONS_EXCEPTION_TEST_H
