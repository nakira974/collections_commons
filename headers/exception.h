/**
 * @file exception.h
 * @brief This file contains the API for handling exceptions using setjmp/longjmp.
 * @author Maxime Loukhal
 * @date 21/02/2024
 */

#ifndef COLLECTIONS_COMMONS_EXCEPTION_H
#define COLLECTIONS_COMMONS_EXCEPTION_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdio>
#include <csetjmp>
#else

#include <stdio.h>
#include <setjmp.h>

#endif

/**
 * @brief Global jump buffer for exceptions
 */
jmp_buf exception_buffer;

// Macros for exception handling

/**
 * @brief Try macro block
 * @def TRY
 */
#define TRY if (setjmp(exception_buffer) == 0)
/**
 * @brief Catch macro block
 * @def CATCH
 */
#define CATCH else
/**
 * @brief Finally macro block
 * @def FINALLY
 */
#define FINALLY

/**
 * @brief Function to throw an exception
 */
void throw_exception() {
    longjmp(exception_buffer, 1);
}

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_EXCEPTION_H
