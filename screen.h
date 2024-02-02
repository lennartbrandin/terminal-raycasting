#ifndef SCREEN_H
#define SCREEN_H

#include "colors.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Get control over IO to get terminal window size depending on the OS
// #ifdef _WIN32
//     #include <windows.h> // Should get screensize and sleep in ms
// #elif __MACH__
#include <sys/ioctl.h>
#include <unistd.h>

// Constants
#define NUM_CHARACTERS 8
#define STD_FRAME_INTERVALL_MS 25000

/**
 * @brief Available screen modes:
 * ASCII_CHARS: Rendering walls as regular ASCII characters
 * ANSI_COLORS: Rendering walls as regular ASCII characters, 
 * overlayed by traditional ANSI-background- and foreground colors
 * 
 */
enum SCREEN_MODE {
    SM_ASCII_CHARS,
    SM_ANSI_COLORS
};

/**
 * @brief Screen is a struct that needs to be initialized before working 
 * with any of the functions below.
 * 
 */
typedef struct {
    struct winsize w;
    unsigned short num_rows;
    unsigned short num_colums;
    char **framebuffer;
    unsigned int frame_col_counter;
    useconds_t frame_interval_ms;
    enum SCREEN_MODE screen_mode;
} screen_t;

/**
 * @brief init_screen() initializes an before declared screen structure
 * with standard values and settings.
 * 
 * @param screen is a pointer to a declared screen structure
 */
void init_screen(screen_t* screen);

/**
 * @brief construct_frame_column() uses @param distance to calculate the wall 
 * height from the players position and then calculate which character should 
 * be rendered accordingly.
 * 
 * @param screen is a pointer to an already initialized screen structure
 * @param distance is a value that represents the distance from the player to a wall
 */
void construct_frame_column(screen_t* screen, double distance);

/**
 * @brief render_frame() renders/outputs the current framebuffer to the 
 * virtual screen (terminal).
 * 
 * @param screen is a pointer to an already initialized screen structure
 */
void render_frame(screen_t* screen);

/**
 * @brief destroy_screen() frees the allocated memory for the framebuffer and must be 
 * called when the screen structure gets out of use to prevent memory leaks.
 * 
 * @param screen is a pointer to an already initialized screen structure
 */
void destroy_screen(screen_t* screen);

#endif