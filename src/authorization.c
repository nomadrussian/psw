#include "authorization.h"

#include "config.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "masterpassword.h"
#include "psw.h"

#include "directory.h"
#include "safe_util.h"

bool authorized = false; 
static char master_password_buff[MAX_MASTER_PASSWORD_LEN + 1] = { 0 };

// (plug) implement hash + salt checks
int check_authentification_data()
{
    int err_code;

    FILE *f_master_password;

    if (!(f_master_password = fopen(DATA_DIR "/" DATA_FILE_MASTER_HASH, "r")))
    {
        err_code = err_CORRUPTED_AUTHENTIFICATION_DATA;
    }
    else
    {
        fclose(f_master_password);
        err_code = OK;
    }

    return err_code;
}

NOOPTIMIZE int attempt_authorize()
{
    if (authorized)
    {
        return err_AUTHORIZED;
    }

    // negative error codes mean errors, non-negative - success
    int err_code;
    if ((err_code = load_authentification_data()) < 0)
    {
        return err_code;
    }

    size_t master_password_buffer_size = 0;
    char *master_password = CLI_get_password(&master_password_buffer_size);
    if (!strcmp(master_password_buff, master_password))
    {
        err_code = SUCCESS;
    }
    else
    {
        err_code = err_WRONG_MASTER_PASSWORD;
    }

    if (master_password_buffer_size > 0)
    {
        safe_free(master_password, master_password_buffer_size);
    }

    return err_code;
}

int load_authentification_data()
{
    FILE *f_master_password;
    
    if (!(f_master_password = fopen(DATA_DIR "/" DATA_FILE_MASTER_HASH, "r")))
    {
        return err_CORRUPTED_AUTHENTIFICATION_DATA;
    }

    fgets(master_password_buff, MAX_MASTER_PASSWORD_LEN, f_master_password);
    fclose(f_master_password);

    return OK;
}

NOOPTIMIZE int force_log_out()
{
    clear_master_password_buff();
    authorized = false;
    return LOGGED_OUT;
}

NOOPTIMIZE void clear_master_password_buff()
{
    safe_clear(master_password_buff, MAX_MASTER_PASSWORD_LEN + 1);
}

