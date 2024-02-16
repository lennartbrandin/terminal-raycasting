#include <stdlib.h> // Open files
#include "sheet9.h"
#include "screen.h"
#include "game.h"
#include "raycast.h"
#include "input.h"
#include <unistd.h>

// Extern variables (Need to be defined again for some reason)
FILE* out_file;
int mouse_fd;

void open_files() {
  // Allocate extern variables
  out_file = fopen(OUTFILE, "w");
  //setvbuf(stdout, NULL, _IOFBF, 0); //  Fully buffering, because we want to flush manually

  mouse_fd = open(MOUSEFILE, O_RDONLY);
  if (mouse_fd < 0) {
    printf("Could not open mouse driver\n");
  }
}

void close_files() {
  fclose(out_file);
  close(mouse_fd);
}

int main() {
  open_files();
  PRINT("Starting game\n");

  screen_t screen;
  game_t game;

  init_screen(&screen);
  initialize_game(&game, 3, 3, 0.0, 60);
  
  /* Change screen mode */
  //screen.screen_mode = SM_ANSI_COLORS;

  while (!game.exit) {
    raycast(&game, &game.player, &screen);
    render_frame(&screen);

    int mouse_mov = 0;
    // Render only when there is input
    while (!kb_hit() && !ms_mov(mouse_fd, &mouse_mov)) {
      usleep(KEYPRESS_CHECK_INTERVAL);
    }
    turn(&game.player, mouse_mov);
    move(&game, &game.player);
  }
  
  destroy_screen(&screen);
  free_field(&game);
  PRINT("Game ended\n");
  close_files();
  return 0;
}
