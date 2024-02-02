#include <math.h>
#include "string.h"
#include "sheet9.h"
#include "raycast.h"
#include "vector.h"

void reset_ray_hits(game_t* game) {
    for (int y = 0; y < FIELD_LEN; y++) {
        for (int x = 0; x < FIELD_LEN; x++) {
            get_object(game, x, y)->hit_by_ray = false;
        }
    }
}

void raycast(game_t* game, screen_t* screen) {
    // Calculate Field of view begin & end in degree
    // The ray is casted from "left" to "right", as the screen is drawn from left to right
    double degree = game->camera_angle + game->camera_fov/2;
    double degree_incr = (double)game->camera_fov / screen->num_colums;

    // Reset hit_by_ray for every object
    reset_ray_hits(game);

    // Cast a ray for every horizontal "pixel" on the screen
    for (int i = 0; i < screen->num_colums; degree -= degree_incr) {
        double rayCos = cos(deg_to_rad(degree)) / PRECISION;
        double raySin = sin(deg_to_rad(degree)) / PRECISION;
        vector_t ray = game->camera;
        
        object_t* object;
        do {
            // Move by (1 / precision) val in direction of ray
            ray.x += rayCos;
            ray.y += raySin;
            object = get_object(game, floor(ray.x), floor(ray.y));
            object->hit_by_ray = true;
        } while (object->transparent);

        double distance = v_dist(game->camera, ray);
        
        // Rotate hypotenuse to angle of camera
        distance *= cos(deg_to_rad(degree - game->camera_angle)); // Correct fisheye effect

        construct_frame_column(screen, distance);
        i++;
    }
    PRINT("Camera: (%.2f, %.2f), Angle: %.2f\n", game->camera.x, game->camera.y, game->camera_angle);
    PRINT("Colums (%d/%d) written\n", screen->frame_col_counter, screen->num_colums);
    print_field(game);
    fflush(out_file);
}