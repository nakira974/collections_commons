/**
 * @file set.h
 * @brief This file contains the API for Set collections
 * @author Maxime Loukhal
 * @date 23/02/2024
 */
#ifndef COLLECTIONS_COMMONS_SET_H
#define COLLECTIONS_COMMONS_SET_H

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data structure definition for a generic dataset
 */
typedef LinkedList Set;

/**
 * @brief Data structure for a set identify by a generic key
 */
typedef struct KeySetEntry {
    void *key;
    Set set;
} KeySetEntry;

/**
 * @brief Determine if sets from hashtable to equals are covering ALL hashtable, if true return the best solution
 * @param elements Elements to be covered
 * @param elements_to_equals Sub sets to determine if they can cover ALL hashtable
 * @param equalsed_elements Shortest list of hashtable that equals ALL hashtable
 * @return True if hashtable to equals are covering ALL hashtable, false otherwise
 */
bool set_equals_entries(Set *elements, Set *elements_to_equals, Set *equalsed_elements);

/**
 * @brief Create a Set
 * @param set Set reference to create
 * @param equals User equals function to determine if hashtable are equals or not
 * @param destroy User destroy function to clean set hashtable on remove
 * @complexity O(1)
 */
void set_create(Set *set, bool (*equals)(const void *left, const void *right), void (*destroy)(void *value));

/**
 * @biref Try to insert a value in the given set
 * @param set Set to insert a value in
 * @param value Value to insert in the set
 * @return True if the value was inserted in the given Set, false otherwise
 * @complexity O(n) where n is the number of hashtable inside the given Set to compare with the parameter value
 */
bool set_add(Set *set, const void *value);

/**
 * @brief Remove from the set a value that equals the value parameter then return a pointer to the removed value
 * @param set Set to remove a value in
 * @param value Reference to the delete value in the given set
 * @return True if the value was correctly removed, otherwise
 * @complexity O(n) where n is the number of hashtable inside the given Set to compare with the parameter value
 */
bool set_remove(Set *set, void **value);

/**
 * @brief Build a Set resulting of the Union of left and right, left and right MUST stay accessible before result is destroy
 * @param union_result Reference Set resulting of the union between left and right
 * @param left Left Set to compare for union operation
 * @param right Right Set to compare for union operation
 * @return true if the union succeed, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool set_union(Set *union_result, const Set *left, const Set *right);

/**
 * @biref Build a Set resulting of the Intersection of left and right, left and right MUST stay accessible before result is destroy
 * @param intersection_result Reference Set resulting of the intersection between left and right
 * @param left Left Set to compare for intersection operation
 * @param right Right Set to compare for intersection operation
 * @return true if the intersection succeed, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool set_intersection(Set *intersection_result, const Set *left, const Set *right);

/**
 * @brief Build a Set resulting of the Difference of left and right, left and right MUST stay accessible before difference_result is destroy
 * @param difference_result Reference Set resulting of the difference between left and right
 * @param left Left Set to compare for difference operation
 * @param right Right Set to compare for difference operation
 * @return true if the difference succeed, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool set_difference(Set *difference_result, const Set *left, const Set *right);

/**
 * @brief Test if the value is in the given Set
 * @param set Set to search in
 * @param value Value to search in the set
 * @return true if the element is in the set, false otherwise
 * @complexity O(n) where n is the number of hashtable inside the given Set to compare with the parameter value
 */
bool set_isMember(const Set *set, const void *value);

/**
 * @brief Test if the left operand is a subset of the right operand
 * @param left Set to determine if it's a subset of right operand
 * @param right Set to be compared with left operand
 * @return true if the left Set is a subset of the right Set, false otherwise
 * @complexity O(mn) where m and n are the number of hashtable in each operand
 */
bool set_isSubset(const Set *left, const Set *right);

/**
 * @brief Test if left and right Set operands are equal
 * @param left Left Set reference operand
 * @param right Right Set reference operand
 * @return true if left and right are equal, false otherwise
 * @complexity O(n ^ 2 ) where n is the number of hashtable inside left AND right
 */
bool set_equals(const Set *left, const Set *right);

/**
 * @brief Convert the given set into a hashset
 * @param set Set to be converted to hashset
 * @return Converted set to hashset
 */
Set* set_toHashSet(Set *set, int (*hash)(const void *key));

#ifdef __cplusplus
/**
 * @brief Inline function to get the current Set size
 * @param set Reference set to get the size
 * @return The size of the current Set
 * @complexity O(1)
 */
static inline int set_size(const Set *set) {
    return list_size((LinkedList *) set);
} ;

/**
 * @brief Inline function to destroy a set
 * @param set Set to destroy
 * @complexity O(n) where n is the number of hashtable inside the given Set to destroy
 */
static inline void set_destroy(Set *set) {
    list_destroy(set);
}

/**
 * @brief Inline function that returns a random element from the set
 */
static inline LinkedElement *set_getRandom(Set *set) {
    return list_getRandom(set);
}

/**
 * @brief Inline function that evaluates the current set into an array
 * @param stack Set to be converted to array
 * @return Converted set to array
 */
static inline void** set_toArray(Set * set){
    return list_toArray(set);
}
#else
/**
 * @brief Macro that evaluates the size of a given Set
 * @param set Reference set to get the size
 * @return The size of the current Set
 * @complexity O(1)
 */
#define set_size(set) ((set)->size)

/**
 * @brief Macro that evaluates destruction of a given set
 * @param set Set to destroy
 * @complexity O(n) where n is the number of hashtable inside the given Set to destroy
 */
#define set_destroy(set) list_destroy

/**
 * @brief Macro that evaluates a random element from the set and returns it
 */
#define set_get_random(set) list_getRandom

/**
 * @brief Macro that evaluates the current set into an array
 * @param stack Set to be converted to array
 * @return Converted set to array
 */
#define set_toArray(set) list_toArray
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_SET_H
