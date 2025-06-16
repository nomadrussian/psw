#ifndef PSW_H
#define PSW_H

#include <stdbool.h>

#include "error.h"

typedef enum {
    cmd_GET_ALL_ENTRIES, // priority: ESSENTIAL
    cmd_GET_ENTRY, // priority: middle
    cmd_ADD_ENTRY, // priority: ESSENTIAL
    cmd_EDIT_ENTRY, // priority: middle
    cmd_REMOVE_ENTRY, // priority: ESSENTIAL
    cmd_BACKUP, // priority: middle
    cmd_AUTHORIZE, // priority: ESSENTIAL
    cmd_SET_MASTER_PASSWORD, // priority: ESSENTIAL
    cmd_GENERATE_PASSWORD, // priority: 0 just so it does something useful + safe rand
    cmd_CHECK_PASSWORD_SAFETY, // priority: last
    cmd_GENERATE_HASH, // priority: last
    cmd_HELP, // priority: very last
    cmd_INFO, // priority: very last
    cmd_QUIT, // priority: SAFETY
    cmd_UNKNOWN_COMMAND
} Command;

int do_command(Command command);
int check_authentification_data();
bool requires_authorization(Command command);
int safe_exit(int exit_code);

#endif

