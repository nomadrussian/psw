#include "info.h"

#include <stdio.h>

#include "version.h"

int showup_info()
{
    printf("PSW %d.%d\n", VERSION_MAJOR, VERSION_MINOR);

    return 0;
}

