#include "masterpassword.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "error.h"
#include "safe_utils.h"

#include "cli.h"
#include "psw.h"

NOOPTIMIZE int set_master_password()
{
    int err_code;
    char *new_password;
    size_t new_password_buffer_size;
    size_t password_len;

    new_password = CLI_get_password(&new_password_buffer_size);
    password_len = strlen(new_password);

    if (password_len < MIN_MASTER_PASSWORD_LEN || password_len > MAX_MASTER_PASSWORD_LEN)
    {
        err_code = err_PASSWORD_DOES_NOT_MEET_REQUIREMENTS;
        goto _quit;
    }

    FILE *f_master_password;

    if (!(f_master_password = fopen(DATAPATH_MASTER_PASSWORD, "w")))
    {
        err_code = err_FAILED_TO_SET_MASTER_PASSWORD;
        goto _quit;
    }

    if (fputs(new_password, f_master_password) != EOF)
    {
        err_code = SUCCESS;
        force_log_out();
        showup_err(LOGGED_OUT);
    }
    else
    {
        err_code = err_FAILED_TO_SET_MASTER_PASSWORD;
    }

_quit:
    if (new_password_buffer_size > 0)
    {
        safe_free(new_password, new_password_buffer_size);
    }

    fclose(f_master_password);

    return err_code;
}

