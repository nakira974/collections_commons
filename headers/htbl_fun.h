/**
 * @file htbl_fun.h
 * @brief This file contains the API for basic hash table functions
 * @author Maxime Loukhal
 * @date 28/02/2024
 */


#ifndef COLLECTIONS_COMMONS_HTBL_FUNC_H
#define COLLECTIONS_COMMONS_HTBL_FUNC_H

/**
 * @brief Convert the given key into a permuted integer using consecutive XOR shifts
 * @param key Key to hash
 * @return Generated hash table index
 * @author P.J. WEINBERGER
 * @see 'Compilers : Principles, Technics and Tools' from Alfred V. AHO
 */
int hashpjw(const void* key);
#endif //COLLECTIONS_COMMONS_HTBL_FUNC_H
