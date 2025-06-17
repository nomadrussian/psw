#include "safe_util.h"

#include "config.h"
#include "error.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "safe_util.h"

NOOPTIMIZE int safe_clear(void *address, size_t size)
{
    if (address == nullptr)
    {
        return err_NULLPTR_CLEAR_ATTEMPT;
    }

    memset(address, '\0', size);

    return OK;
}

NOOPTIMIZE int safe_free(void *address, size_t size)
{
    if (address == nullptr)
    {
        return err_NULLPTR_FREE_ATTEMPT;
    }

    safe_clear(address, size);
    free(address);
 
    return OK;
}

// (plug) to implement clearing RAM by force to prevent ram dumps exploits
NOOPTIMIZE int safe_exit(int exit_code)
{
    exit(exit_code);

    return err_FAILED_SAFE_EXIT;
}

