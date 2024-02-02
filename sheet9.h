#ifndef SHEET9_H
#define SHEET9_H

#include <stdio.h>
#include <stdlib.h>

// Change settings here
#define DEBUG

#define MOUSEFILE "/dev/input/mice"
extern int mouse_fd;

#ifdef DEBUG

#define OUTFILE "output.txt"
extern FILE* out_file;

/**
 * @brief Opens the output and error files.
*/
void open_files();

/**
 * @brief Closes the output and error files.
*/
void close_files();

#define PRINT(...) fprintf(out_file, __VA_ARGS__)

#else

#define PRINT(...)

#endif

#endif