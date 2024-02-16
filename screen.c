#include "colors.h"
#include "screen.h"
#include "sheet9.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

const char* available_colors_bg[NUM_COLORS] = { ANSI_CC_BG_WHITE, ANSI_CC_BG_BRIGHT_CYAN, ANSI_CC_BG_BLUE, ANSI_CC_BG_BRIGHT_BLUE, ANSI_CC_BG_BRIGHT_MAGENTA, ANSI_CC_BG_BRIGHT_RED, ANSI_CC_BG_BRIGHT_YELLOW, ANSI_CC_BG_BRIGHT_GREEN };
const char* available_colors_fg[NUM_COLORS] = { ANSI_CC_FG_WHITE, ANSI_CC_FG_BRIGHT_CYAN, ANSI_CC_FG_BLUE, ANSI_CC_FG_BRIGHT_BLUE, ANSI_CC_FG_BRIGHT_MAGENTA, ANSI_CC_FG_BRIGHT_RED, ANSI_CC_FG_BRIGHT_YELLOW, ANSI_CC_FG_BRIGHT_GREEN };
const char available_characters[NUM_CHARACTERS] = { '~', '+', '*', 'o', 'Q', '&', '0', '#' };
const char sky_char = '`';
const char floor_char = '-';


void init_screen(screen_t* screen) {
    PRINT("[IMPORTANT] Please do not resize this terminal window from this point until you are finished!\n");
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen->w) == -1) {
        printf("Frame size could not be determined.\n");
        exit(1);
    }
    screen->num_rows = screen->w.ws_row - 1; // -1, because the bottom line is always a line scanning for input, so the framebuffer has an offset of 1
    screen->num_colums = screen->w.ws_col;
    PRINT("Determined framebuffer size: fb[%hu (rows)][%hu (columns)]\n", screen->num_rows, screen->num_colums);
    screen->framebuffer = malloc(screen->num_rows * sizeof(char*)); // ERROR CHECKING
    for (unsigned int i = 0; i < screen->num_rows; i++) {
        screen->framebuffer[i] = malloc(screen->num_colums * sizeof(char));
    }
    screen->frame_col_counter = 0;
    screen->frame_interval_ms = STD_FRAME_INTERVALL_MS;
    screen->screen_mode = SM_ASCII_CHARS;
}

void construct_frame_column(screen_t* screen, double distance) {
    int wall_height = (int) round((double) screen->num_rows / distance);
    if (wall_height > screen->num_rows) {
        wall_height = screen->num_rows;
    }

    char wall_char;
    if ((int) round(distance) < NUM_CHARACTERS) {
        wall_char = available_characters[NUM_CHARACTERS - 1 - (int)round(distance)]; // -(int) round(distance) For reverse order
    } else {
        wall_char = available_characters[0];
    }

    if (screen->frame_col_counter == screen->num_colums) {
        screen->frame_col_counter = 0;
    }

    unsigned int upper_limit = (screen->num_rows - wall_height) / 2;
    unsigned int lower_limit = (screen->num_rows + wall_height) / 2;
    for (unsigned int i = 0; i < screen->num_rows; i++) {
        if (i < upper_limit) {
            screen->framebuffer[i][screen->frame_col_counter] = sky_char;
        } else if (i > lower_limit) {
            screen->framebuffer[i][screen->frame_col_counter] = floor_char;
        } else {
            screen->framebuffer[i][screen->frame_col_counter] = wall_char;
        }
    }
    screen->frame_col_counter++;
}

void render_frame(screen_t* screen) {
    // Overwrite previous output
    for (int i = 0; i < screen->num_rows; i++) {
        printf(ANSI_MOV_UP);
    }
    // Loop through every "pixel" in the framebuffer and print them either 
    // as character or as characters with applied ANSI color code.
    for (unsigned int i = 0; i < screen->num_rows; i++) {
        for (unsigned int j = 0; j < screen->num_colums; j++) {
            if (screen->screen_mode == SM_ASCII_CHARS) {
                printf("%c", screen->framebuffer[i][j]);
            } else {
                char* render_ansi_str = malloc(sizeof(char) * MAX_CHARS_ANSI_BUFFER);
                if (screen->framebuffer[i][j] != sky_char && screen->framebuffer[i][j] != floor_char) {
                    /*
                        Determine the color depth (index in the available_colors arrays) from the position
                        that the current char in the framebuffer has.
                    */
                    // Check at which position the current char appears in the available_chars array
                    char* first_char_occurrance = strchr(available_characters, screen->framebuffer[i][j]);
                    int color_depth_index = (int)(first_char_occurrance - available_characters);
                    ansi_color(render_ansi_str, available_colors_fg[color_depth_index], available_colors_bg[color_depth_index], screen->framebuffer[i][j]);
                    printf("%s", render_ansi_str);
                    ansi_color_reset();
                } else {
                    printf("%c", screen->framebuffer[i][j]);
                }
                free(render_ansi_str);
            }
        }
        printf("\n");
    }
}

void destroy_screen(screen_t* screen) {
    // Clear terminal
    for (int i = 0; i < screen->num_rows; i++) {
        printf(ANSI_DEL_LINE);
        printf(ANSI_MOV_UP);
    }

    for (unsigned int i = 0; i < screen->num_rows; i++) {
        free(screen->framebuffer[i]);
    }
    free(screen->framebuffer);
}
