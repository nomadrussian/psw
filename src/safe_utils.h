#ifndef SAFE_UTILS_H
#define SAFE_UTILS_H

#include <stdbool.h>
#include <stddef.h>

#include "config.h"

NOOPTIMIZE int safe_clear(void *address, size_t size);
NOOPTIMIZE int safe_free(void *address, size_t size);
NOOPTIMIZE int safe_exit(int err_code);

#endif

