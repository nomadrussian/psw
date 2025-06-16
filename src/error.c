#include "error.h"

#include <stdio.h>

const Error ErrorMap[] = {
    { LOGGED_OUT, msg_LOGGED_OUT },
    { SUCCESS, msg_SUCCESS },
    { OK, msg_OK },
    { err_UNKNOWN_COMMAND, errmsg_UNKNOWN_COMMAND },
    { err_UNAUTHORIZED, errmsg_UNAUTHORIZED },
    { err_AUTHORIZED, errmsg_AUTHORIZED },
    { err_CORRUPTED_AUTHENTIFICATION_DATA, errmsg_CORRUPTED_AUTHENTIFICATION_DATA },
    { err_WRONG_MASTER_PASSWORD, errmsg_WRONG_MASTER_PASSWORD },
    { err_FAILED_TO_SET_MASTER_PASSWORD, errmsg_FAILED_TO_SET_MASTER_PASSWORD },
    { err_PASSWORD_DOES_NOT_MEET_REQUIREMENTS, errmsg_PASSWORD_DOES_NOT_MEET_REQUIREMENTS },
    { err_FAILED_SAFE_EXIT, errmsg_FAILED_SAFE_EXIT },
    { err_UNKNOWN_ERROR, errmsg_UNKNOWN_ERROR },
    { err_NULLPTR_FREE_ATTEMPT, errmsg_NULLPTR_FREE_ATTEMPT },
    { err_NULLPTR_CLEAR_ATTEMPT, errmsg_NULLPTR_CLEAR_ATTEMPT }
};

void showup_err(int err_code)
{
    for (size_t i = 0; i < sizeof(ErrorMap); i++)
    {
        Error err = ErrorMap[i];
        if (err_code == err.err_code)
        {
            printf("# %s\n", err.errmsg);
            return;
        }
    }

    printf("%s\n", errmsg_UNKNOWN_ERROR);
}

