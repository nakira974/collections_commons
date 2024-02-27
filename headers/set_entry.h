/**
 * @file set.h
 * @brief This file contains the API for key set entries
 * @author Maxime Loukhal
 * @date 26/02/2024
 */
#ifndef COLLECTIONS_COMMONS_SET_ENTRY_H
#define COLLECTIONS_COMMONS_SET_ENTRY_H
#include "set.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data structure for a set identify by a generic key
 */
typedef struct KeySetEntry{
    void *key;
    Set set;
}KeySetEntry;

/**
 * @brief Determine if sets from elements to match are covering ALL elements, if true return the best solution
 * @param elements Elements to be covered
 * @param elements_to_match Sub sets to determine if they can cover ALL elements
 * @param matched_elements Shortest list of elements that match ALL elements
 * @return True if elements to match are covering ALL elements, false otherwise
 */
bool set_match_entries(Set *elements, Set* elements_to_match, Set * matched_elements);
#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_SET_ENTRY_H
