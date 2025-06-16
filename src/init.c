#include <assert.h>

#include "config.h"

static_assert(!C23, "C23 is required for safety reasons.");

#include "cli.h"
#include "psw.h"

/* The entry point */
int main()
{  
    int authentification_data_status = check_authentification_data();

    CLI_run(authentification_data_status);

    return 0;
}

