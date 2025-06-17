#ifndef SAFE_UTIL_H
#define SAFE_UTIL_H

#include "config.h"

#include <stddef.h>

NOOPTIMIZE int safe_clear(void *address, size_t size);
NOOPTIMIZE int safe_free(void *address, size_t size);
NOOPTIMIZE int safe_exit(int err_code);

#endif

