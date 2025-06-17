#include "masterpassword.h"

#include "config.h"
#include "error.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "psw.h"

#include "directory.h"
#include "safe_util.h"

NOOPTIMIZE int set_master_password()
{
    int err_code;

    err_code = dir_is_available(DATA_DIR "/");

    
    if (err_code == err_DIR_DOES_NOT_EXIST)
    {
        err_code = dir_create(DATA_DIR "/");

        if (err_code < 0)
        {
            return err_code;
        }
    }
    else if (err_code < 0)
    {
        return err_code; 
    }

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

    if (!(f_master_password = fopen(DATA_DIR "/" DATA_FILE_MASTER_HASH, "w")))
    {
        err_code = err_FAILED_TO_SET_MASTER_PASSWORD;
        goto _quit;
    }

    if (fputs(new_password, f_master_password) != EOF)
    {
        err_code = SUCCESS;
    }
    else
    {
        err_code = err_FAILED_TO_SET_MASTER_PASSWORD;
    }

    fclose(f_master_password);

_quit:
    if (new_password_buffer_size > 0)
    {
        safe_free(new_password, new_password_buffer_size);
    }

    return err_code;
}

