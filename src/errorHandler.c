/* errorHandler.c - mainly informing the user about errors that occured */

#include <stdio.h>
#include <stdlib.h>

#include "errorHandler.h"

void err_RedundantArg(char **argv, int argID)
{
    printf(
        "REDUNDANT ARGUMENT(S): \'%s...\' [id:%d]\n"
        "USE 'help' TO GET MORE INFORMATION.\n",
        argv[argID], argID
    );

    exit(1);
}

void err_RedundantFlag(char **argv, int argID)
{
    printf(
        "REDUNDANT FLAG(S): \'%s...\' [id:%d]\n"
        "USE 'help' TO GET MORE INFORMATION.\n",
        argv[argID], argID
    );

    exit(1);
}

void err_UnexpectedArg(char **argv, int argID)
{
    printf(
        "UNEXPECTED ARGUMENT: \'%s...\' [id:%d]\n"
        "USE 'help' TO GET MORE INFORMATION ABOUT AVAILABLE "
        "ARGUMENT OPTIONS.\n",
        argv[argID], argID
    );

    exit(1);
}

void err_UnexpectedArgSpecified(char **argv, int argID, char *unexp, char *exp)
{
    printf(
        "UNEXPECTED [%s]: \'%s...\' [id:%d]\n"
        "ANTICIPATED <%s>\n"
        "USE 'help [COMMAND]' TO GET MORE INFORMATION ABOUT AVAILABLE "
        "ARGUMENT OPTIONS.\n",
        unexp, argv[argID], argID, exp
    );

    exit(1);
}

void err_UnexpectedArgRange(char **argv, int argID, char *unexp, char *exp)
{
    printf(
        "UNEXPECTED [%s]: \'%s\' [id:%d]\n"
        "ANTICIPATED RANGE: <%s>\n"
        "USE 'help [COMMAND]' TO GET MORE INFORMATION ABOUT AVAILABLE "
        "ARGUMENT OPTIONS.\n",
        unexp, argv[argID], argID, exp
    );

    exit(1);
}

