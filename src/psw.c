#include "psw.h"

#include <stdbool.h>
#include <stdlib.h>

#include "authorization.h"
#include "error.h"
#include "help.h"
#include "info.h"

static const Command require_authorization_cmd_list[] = {
    cmd_GET_ALL_ENTRIES,
    cmd_GET_ENTRY,
    cmd_ADD_ENTRY,
    cmd_EDIT_ENTRY,
    cmd_REMOVE_ENTRY,
    cmd_BACKUP
};

static bool authorized = false; 

int do_command(Command command)
{
    if (!authorized && requires_authorization(command))
    {
        return err_UNAUTHORIZED;
    }

    int err_code;

    switch (command)
    {
        case cmd_AUTHORIZE:
            err_code = attempt_authorize();
            authorized = (err_code == SUCCESS);
            return err_code;
        case cmd_HELP: return showup_help();
        case cmd_INFO: return showup_info();
        case cmd_QUIT: return safe_exit(0);
        default: return err_UNKNOWN_COMMAND;
    }
}

int check_authentification_data()
{
    // implement after core authentification algorithm
    return OK;
}

bool requires_authorization(Command command)
{
    for (size_t i = 0; i < sizeof(require_authorization_cmd_list); i++)
    {
        if (command == require_authorization_cmd_list[i])
        {
            return true;
        }
    }

    return false;
}

/* to implement clearing RAM by force */
int safe_exit(int exit_code)
{
    exit(exit_code);

    return err_FAILED_SAFE_EXIT;
}

