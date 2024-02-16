#include <stdlib.h>
#include <math.h>
#include "sheet9.h"
#include "game.h"
#include "colors.h"

// Piet wants a hardcoded field to modify
// This is copied into the field array, we could work directly on this, but i want to keep my malloc
char map_template[FIELD_LEN][FIELD_LEN] = {
    { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', 'W', 'W', 'W', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', 'W' },
    { 'W', '0', '0', 'W', '0', 'W', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', 'W', '0', 'W', '0', '0', '0', 'W' },
    { 'W', '0', '0', 'W', '0', 'W', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', 'W', 'W', 'W', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', 'W', '0', 'W', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', 'W', 'W', 'W', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'W' },
    { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
};

bool valid_coordinates(int x, int y) {
    // PRINT("Checking coordinates: (%d/%d)\n", x, y); // Massive amount of output
    if (x < FIELD_LEN && y < FIELD_LEN && x >= 0 && y >= 0) {
        return true;
    } else {
        PRINT("Tried to access field out of bounds: (%d/%d)\n", x, y);
        return false;
    }
}

bool valid_position(game_t* game, vector_t pos) {
    // Check if pos is too close to any wall
    for (int y = pos.y - MIN_DIST; y <= pos.y + MIN_DIST; y++) {
        for (int x = pos.x - MIN_DIST; x <= pos.x + MIN_DIST; x++) {
            if (!valid_coordinates(x, y)) {
                return false;
            }
            object_t* object = get_object(game, x, y);
            if (!object->transparent) {
                return false;
            }
        }
    }
    return true;
}

void initialize_field(game_t* game) {
    // "Array" of pointers to objects
    PRINT("Initializing field\n");
    game->field = malloc(sizeof(object_t*) * pow(FIELD_LEN, 2));

    for (int y = FIELD_LEN - 1; y >= 0; y--) {
        for (int x = 0; x < FIELD_LEN; x++) {
            object_t* object = malloc(sizeof(object_t));
            
            // If on the edge or true in template make object to wall
            if (map_template[y][x] == 'W' || x == 0 || x == FIELD_LEN-1 || y == 0 || y == FIELD_LEN-1) {
                object->display = WALL_CHAR;
                object->transparent = false;
            } else {
                object->display = EMPTY_CHAR;
                object->transparent = true;
            }
            set_object(game, x, y, object);
        }
    }
    PRINT("Initialized field\n");
}

void initialize_game(game_t* game, int x, int y, double angle, int fov) {
    PRINT("Initializing game\n");
    entity_t player;
    player.pos = (vector_t){x, y};
    player.angle = angle;
    player.fov = fov;
    player.properties.display = PLAYER_CHAR;
    player.properties.transparent = false;
    player.properties.traversable = false;

    game->player = player;
    game->exit = false;
    initialize_field(game);
}

void free_field(game_t* game) {
    PRINT("Freeing field\n");
    for (int i = 0; i < pow(FIELD_LEN, 2); i++) {
            free(game->field[i]);
    }
    free(game->field);
}

void print_field(game_t* game) {
    PRINT("Printing field\n");
    // Display Player on field for time of print
    vector_t* pos = &game->player.pos;
    object_t* original = get_object(game, pos->x, pos->y);
    set_object(game, pos->x, pos->y, &game->player.properties);

    for (int y = FIELD_LEN - 1; y >= 0; y--) {
        for (int x = 0; x < FIELD_LEN; x++) {
            object_t* object = get_object(game, x, y);
            if (object->hit_by_ray) {
                PRINT("\033[31m%c\033[0m ", object->display);
            } else {
                PRINT("%c ", object->display);
            }
        }
        PRINT("\n");
    }

    // Reset object where player was
    set_object(game, pos->x, pos->y, original);
}

object_t* get_object(game_t* game, int x, int y) {
    if (valid_coordinates(x, y)) {
        return game->field[y*FIELD_LEN + x];
    }
    return NULL; // Valid coordinates exits, this suppresses a warning
}

void set_object(game_t* game, int x, int y, object_t* object) {
    if (valid_coordinates(x, y)) {
        (game->field[y*FIELD_LEN + x]) = object;
    }
    return;
}
