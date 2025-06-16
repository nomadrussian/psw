#ifndef CLI_h
#define CLI_h

#include <stdbool.h>
#include <stddef.h>

#include "psw.h"

#define CLI_BUFFER_SIZE 64

void CLI_run(int authentification_data_status);
void CLI_greet();
Command CLI_get_next_command();
Command parse_command(const char *buff);

/** 
 * CLI_get_line - safely read a password from stdin.
 * Parameter size is the SIZE of the new password (not length which is size - 1).
 * Returns an allocated string.
 * DO NOT FORGET TO SAFELY CLEAR THE MEMORY TO 0 BEFORE free().
 * Compiler optimizations can "successfully" optimize out zeroing
 * if you are not careful -> hackers will be able to exploit RAM dumps.
 */
char *CLI_get_password(size_t *size);

#endif

