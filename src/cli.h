#ifndef CLI_h
#define CLI_h

#include "psw.h"

#include <stdbool.h>

void CLI_run();
void CLI_greet();
Command CLI_get_next_command();
Command parse_command(const char *buff);

/** 
 * CLI_get_line - safely read a line from stdin.
 * Returns an allocated C string.
 * DO NOT FORGET TO SAFELY CLEAR THE MEMORY TO 0 BEFORE free().
 * Compiler optimizations can skip zeroing if you are not careful.
 */
char *CLI_get_password();

#endif

