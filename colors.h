#ifndef COLORS_H
#define COLORS_H

// Other constants
#define NUM_COLORS 8
#define MAX_CHARS_ANSI_BUFFER 20 // Max amount of chars in an ANSI sequence

// ANSI Basics
#define ANSI_RESET "0"
#define ANSI_BOLD "1"
#define ANSI_ESCAPE_START "\033["
#define ANSI_FG "38"
#define ANSI_BG "48"
#define ANSI_SEPERATOR ";"
#define ANSI_END "m"

#define ANSI_MOV_UP "\033[1A"
#define ANSI_DEL_LINE "\033[2K"

// ANSI RGB
#define ANSI_MAX_RGB "255"
#define ANSI_MIN_RGB "0"

// Traditional ANSI Foreground colours
#define ANSI_CC_FG_BLACK "30"
#define ANSI_CC_FG_RED "31"
#define ANSI_CC_FG_GREEN "32"
#define ANSI_CC_FG_YELLOW "33"
#define ANSI_CC_FG_BLUE "34"
#define ANSI_CC_FG_MAGENTA "35"
#define ANSI_CC_FG_CYAN "36"
#define ANSI_CC_FG_WHITE "37"
#define ANSI_CC_FG_BRIGHT_BLACK "90"
#define ANSI_CC_FG_BRIGHT_RED "91"
#define ANSI_CC_FG_BRIGHT_GREEN "92"
#define ANSI_CC_FG_BRIGHT_YELLOW "93"
#define ANSI_CC_FG_BRIGHT_BLUE "94"
#define ANSI_CC_FG_BRIGHT_MAGENTA "95"
#define ANSI_CC_FG_BRIGHT_CYAN "96"
#define ANSI_CC_FG_BRIGHT_WHITE "97"

// Traditional ANSI Background colors
#define ANSI_CC_BG_BLACK "40"
#define ANSI_CC_BG_RED "41"
#define ANSI_CC_BG_GREEN "42"
#define ANSI_CC_BG_YELLOW "43"
#define ANSI_CC_BG_BLUE "44"
#define ANSI_CC_BG_MAGENTA "45"
#define ANSI_CC_BG_CYAN "46"
#define ANSI_CC_BG_WHITE "47"
#define ANSI_CC_BG_BRIGHT_BLACK "100"
#define ANSI_CC_BG_BRIGHT_RED "101"
#define ANSI_CC_BG_BRIGHT_GREEN "102"
#define ANSI_CC_BG_BRIGHT_YELLOW "103"
#define ANSI_CC_BG_BRIGHT_BLUE "104"
#define ANSI_CC_BG_BRIGHT_MAGENTA "105"
#define ANSI_CC_BG_BRIGHT_CYAN "106"
#define ANSI_CC_BG_BRIGHT_WHITE "107"

/**
 * @brief ANSI_COLOR() allows to create a custom ANSI color sequence which gets applied 
 * to a character.
 * 
 * @param ansi_format_buffer is string buffer that the created ANSI color sequence gets 
 * written into to print it out afterwards.
 * @param ANSI_COLOR_CODE_FG is the ANSI color code for foreground colors.
 * @param ANSI_COLOR_CODE_BG is the ANSI color code for background colors.
 * @param char_to_color is the character that the created ANSI color sequence applies to.
 */
void ansi_color(char* ansi_format_buffer, const char* ANSI_COLOR_CODE_FG, const char* ANSI_COLOR_CODE_BG, char char_to_color);

/**
 * @brief ANSI_COLOR_RESET() simply resets the created ANSI color sequence to allow 
 * independent coloring of given characters.
 * 
 */
void ansi_color_reset();

#endif