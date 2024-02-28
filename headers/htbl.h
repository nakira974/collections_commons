//
// Created by maxim on 28/02/2024.
//

#ifndef COLLECTIONS_COMMONS_HTBL_H
#define COLLECTIONS_COMMONS_HTBL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#include <math.h>
#endif

/**
 * @brief PJW method to convert the given key into a permuted integer using consecutive XOR shifts
 * @param table_size Hash table size
 * @param key Key to hash
 * @return Generated hash table index
 * @author P.J. WEINBERGER
 * @see 'Compilers : Principles, Technics and Tools' from Alfred V. AHO
 */
int hashpjw(const void* key);

/**
 * @brief Hashes the memory address of a reference and returns it as a uint64_t value
 * @param table_size Hash table size
 * @param ref The reference whose address is to be hashed
 * @return The hashed value of the reference address
 */
int hashref(const void *ref);

/**
 * Inline assembly implementation of integer comparison.
 * @param a Pointer to the first value
 * @param b Pointer to the second value
 * @return true if two numbers are stricly equals, false otherwise
 */
bool cmp_int(const void *a, const void *b);


#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_HTBL_H
