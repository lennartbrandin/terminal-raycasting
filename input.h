#include "game.h"
#include "termios.h"
#include "fcntl.h"

#define CAMERA_ANGLE_INCR 2.5
#define CAMERA_ANGLE_INCR_MOUSE 0.25
#define CAMERA_MOVE_INCR 0.1
#define KEYPRESS_PER_FRAME 100 // Keypress to process per frame
#define KEYPRESS_CHECK_INTERVAL 10000 // Check for keypress every x microseconds

typedef struct termios terminal_t;

/**
 * @return terminal data
*/
terminal_t get_terminal(void);

/**
 * @return stdin flags
*/
int get_stdin_flags(void);

/**
 * Set terminal & stdin flags
 * @param terminal Terminal data
 * @param stdin_flags Stdin flags
*/
void set_terminal(terminal_t terminal, int stdin_flags);

/**
 * Modify terminal to read one character at a time
 * Modify stdin to non-blocking
 * @param terminal Pointer to terminal data
 * @param stdin_flags Stdin flags
*/
void cooked_terminal(terminal_t terminal, int stdin_flags);


/**
 * Checks if a key has been pressed.
 * @return true if a key has been pressed, false otherwise.
*/
bool kb_hit(void);

/**
 * Check for mouse movement, if detected write to mov
 * @param file_driver File driver for mouse
 * @return true if mouse movement detected, false otherwise
*/
bool ms_mov(int file_driver, int* mov);

/**
 * Turn camera
 * @param game Pointer to game data
 * @param dist Distance to turn
*/
void turn(game_t *game, int dist);

/**
 * Move camera based on buffered keypresses
 * @param game Pointer to game data
*/
void move(game_t *game);