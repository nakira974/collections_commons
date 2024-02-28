//
// Created by maxim on 28/02/2024.
//
#include "htbl.h"

int cmp_int(const void *a, const void *b){
    int result;

#ifdef __x86_64__
    asm volatile (
            "xor %[result], %[result]\n\t"
            "cmp %[key1], %[key2]\n\t"
            "sete %%al\n\t"
            "movzb %%al, %[result]\n\t"
            : [result] "+r" (result)
    : [key1] "r" (*(int*)a), [key2] "r" (*(int*)b)
    : "cc", "al"
    );
#endif

#ifdef __AVR__
    asm volatile (
            "clr r24\n\t"
            "cpse %[ref], r24\n\t"
            "ldi %[hash], 1\n\t"
            "rjmp end\n\t"
            "ldi %[hash], 0\n\t"
            "end:\n\t"
            : [hash] "=r" (hash)
            : [ref] "r" (ref)
            : "r24"
    );
#endif

#ifdef __riscv
    asm volatile (
            "sub %[ref], %[ref], %[ref]\n\t"
            "bgez %[ref], greater_or_equal\n\t"
            "li %[hash], 0\n\t"
            "j end\n\t"
            "greater_or_equal:\n\t"
            "li %[hash], 1\n\t"
            "end:\n\t"
            : [hash] "=r" (hash)
            : [ref] "r" (ref)
            : "t0"
    );
#endif

#ifdef __ARM_ARCH
    asm volatile (
            "sub %[ref], %[ref], %[ref]\n\t"
            "bge %[ref], greater_or_equal\n\t"
            "mov %[hash], #0\n\t"
            "b end\n\t"
            "greater_or_equal:\n\t"
            "mov %[hash], #1\n\t"
            "end:\n\t"
            : [hash] "=r" (hash)
            : [ref] "r" (ref)
            : "cc"
    );
#endif

    return result;
}

int hashref(int table_size, const void *ref) {
    const double phi = (sqrt(5) - 1) / 2;
    intptr_t address = (intptr_t) ref;

    return (int) (table_size * (int)( (int) address * phi));
}

int hashpjw(int table_size, const void* key){
    const char * string;
    int value;

    // hash the key the bit to bit operations

    value = 0;
    string = key;

    while(*string != '\0'){
        int temp;
        value = (value<<4) + (*string);
        if(temp=(value & 0xf0000000)){
            value = value ^(temp >> 24);
            value = value ^temp;
        }
        string++;
    }

    return (int) (value % table_size);
}