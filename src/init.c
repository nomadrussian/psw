#include <assert.h>

static_assert(__STDC__ && __STDC_VERSION__, "SAFETY ALERT: Unable to detect C standard.");

#include "config.h"

static_assert(C23, "SAFETY ALERT: C23 or newer required for safety reasons.");
static_assert(SAFECOMPILER, "SAFETY ALERT: Only GCC and CLang are supported.");

#include <stdio.h>

#include "authorization.h"
#include "cli.h"

/* The entry point */
int main()
{   
    int authentification_data_status = check_authentification_data();

    CLI_run(authentification_data_status);

    return 0;
}

