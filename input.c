#include <unistd.h> // STDIN_FILENO
#include <stdio.h> // EOF / stdin
#include <termios.h> // Change terminal settings
#include <fcntl.h> // Change STDIN settings
#include <math.h> // Cos, sin, fmod
#include "sheet9.h"
#include "vector.h"
#include "game.h" // Game object
#include "input.h"

terminal_t get_terminal() {
    terminal_t terminal;
    tcgetattr(STDIN_FILENO, &terminal); // Get terminal settings
    return terminal;
}

int get_stdin_flags() {
    return fcntl(STDIN_FILENO, F_GETFL); // Get STDIN settings
}

void set_terminal(terminal_t terminal, int stdin_flags) {
    tcsetattr(STDIN_FILENO, TCSANOW, &terminal); // Setting TCSANOW: apply changes immediately
    fcntl(STDIN_FILENO, F_SETFL, stdin_flags); // Set STDIN flags
}

void cooked_terminal(terminal_t terminal, int stdin_flags) {
    // Modify terminal flags to process chars instead of lines (not ICANON mode)
    terminal.c_lflag &= ~(ICANON); // Bitwise AND between inverted(ICANON) && c_lflag

    // Modify STDIN flags to be non blocking
    stdin_flags |= O_NONBLOCK; // Add NONBLOCK to flags using bitwise OR

    set_terminal(terminal, stdin_flags);
}

bool kb_hit(void) {
    // Get terminal settings
    terminal_t terminal = get_terminal();
    int stdin_flags = get_stdin_flags();

    // Change terminal to read one character at a time, or EOF if there is no input
    cooked_terminal(terminal, stdin_flags); // This messes up output on macos so it is re-&set between the renders

    // Check if there is a character to read
    int ch = getchar();

    // Reset terminal & stdin
    set_terminal(terminal, stdin_flags);

    // If there is a character, put it back in stdin
    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

bool ms_mov(int file_driver, int* mov) {
    // The re-/setting of the mouse driver is probably unecessary overhead as it could be done once on start & end, see kb_hit
    // Modify mouse driver to read even if no movement
    int mouse_fd_flags = fcntl(file_driver, F_GETFL);
	fcntl(file_driver, F_SETFL, mouse_fd_flags | O_NONBLOCK);

    char mouse_mov[3]; // 3 bytes: buttons, x, y
    int bytes_read = read(file_driver, mouse_mov, sizeof(mouse_mov));
    
    // Reset mouse driver
    fcntl(file_driver, F_SETFL, mouse_fd_flags);

    // If something was read, write movement to mov
    if (bytes_read > 0) {
        *mov = mouse_mov[1];
        return true;
    }
    return false;
}

// Process mouse input
void turn(game_t* game, int dist) {
    double angle = game->camera_angle - dist*CAMERA_ANGLE_INCR_MOUSE;

    if (fabs(angle) > 360) {
        angle = fmod(angle, 360);
    }
    game->camera_angle = angle;
}

// Process keyboard input
void move(game_t* game) {
    int i = KEYPRESS_PER_FRAME;
    // Process multiple keypresses per frame for responsive motion
    while (i--) {
        if(kb_hit()){ 
            char key = getchar();

            vector_t movement = game->camera;
            double camera_angle= game->camera_angle;

            switch (key) {
                case 'w':
                    movement.x += cos(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    movement.y += sin(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    break;
                case 's':
                    movement.x -= cos(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    movement.y -= sin(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    break;
                case 'a':
                    movement.x -= sin(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    movement.y += cos(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    break;
                case 'd':
                    movement.x += sin(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    movement.y -= cos(deg_to_rad(game->camera_angle)) * CAMERA_MOVE_INCR;
                    break;
                case 'q':
                    camera_angle += CAMERA_ANGLE_INCR;
                    break;
                case 'e':
                    camera_angle -= CAMERA_ANGLE_INCR;
                    break;
                case '\x1b': // Escape
                    game->exit = true;
                    break;
                default:
            }

            if (valid_position(game, movement)) {
                game->camera = movement;
            }
            
            if (fabs(camera_angle) > 360) {
                camera_angle = fmod(camera_angle, 360);
            }
            game->camera_angle = camera_angle;
        }
    }
    return;
}
