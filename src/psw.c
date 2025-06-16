#include "psw.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "error.h"
#include "safe_utils.h"

#include "authorization.h"
#include "help.h"
#include "info.h"
#include "masterpassword.h"

static const Command require_authorization_cmd_list[] = {
    cmd_UNAUTHORIZE,
    cmd_GET_ALL_ENTRIES,
    cmd_GET_ENTRY,
    cmd_ADD_ENTRY,
    cmd_EDIT_ENTRY,
    cmd_REMOVE_ENTRY,
    cmd_BACKUP
};

bool authorized = false; 

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
            authorized = (err_code == SUCCESS || err_code == err_AUTHORIZED);
            return err_code;
        case cmd_UNAUTHORIZE: return force_log_out();
        case cmd_SET_MASTER_PASSWORD: return set_master_password();
        case cmd_HELP: return showup_help();
        case cmd_INFO: return showup_info();
        case cmd_QUIT: return safe_exit(0);
        default: return err_UNKNOWN_COMMAND;
    }
}

// (plug) implement hash + salt checks
int check_authentification_data()
{
    FILE *f_master_password;
    int err_code = OK;

    if (!(f_master_password = fopen(DATAPATH_MASTER_PASSWORD, "r")))
    {
        err_code = err_CORRUPTED_AUTHENTIFICATION_DATA;
    }

    return err_code;
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

NOOPTIMIZE int force_log_out()
{
    clear_master_password_buff();
    authorized = false;
    return LOGGED_OUT;
}

