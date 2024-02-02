#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ansi_color(char* ansi_format_buffer, const char* ANSI_COLOR_CODE_FG, const char* ANSI_COLOR_CODE_BG, char char_to_color) {
    strcpy(ansi_format_buffer, ANSI_ESCAPE_START);
    strcat(ansi_format_buffer, ANSI_COLOR_CODE_FG);
    strcat(ansi_format_buffer, ANSI_SEPERATOR);
    strcat(ansi_format_buffer, ANSI_COLOR_CODE_BG);
    strcat(ansi_format_buffer, ANSI_SEPERATOR);
    strcat(ansi_format_buffer, ANSI_BOLD);
    strcat(ansi_format_buffer, ANSI_END);

    // strncat() to specify how long the appended string is, to allow char-appending
    strncat(ansi_format_buffer, &char_to_color, 1);
}

void ansi_color_reset() {
    char* ansi_reset_buffer = malloc(sizeof(char) * MAX_CHARS_ANSI_BUFFER);
    strcpy(ansi_reset_buffer, ANSI_ESCAPE_START);
    strcat(ansi_reset_buffer, ANSI_RESET);
    strcat(ansi_reset_buffer, ANSI_END);
    printf("%s", ansi_reset_buffer);
}

