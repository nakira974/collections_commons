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
 * @brief Create a Set
 * @param set Set reference to create
 * @param match User match function to determine if elements are equals or not
 * @param destroy User destroy function to clean set elements on remove
 * @complexity O(1)
 */
void set_create(Set *set, int (*match)(const void *left, const void *right), void (*destroy)(void *value));

/**
 * @biref Try to insert a value in the given set
 * @param set Set to insert a value in
 * @param value Value to insert in the set
 * @return True if the value was inserted in the given Set, otherwise false
 * @complexity O(n) where n is the number of elements inside the given Set to compare with the parameter value
 */
bool set_add(Set *set, const void *value);

/**
 * @brief Remove from the set a value that match the value parameter then return a pointer to the removed value
 * @param set Set to remove a value in
 * @param value Reference to the delete value in the given set
 * @return True if the value was correctly removed, otherwise
 * @complexity O(n) where n is the number of elements inside the given Set to compare with the parameter value
 */
bool set_remove(Set *set, void **value);

/**
 * @brief Build a Set resulting of the Union of left and right, left and right MUST stay accessible before result is destroy
 * @param union_result Reference Set resulting of the union between left and right
 * @param left Left Set to compare for union operation
 * @param right Right Set to compare for union operation
 * @return true if the union succeed, otherwise false
 * @complexity O(mn) where m and n are the number of elements in each operand
 */
bool set_union(Set *union_result, const Set *left, const Set *right);

/**
 * @biref Build a Set resulting of the Intersection of left and right, left and right MUST stay accessible before result is destroy
 * @param intersection_result Reference Set resulting of the intersection between left and right
 * @param left Left Set to compare for intersection operation
 * @param right Right Set to compare for intersection operation
 * @return true if the intersection succeed, otherwise false
 * @complexity O(mn) where m and n are the number of elements in each operand
 */
bool set_intersection(Set *intersection_result, const Set *left, const Set *right);

/**
 * @brief Build a Set resulting of the Difference of left and right, left and right MUST stay accessible before difference_result is destroy
 * @param difference_result Reference Set resulting of the difference between left and right
 * @param left Left Set to compare for difference operation
 * @param right Right Set to compare for difference operation
 * @return true if the difference succeed, otherwise false
 * @complexity O(mn) where m and n are the number of elements in each operand
 */
bool set_difference(Set *difference_result, const Set *left, const Set *right);

/**
 * @brief Test if the value is in the given Set
 * @param set Set to search in
 * @param value Value to search in the set
 * @return true if the element is in the set, otherwise false
 * @complexity O(n) where n is the number of elements inside the given Set to compare with the parameter value
 */
bool set_is_member(const Set *set, const void *value);

/**
 * @brief Test if the left operand is a subset of the right operand
 * @param left Set to determine if it's a subset of right operand
 * @param right Set to be compared with left operand
 * @return true if the left Set is a subset of the right Set, otherwise false
 * @complexity O(mn) where m and n are the number of elements in each operand
 */
bool set_is_subset(const Set *left, const Set *right);

/**
 * @brief Test if left and right Set operands are equal
 * @param left Left Set reference operand
 * @param right Right Set reference operand
 * @return true if left and right are equal, otherwise false
 * @complexity O(n ^ 2 ) where n is the number of elements inside left AND right
 */
bool set_is_equal(const Set *left, const Set *right);

#ifdef __cplusplus
/**
 * @brief Inline function to get the current Set size
 * @param set Reference set to get the size
 * @return The size of the current Set
 * @complexity O(1)
 */
static inline int set_size(const Set * set){
    return list_size(set);
};

/**
 * @brief Inline function to destroy a set
 * @param set Set to destroy
 * @complexity O(n) where n is the number of elements inside the given Set to destroy
 */
static inline void set_destroy(Set *set){
    list_destroy(set);
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
 * @complexity O(n) where n is the number of elements inside the given Set to destroy
 */
#define set_destroy(set) list_destroy
#endif

#ifdef __cplusplus
}
#endif

#endif //COLLECTIONS_COMMONS_SET_H
