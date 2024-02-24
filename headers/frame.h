/**
 * @file sort.h
 * @brief This file contains the API for page frames management
 * @author Maxime Loukhal
 * @date 24/02/2024
 */

#ifndef COLLECTIONS_COMMONS_FRAME_H
#define COLLECTIONS_COMMONS_FRAME_H

#ifdef __cplusplus
#include <cstdlib>
#include <cstdbool>
#else
#include <stdlib.h>
#endif

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Try to allocate a frame, then returns its index
 * @param frames
 * @return The created frame's index, otherwise -1
 */
int frame_alloc(LinkedList *frames);

/**
 * Try to deallocate a frame based on its id
 * @param frames List of frames where to remove the given frame index
 * @param frame_id Frame id to remove
 * @return true if the frame was destroy, otherwise false
 */
bool frame_destroy(LinkedList *frames, int frame_id);
#ifdef __cplusplus
}
#endif
#endif //COLLECTIONS_COMMONS_FRAME_H
