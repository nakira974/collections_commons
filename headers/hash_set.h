/**
 * @file set.h
 * @brief This file contains the API for generic Set covering
 * @author Maxime Loukhal
 * @date 23/02/2024
 */
#ifndef COLLECTIONS_COMMONS_HASH_SET_H
#define COLLECTIONS_COMMONS_HASH_SET_H
#include "set.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data structure for a set identify by a generic key
 */
typedef struct HashSet{
    void *key;
    Set set;
}HashSet;

/**
 * @brief Determine of elements to match are covering ALL elements
 * @param elements Elements to be covered
 * @param elements_to_match Sub sets to determine if they can cover ALL elements
 * @param matched_elements Shortest list of elements that match ALL elements
 * @return True if elements to match are covering ALL elements, false otherwise
 */
bool set_match_exact(Set *elements, Set* elements_to_match, Set * matched_elements);
#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_HASH_SET_H
