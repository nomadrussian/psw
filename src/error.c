#include "error.h"

#include <stdio.h>

const Error ErrorMap[] = {
    { SUCCESS, SUCCESS_MSG },
    { OK, OK_MSG },
    { err_UNKNOWN_COMMAND, err_UNKNOWN_COMMAND_MSG },
    { err_UNAUTHORIZED, err_UNAUTHORIZED_MSG},
    { err_NO_MASTER_PASSWORD_FOUND, err_NO_MASTER_PASSWORD_FOUND_MSG },
    { err_WRONG_MASTER_PASSWORD, err_WRONG_MASTER_PASSWORD_MSG },
    { err_FAILED_SAFE_EXIT, err_FAILED_SAFE_EXIT_MSG },
    { err_UNKNOWN_ERROR, err_UNKNOWN_ERROR_MSG }
};

void showup_err(int err_code)
{
    for (size_t i = 0; i < sizeof(ErrorMap); i++)
    {
        Error err = ErrorMap[i];
        if (err_code == err.err_code)
        {
            printf("%s\n", err.err_msg);
            return;
        }
    }

    printf("%s\n", err_UNKNOWN_ERROR_MSG);
}

