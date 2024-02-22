//
// Created by maxim on 21/02/2024.
//

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

jmp_buf exception_buffer;

#define TRY if (setjmp(exception_buffer) == 0)
#define CATCH else
#define FINALLY

void throw_exception() {
    longjmp(exception_buffer, 1);
}

#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_EXCEPTION_H
