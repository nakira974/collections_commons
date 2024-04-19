/**
 * @file hash_utils.h
 * @brief This file contains the API for basic hash functions
 * @author Maxime Loukhal
 * @date 09/03/2024
 */
#ifndef COLLECTIONS_COMMONS_HASH_UTILS_H
#define COLLECTIONS_COMMONS_HASH_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#include <cstdint>
#include <cstdbool>
#else
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#endif
/**
* @brief PJW method to convert the given key into a permuted integer using consecutive XOR shifts
* @param table_size Hash table size
* @param key Key to hash
* @return Generated hash table index
* @author P.J. WEINBERGER
* @see 'Compilers : Principles, Technics and Tools' from Alfred V. AHO
*/
int hashpjw(const void *key);

/**
 * @brief Hashes the memory address of a reference and returns it as a uint64_t value
 * @param table_size Hash table size
 * @param ref The reference whose address is to be hashed
 * @return The hashed value of the reference address
 */
int hashref(const void *ref);

/**
 * @brief Takes an input integer and returns an integer hash value.
 *
 * @param integer The input integer for which the hash value needs to be calculated.
 * @return The calculated hash value as an integer.
 * @see https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
 * @details The magic number used in the hash calculation was determined through a rigorous testing process. A special multi-threaded test program was employed, running for several hours. This program evaluated key factors such as the avalanche effect (the number of output bits that change if a single input bit is changed, which should be nearly 16 on average), independence of output bit changes (ensuring that output bits do not depend on each other), and the probability of a change in each output bit if any input bit is changed. The calculated values outperform the 32-bit finalizer used by MurmurHash and are almost as good as when using AES. Additionally, the use of the same constant twice provides a slight advantage, resulting in improved performance based on previous tests. However, it is important to note that the exact impact on performance may vary and further testing is recommended.
 */
int hashint(const void *integer);

/**
 * Inline assembly implementation of integer comparison.
 * @param a Pointer to the first value
 * @param b Pointer to the second value
 * @return true if two numbers are stricly compareTo, false otherwise
 */
int cmp_int(const void *a, const void *b);
#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_HASH_UTILS_H
