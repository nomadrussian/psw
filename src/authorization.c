#include "authorization.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "error.h"

char password_buff[64] = { 0 };

int attempt_authorize()
{
    int err_code;
    if ((err_code = load_authentification_data()) < 0)
    {
        return err_code;
    }

    char *master_password = CLI_get_password();
    if (!strcmp(password_buff, master_password))
    {
        err_code = SUCCESS;
    }
    else
    {
        err_code = err_WRONG_MASTER_PASSWORD; 
    }

    free(master_password); // implement safe_free()

    return err_code;
}

int load_authentification_data()
{
    FILE *f_master_password;
    
    if (!(f_master_password = fopen("database/mp.db", "r")))
    {
        return err_NO_MASTER_PASSWORD_FOUND;
    }

    fgets(password_buff, 64, f_master_password);
    fclose(f_master_password);

    return OK;
}

