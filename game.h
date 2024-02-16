#ifndef FIELD_H
#define FIELD_H

#include <stdbool.h>
#include "vector.h"

#define FIELD_LEN 24
#define MAX_CHAR 64
#define WALL_CHAR '1'
#define EMPTY_CHAR ' '
#define PLAYER_CHAR 'P'
#define MIN_DIST 0 // Minimum distance to wall

typedef struct{
    char display; // Displayed character
    bool transparent; // Can rays pass through?
    bool traversable; // Can entities walk through?
    bool hit_by_ray; // Reset every raycast, used to color fov in print_field (minimap)
} object_t; // Type of object at field pos

typedef struct{
    object_t properties;
    vector_t pos;
    double angle; // Global orientated angle (Unit circle like)
    int fov; // FoV in degree
} entity_t;

typedef struct{
    object_t** field;
    entity_t player;
    bool exit; // Exit game in main loop
} game_t;


/**
 * check if coordinates are out of bounds
 * @return true, unless out of bounds
*/
bool valid_coordinates(int x, int y);

/**
 * Check if position is too close to wall
 * @param game Pointer to game data
 * @param pos position
*/
bool valid_position(game_t* game, vector_t pos);


/**
 * Allocate memory for the field,
 * initialize its elements to empty objects or walls
 * @param game Pointer to game data
*/
void initialize_field(game_t* game);

/**
 * Create game data and initialize field
 * @param game Pointer to game data
 * @param x Horizontal coordinate of player
 * @param y Vertical coordinate of player
 * @param angle Angle of player camera in degree
 * @param fov Field of view in degree
*/
void initialize_game(game_t* game, int x, int y, double angle, int fov);

/**
 * Free allocated memory by field
 * @param game Pointer to game data
*/
void free_field(game_t* game);

/**
 * get object of each field and print it like a 2D array, color stuff in FoV
 * @param game Pointer to game data
*/
void print_field(game_t* game);


/**
 * get object memory location of coordinates
 * @param game Pointer to game data
 * @param x Horizontal coordinate
 * @param y Vertical coordinate
 * @return Pointer to object_t unless invalid coordinates
*/
object_t* get_object(game_t* game, int x, int y);

/**
 * set object memory location of coordinates
 * @param game Pointer to game data
 * @param x Horizontal coordinate
 * @param y Vertical coordinate
 * @param object Data to write to field
 * @return Pointer to object_t unless invalid coordinates
*/
void set_object(game_t*, int x, int y, object_t* object);

#endif