#ifndef RAYCAST_H
#define RAYCAST_H

#include "game.h"
#include "screen.h"

#define PRECISION 64 // Precision of distance (Smoother walls)

/**
 * Reset hit_by_ray for every object
 * @param game Pointer to game data
*/
void reset_ray_hits(game_t* game);

/**
 * Cast rays over fov calculate distance to wall and draw columns
 * @param game Pointer to game data
 * @param screen Pointer to screen data
*/
void raycast(game_t* game, screen_t* screen);

#endif