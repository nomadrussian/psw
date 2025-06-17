#ifndef CONFIG_H
#define CONFIG_H

#define GCC_NOOPTIMIZE __attribute__((noinline)) __attribute__((optimize("-O0")))
#define clang_NOOPTIMIZE __attribute__((noinline)) __attribute__((optnone))

/**
 * GCC 15 or higher is preferred due to full support of C23.
 * GCC 14 has problems due to only experimental C23 support.
 */
#if defined(__GNUC__) && \
    !defined(__llvm__) && \
    !defined(__INTEL_COMPILER) && \
    !defined(__clang__)
#  define __GCC__
#endif

#ifdef __GCC__
#  define SAFECOMPILER 1
#  define NOOPTIMIZE GCC_NOOPTIMIZE
#elifdef __clang__
#  define SAFECOMPILER 1
#  define NOOPTIMIZE clang_NOOPTIMIZE
#else
#  define SAFECOMPILER 0
#endif

#if __STDC_VERSION__ >= 202311L
#  define C23 1
#else
#  define C23 0
#endif

#define DATA_DIR "dt"
#define DATA_FILE_MASTER_HASH "0.dt"
#define DATA_FILE_MASTER_SALT "1.dt"
#define DATA_FILE_DATABASE_SALT "3.dt"
#define DATA_FILE_DATABASE "4.dt"

#endif

