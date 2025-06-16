#include "authorization.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "error.h"
#include "safe_utils.h"

#include "cli.h"
#include "masterpassword.h"
#include "psw.h"

static char master_password_buff[MAX_MASTER_PASSWORD_LEN + 1] = { 0 };

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
    
    if (!(f_master_password = fopen(DATAPATH_MASTER_PASSWORD, "r")))
    {
        return err_CORRUPTED_AUTHENTIFICATION_DATA;
    }

    fgets(master_password_buff, MAX_MASTER_PASSWORD_LEN, f_master_password);
    fclose(f_master_password);

    return OK;
}

NOOPTIMIZE void clear_master_password_buff()
{
    safe_clear(master_password_buff, MAX_MASTER_PASSWORD_LEN + 1);
}

